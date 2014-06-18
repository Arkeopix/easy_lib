/*
** regex.c for zappy in /home/mendie_j/code/c/project/zappy
** 
** Made by mendiela
** Login   <mendie_j@epitech.net>
** 
** Started on  Tue May  6 09:28:14 2014 mendiela
** Last update Tue May  6 11:40:48 2014 mendiela
*/

#define _GNU_SOURCE
#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "regex.h"

char    	*get_match( t_regex *this, const int offset ) {
  return ( this->_f_size > offset ? this->_f_match[offset] : NULL );
}

void		clean_match( t_regex *this ) {
  memset( &this->_f_match, 0, sizeof( this->_f_match ) );
}

static int     	match_loop( t_regex *this, regmatch_t *m, const char *p, const char *str ) {
  char		*buffer;
  int		i;
  static int   	j = 0;
  int		start;
  int		finish;

  i = 0;
  while ( i < this->_n_match ) {
      if ( m[i].rm_so == -1 )
	return ( 1 );
      start = m[ i ].rm_so + ( p - str );
      finish = m[ i ].rm_eo + ( p - str );
      asprintf( &buffer, "%.*s", ( finish - start ), str + start );
      if ( j == MATCH_MALLOC( this->_n_match ) )
	return ( 1 );
      this->_f_match[ j ] = strdup( buffer );
      free( buffer );
      this->_f_size = j + 1;
      i++;
      j++;
    }
}

int     	match( t_regex *this, const char *str )
{
  const char   	*p;
  int		nomatch;
  int		start;
  int		finish;
  regmatch_t	m[ this->_n_match ];

  p = str;
  if ( ( this->_f_match = malloc( MATCH_MALLOC( this->_n_match ) * sizeof( char* ) ) ) == NULL )
    return ( 1 );
  while ( 42 ) {
      nomatch = regexec( &this->_regex, p, this->_n_match, m, 0 );
      if ( nomatch )
	return ( nomatch );
      match_loop( this, m, p, str );
      p += m[ 0 ].rm_eo;
    }
  return ( 0 );
}

int		t_regex_init( t_regex *this, const char *regex, const int nbr_match, const int flags ) {
  int		status;
  char		error[ MAX_ERR_MSG ];
  
  this->match = &( match );
  this->get_match = &( get_match );
  this->clean_match = &( clean_match );
  this->_n_match = nbr_match;
  status = regcomp( &this->_regex, regex, flags );
  if ( status ) {
      regerror( status, &this->_regex, error, MAX_ERR_MSG );
      fprintf( stderr, "Error compiling regex %s: %s\n", regex, error );
      return ( 1 );
    }
  return ( 0 );
}

int		t_regex_destroy( t_regex *this ) {
  int		i;

  i = 0;
  while ( i < this->_f_size ) {
    free(this->_f_match[ i ]);
    i++;
  }
  free( this->_f_match );
  regfree( &this->_regex );
}
