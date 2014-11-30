#ifdef  _WIN32
  #ifndef WIN32_LEAN_AND_MEAN
  #define WIN32_LEAN_AND_MEAN
  #endif
  #include <windows.h>
  #include <sys/socket.h>
  #include <ws2tcpip.h>
  #include <process.h>
#elif __linux__
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netdb.h>
  #include <sys/ioctl.h>
  #include <netinet/in.h>
  #include <netinet/ip.h>
  #include <string.h>
  #include <stdlib.h>
  #include <errno.h>
#endif
#include <stdio.h>

#include "easy_socket.h"

t_easy_socket *e_accept(t_easy_socket * this)
{
	t_easy_socket *new;
	int size = sizeof(struct sockaddr);

	memset(&new->_client_addr, 0, sizeof(new->_client_addr));
	if (new->_socket =
	    accept(this->_socket, (struct sockaddr *)&new->_client_addr,
		   &size) == -1) {
	  fprintf(stderr, ERROR_ACCEPT), perror("accept");
	  return NULL;
	}
	_init_func(new);
	return new;
}

int *e_close(t_easy_socket * this)
{
	close(this->_socket);
}

int e_write(t_easy_socket * this, const char *str)
{
	int len, bytes = 0, bytes_left = 0, total = 0;

	if (str == NULL || (len = strlen(str) <= 0)) {
		fprintf(stderr, ERROR_STRLEN);
		return -1;
	}

	bytes_left = len;
	while (total < len) {
		if ((bytes =
		     send(this->_socket, str + total, bytes_left, 0)) == -1) {
			fprintf(stderr, ERROR_SEND);
			return -1;
		}
		total += bytes;
		bytes_left -= bytes;
	}
	return 0;
}

char *e_read(t_easy_socket * this)
{
	char buff[BUFF_SIZE];
	char *ret;
	unsigned long n = 0;
	int total = 0, bytes;

#ifdef _WIN32 
	if (ioctlsocket(this->_socket, FIONREAD, &n) < 0) {
		fprintf(stderr, ERROR_IOCTLSOCK, WSAGetLastError());
		return NULL;
	}
#elif __linux__
	if (ioctl(this->_socket, FIONREAD, &n) < 0) {
		fprintf(stderr, ERROR_IOCTL), perror("ioctl");
		return NULL;
	}
#endif
	if ((ret = malloc(n * sizeof(*ret))) == NULL) {
		fprintf(stderr, MALLOC_FAIL);
		return NULL;
	}

	while (total < n) {
		if (bytes = recv(this->_socket, buff, BUFF_SIZE, 0) <= 0) {
			fprintf(stderr, ERROR_RECV);
			free(ret);
			return NULL;
		}
		strncpy(ret, buff, total);
		total += bytes;
	}
	return ret;
}

void _init_func(t_easy_socket * this)
{
	this->e_accept = &(e_accept);
	this->e_write = &(e_write);
}

int socket_init(t_easy_socket * this, const char *port)
{
#ifdef _WIN32
	WORD version = MAKEWORD(2, 2);
	WSADATA ws_data;
#endif
	int status;
	struct addrinfo hints;
	struct addrinfo *serv_info;
	struct addrinfo *tmp;

#ifdef _WIN32
	if ((WSAStartup(version, &ws_data)) != 0) {
		fprintf(stderr, WINSOCK_INIT_FAIL, WSAGetLastError());
		return -1;
	}
#endif
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	if ((status = getaddrinfo(NULL, port, &hints, &serv_info)) != 0) {
		fprintf(stderr, ERROR_GETADDRINFO, gai_strerror(status));
#ifdef _WIN32
		WSACleanup();
#endif
		return -1;
	}

	for (tmp = serv_info; tmp != NULL; tmp = tmp->ai_next) {
		if (this->_socket = socket(tmp->ai_family, tmp->ai_socktype,
					   tmp->ai_protocol) ==
		    -1) {
			fprintf(stderr, ERROR_INIT_SOCKET), perror("socket");
			return -1;
		}
	}

	printf("socket = %d\n", this->_socket);
	if (setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR, (const char[]) {
		       1}, sizeof(int)) != 0) {
  fprintf(stderr, ERROR_SETSOCKOPT), perror("setsockopt");
#ifdef _WIN32
		WSACleanup();
#endif
		return -1;
	}
	printf("xouxou\n");

	if (bind(this->_socket, tmp->ai_addr, tmp->ai_addrlen) == -1) {
		close(this->_socket);
		fprintf(stderr, BIND_FAIL, port);
	}

	if (tmp == NULL) {
		fprintf(stderr, BIND_FAIL, port);
#ifdef _WIN32
		WSACleanup();
#endif
		return -1;
	}
	freeaddrinfo(serv_info);

	if (listen(this->_socket, BACKLOG) == -1) {
		close(this->_socket);
#ifdef _WIN32
		WSACleanup();
#endif
		fprintf(stderr, ERROR_LISTEN);
		return -1;
	}
	return 0;
}

int main(void)
{
	t_easy_socket serv_socket, *client_socket;

	if (socket_init(&serv_socket, "6669") != 0) {
		fprintf(stderr, "oups");
	}

	while (42) {
		if ((client_socket =
		     serv_socket.e_accept(&serv_socket)) != NULL) {
			printf("youps\n");
		}
	}
}
