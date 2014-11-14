#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <stdio.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <process.h>
#include "easy_socket.h"

t_easy_socket   *e_accept( t_easy_socket *this ) {
  t_easy_socket *new;
  int           size = sizeof( struct sockaddr );

  memset( &new->_client_addr, 0, sizeof( new->_client_addr ));
  if ( new->_socket = accept( this->_socket, (struct sockaddr*)&new->_client_addr,
    &size) == -1 ) {
      fprintf( stderr, ERROR_ACCEPT, WSAGetLastError() );
      return NULL;
  }
  _init_func( new );
  return new;
}

int             *e_close( t_easy_socket *this ) {
  close( this->_socket );
}

char            *e_read( t_easy_socket *this ) {
  
}


void            _init_func( t_easy_socket *this ) {
  this->e_accept = &( e_accept );
}

int             socket_init( t_easy_socket *this, const char *port, t_init *init ) {
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
    WSACleanup();
    return -1;
  }
  freeaddrinfo( serv_info );

  if ( listen( this->_socket, BACKLOG ) == -1 ) {
    close( this->_socket );
    WSACleanup();
    fprintf( stderr, ERROR_LISTEN);
    return -1;
  }
  return 0;
}
