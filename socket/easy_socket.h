#ifndef         EASY_SOCKET_H_
# define        EASY_SOCKET_H_

# define        WINSOCK_INIT_FAIL "Winsock initialisation failed%d\n"
# define        ERROR_INIT_SOCKET "Failed to create socket: %d\n"
# define        ERROR_SETSOCKOPT  "Failed to set sockopt: %s\n"
# define        ERROR_LISTEN      "Failed to listen\n"
# define        BIND_FAIL         "Socket failed to bind socket to port %d\n"
# define        ERROR_GETADDRINFO "GetAddrInfo failed: %s\n"
# define        BACKLOG           10

typedef struct  s_easy_socket t_easy_socket;

typedef struct  s_easy_socket {
/*
  int           ( *e_setsockopt )( t_easy_socket *, const int, const int, const int * );
  int           ( *e_bind )( t_easy_socket *);
  int           ( *e_listen ) ( t_easy_socket *, const int );
  int           ( *e_write ) ( t_easy_socket *, const char *, size_t size );
*/

  int           _socket;
}               t_easy_socket;

typedef struct          s_init {
  int                   sin_family;
  int                   socket_type;
  int                   socket_prot;
}                       t_init;

int             socket_init( t_easy_socket *, const char*, t_init * );

#endif          /* !EASY_SOCKET_H_ */
