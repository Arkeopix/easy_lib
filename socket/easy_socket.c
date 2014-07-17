#include "easy_socket.h"

int             e_setsockopt( t_easy_socket *this, const int sock_lvl, const int optname, const int *opval ) {
  if ( setsockopt( this->_socket, sock_lvl, optname, optval, sizeof( int )) < 0 ) {
    fprintf( stderr, ERROR_SETSOCKOPT, strerror( errno ));
    return -1;
  }

  return 0;
}

int             e_bind( t_easy_socket *this ) {
  if ( bind ( this->_socket, ( struct sockaddr * )&this->_sockaddr, sizeof( this->_sockaddr )) < 0 ) {
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

int             socket_init( t_easy_socket *this, const int port, t_init *init ) {
  this->e_setsockopt = &( e_setsockopt );
  this->e_bind = &( e_bind );
  this->e_listen = &( e_listen );
  memset( &this._sockaddr, 0, sizeof( this->_sockaddr ));
  sockaddr.sin_family = init->sin_family;
  sockaddr.sin_addr.s_addr = htonl( init->s_addr );
  sockaddr.sin_port = htons( port );

  if (( this->socket = socket( sockaddr.sin_family, init->socket_type, init->socket_prot )) < 0 ) {
    fprintf( stderr, ERROR_INIT_SOCKET, strerror( errno ));
    return -1;
  }

  return 0;
}
