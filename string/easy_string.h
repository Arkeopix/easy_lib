#ifndef		EASY_STRING_H_
# define	EASY_STRING_H_

# define	ERROR_MALLOC_FAILED		"Error memory allocation failed: %s"

typedef struct	s_easy_string {
    char		*string;
	int			len;
	int			allocated_memory;
	
	int			(*e_len)(struct s_easy_string *this);
	int			(*e_resize)(struct s_easy_string *this, const int new_size, ...);
	int			(*e_reserve)(struct s_easy_string *this, const int new_size);
	int			(*e_clear)(struct s_easy_string *this);
	int			(*e_empty)(struct s_easy_string *this);
	int			(*e_shrink_to_fit)(struct s_easy_string *this);
}				t_easy_string;

int		e_string_init(t_easy_string *this, char *str);
int		e_string_destroy(t_easy_string *this);

#endif		/* !EASY_STRING_H_ */
