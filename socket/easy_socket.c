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

int             e_write( t_easy_socket *this, const char *str ) {
  int           len, bytes = 0, bytes_left = 0, total = 0;

  if ( str == NULL || ( len = strlen( str ) <= 0 ) ) {
    fprintf( stderr, ERROR_STRLEN);
    return -1;
  }

  bytes_left = len;
  while ( total < len ) {
    if ( ( bytes = send( this->_socket, str + total, bytes_left, 0 ) ) == -1 ) {
      fprintf( stderr, ERROR_SEND);
      return -1;
    }
    total += bytes;
    bytes_left -= bytes;
  }
  return 0;
}

char            *e_read( t_easy_socket *this ) {
  char          buff[BUFF_SIZE];
  char          *ret;
  unsigned long n = 0;
  int           total = 0, bytes;

  if ( ioctlsocket( this->_socket, FIONREAD, &n) < 0 ) {
    fprintf( stderr, ERROR_IOCTLSOCK, WSAGetLastError() );
    return NULL;
  }
  if ( ( ret = malloc( n * sizeof( *ret ) ) ) == NULL ) {
    fprintf( stderr, MALLOC_FAIL);
    return NULL;
  }

  while ( total < n ) {
    if ( bytes = recv( this->_socket, buff, BUFF_SIZE, 0 ) <= 0 ) {
      fprintf( stderr, ERROR_RECV );
      free( ret );
      return NULL;
    }
    strncpy( ret, buff, total );
    total += bytes;
  }
  return ret;
}

void            _init_func( t_easy_socket *this ) {
  this->e_accept = &( e_accept );
  this->e_write = &( e_write );
}

int            socket_init( t_easy_socket *this, const char *port, t_init *init ) {
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
    if (( status = getaddrinfo( NULL, port, &hints, &serv_info )) != 0 ) {
    fprintf( stderr, ERROR_GETADDRINFO, gai_strerror( status ) );
    WSACleanup();
    return -1;
  }


  for ( tmp = serv_info; tmp != NULL; tmp = tmp->ai_next ) {
    if ( this->_socket = socket( tmp->ai_family, tmp->ai_socktype,
      tmp->ai_protocol ) == INVALID_SOCKET ) {
        fprintf( stderr, ERROR_INIT_SOCKET, WSAGetLastError() );
        continue;
    }

    printf( "socket = %d\n", this->_socket);
    if ( setsockopt( this->_socket, SOL_SOCKET, SO_REUSEADDR,
      (const char[]){1}, sizeof( int ) ) != 0 ) {
        fprintf( stderr, ERROR_SETSOCKOPT, WSAGetLastError() );
        WSACleanup();
        return -1;
    }

    printf( "xouxou\n");

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

int       main(void) {
  t_init  init;
  t_easy_socket serv_socket, *client_socket;

  init.sin_family = AF_UNSPEC;
  init.socket_type = SOCK_STREAM;

  if ( socket_init( &serv_socket, "6669", &init ) != 0 ) {
    fprintf( stderr, "oups" );
  }

  while ( 42 ) {
    if ( ( client_socket = serv_socket.e_accept( &serv_socket ) ) != NULL ) {
      printf( "youps\n");
    }
  }
}
