#ifndef         EASY_SOCKET_H_
#define        EASY_SOCKET_H_

#define        WINSOCK_INIT_FAIL "Winsock initialisation failed%d\n"
#define        ERROR_INIT_SOCKET "Failed to create socket: %d\n"
#define        ERROR_SETSOCKOPT  "Failed to set sockopt: %s\n"
#define        ERROR_LISTEN      "Failed to listen\n"
#define        BIND_FAIL         "Socket failed to bind socket to port %d\n"
#define        ERROR_GETADDRINFO "GetAddrInfo failed: %s\n"
#define        ERROR_ACCEPT      "Accept failed: %d\n"
#define        ERROR_STRLEN      "You have to provide a string\n"
#define        ERROR_SEND        "Send failed\n"
#define        ERROR_RECV        "Recv failed\n"
#define        ERROR_IOCTLSOCK   "Ioctlsocket failed to assert socket data: %d\n"
#define        MALLOC_FAIL       "Could not alocate memory for buffer\n"
#define        BACKLOG           10
#define        BUFF_SIZE         124

typedef struct s_easy_socket t_easy_socket;

typedef struct s_easy_socket {
	t_easy_socket *(*e_accept) (t_easy_socket *);
	int (*e_close) (t_easy_socket *);
	int (*e_write) (t_easy_socket *, const char *);
	char *(*e_read) (t_easy_socket *);

	SOCKET _socket;
	struct sockaddr_in _client_addr;
} t_easy_socket;

int socket_init(t_easy_socket *, const char *);
void _init_func(t_easy_socket *);

#endif				/* !EASY_SOCKET_H_ */
