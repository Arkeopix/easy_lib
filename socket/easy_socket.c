#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <stdio.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <process.h>
#include "easy_socket.h"

/*
int             e_setsockopt( t_easy_socket *this, const int sock_lvl, const int optname, const int *opval ) {
  if ( setsockopt( this->_socket, sock_lvl, optname, optval, sizeof( int )) < 0 ) {
    fprintf( stderr, ERROR_SETSOCKOPT, strerror( errno ));
    return -1;
  }

  return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
int             e_bind( t_easy_socket *this ) {
  if ( bind ( thi
  s->_socket, ( struct sockaddr * )&this->_sockaddr, sizeof( this->_sockaddr )) < 0 ) {
    fprintf( stderr, ERROR_BIND, this->_socket, ,strerror( errno ));
    close( this->_socket );
    return -1;
  }

  return 0;
}

int             e_listen( t_easy_socket *this, const int backlog ) {
  if ( listen( this->_socket, backlog ) < 0 ) {
    fprintf( stderr, ERROR_LISTEN, this->_socket, ,strerror( errno ));
    close( this->_socket );
    return -1;
  }

  return 0;
}

int             e_write( t_easy_socket *this, const char *data, size_t size ) {
  char          tmp[size + 1];

  tmp =
}
*/
int             socket_init( t_easy_socket *this, const char *port, t_init *init ) {
  /*
  this->e_setsockopt = &( e_setsockopt );
  this->e_bind = &( e_bind );
  this->e_listen = &( e_listen );
  */

  WORD         version = MAKEWORD(2,2);
  WSADATA      ws_data;
  int          status;
  struct addrinfo hints;
  struct addrinfo *serv_info;
  struct addrinfo *tmp;

  if (( WSAStartup( version, &ws_data )) != 0 ){
    fprintf( stderr, WINSOCK_INIT_FAIL, WSAGetLastError() );
    return -1;
  }

  memset( &hints, 0, sizeof( hints ));
  hints.ai_family = init->sin_family;
  hints.ai_socktype = init->socket_type;
  hints.ai_protocol = init->socket_prot;
  if (( status = getaddrinfo( NULL, port, &hints, &serv_info )) != 0 ) {
    fprintf( stderr, ERROR_GETADDRINFO, gai_strerror( status ) );
    WSACleanup();
    return -1;
  }

  for ( tmp = serv_info; tmp != NULL; tmp = tmp->ai_next ) {
    if ( this->_socket = socket( tmp->ai_family, tmp->ai_socktype,
      tmp->ai_protocol ) < 0 ) {
        fprintf( stderr, ERROR_INIT_SOCKET, WSAGetLastError() );
        continue;
    }

    if ( setsockopt( this->_socket, SOL_SOCKET, SO_REUSEADDR,
      (char[]){1}, sizeof( int ) ) != 0 ) {
        fprintf( stderr, ERROR_SETSOCKOPT, WSAGetLastError() );
        WSACleanup();
        return -1;
    }

    if ( bind( this->_socket, tmp->ai_addr, tmp->ai_addrlen) == -1) {
      close( this->_socket );
      fprintf( stderr, BIND_FAIL, port );
      continue;
    }

    break;
  }

  if ( tmp == NULL ) {
    fprintf( stderr, BIND_FAIL, port );
    return -1;
  }
  freeaddrinfo( serv_info );

  if ( listen( this->_socket, BACKLOG ) == -1 ) {
    fprintf( stderr, ERROR_LISTEN);
    return -1;
  }
  return 0;
}
