#ifndef LIST_H_
# define LIST_H_

# define bool	unsigned char
# define true	1
# define false	0

typedef struct		s_list
{
  unsigned int		size;
  bool			empty_node;
  void*			(*add)(struct s_list**, void*);
  void			(*clear)(struct s_list**);
  bool			(*is_empty)(struct s_list**);
  struct s_list*	(*remove)(struct s_list**, void*);
  struct s_list*	(*remove_at)(struct s_list**, unsigned int);
  struct s_list*	(*remove_last)(struct s_list**);
  struct s_list*	(*remove_first)(struct s_list**);
  void			*data;
  struct s_list		*next;
}			t_list;

void*			easy_list_add(t_list **self, void *data);
void			easy_list_clear(t_list **self);
bool			easy_list_is_empty(t_list **self);
t_list*			easy_list_remove(t_list **self, void *data);
t_list*			easy_list_remove_last(t_list **self);
t_list*			easy_list_remove_first(t_list **self);
t_list*			easy_list_remove_at(t_list **self, unsigned int n);
t_list*			easy_list_constructor(t_list **list);
t_list*			easy_list_free_node(t_list* node);

#endif /* !LIST_H_ */
