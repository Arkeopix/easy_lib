/*
** regex.h for zappy in /home/mendie_j/code/c/project/zappy
** 
** Made by mendiela
** Login   <mendie_j@epitech.net>
** 
** Started on  Tue May  6 09:21:50 2014 mendiela
** Last update Tue May  6 11:46:47 2014 mendiela
*/

#ifndef			REGEX_H_
# define		REGEX_H_

# define		MAX_ERR_MSG	0x1000
# define		MATCH_MALLOC(x)	4 * x

typedef struct		s_regex t_regex;

typedef struct		s_regex {
  int			( *match )( t_regex *, const char * );
  char			*( *get_match )( t_regex *,const int );
  void			( *clean_match )( t_regex * );
  regex_t		_regex;
  int			_n_match;
  char			**_f_match;
  int			_f_size;
}			t_regex;

int			t_regex_init( t_regex *, const char *, const int, const int );
int			t_regex_destroy( t_regex * );
int			match( t_regex *, const char * );
char			*get_match( t_regex*, const int );
void			clean_match( t_regex * );

#endif			/* !REGEX_H_ */
