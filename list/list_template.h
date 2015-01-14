#ifndef LIST_TEMPLATE_H_
# define LIST_TEMPLATE_H_

# define bool	unsigned char
# define true	1
# define false	0

# define define_list(type) \
\
typedef struct		s_list_##type \
{ \
  unsigned int		size; \
  bool			empty_node; \
  void*			(*add)(struct s_list_##type**, type); \
  void			(*clear)(struct s_list_##type**); \
  bool			(*is_empty)(struct s_list_##type**); \
  struct s_list_##type*	(*remove)(struct s_list_##type**, type); \
  struct s_list_##type*	(*remove_at)(struct s_list_##type**, unsigned int); \
  struct s_list_##type*	(*remove_last)(struct s_list_##type**); \
  struct s_list_##type*	(*remove_first)(struct s_list_##type**); \
  type			data; \
  struct s_list_##type		*next; \
}			t_list_##type; \
\
void*			easy_list_add_##type(t_list_##type **self, type data); \
void			easy_list_clear_##type(t_list_##type **self); \
bool			easy_list_is_empty_##type(t_list_##type **self); \
t_list_##type*		easy_list_remove_##type(t_list_##type **self, type data); \
t_list_##type*		easy_list_remove_last_##type(t_list_##type **self); \
t_list_##type*		easy_list_remove_first_##type(t_list_##type **self); \
t_list_##type*		easy_list_remove_at_##type(t_list_##type **self, unsigned int n); \
t_list_##type*		easy_list_constructor_##type(); \
t_list_##type*		easy_list_free_node_##type(t_list_##type* node); \
\
t_list_##type* easy_list_remove_first_##type(t_list_##type** self) \
{ \
  t_list_##type*  tmp; \
 \
  if (!(*self)) \
    return (NULL); \
  tmp = (*self); \
  (*self) = (*self)->next; \
  easy_list_free_node_##type(tmp); \
  tmp = NULL; \
  if (*self) \
    (*self)->size--; \
  return (*self); \
} \
 \
t_list_##type* easy_list_free_node_##type(t_list_##type* node) \
{ \
  node->next = NULL; \
  free(node); \
  node = NULL; \
  return (node); \
} \
 \
t_list_##type* easy_list_remove_last_##type(t_list_##type** self) \
{ \
  t_list_##type*  tmp; \
  t_list_##type*  to_rm; \
 \
  if (!(*self)) \
    return (NULL); \
  tmp = (*self); \
  if ((*self)->next == NULL) \
    return (easy_list_free_node_##type(*self)); \
  while (tmp && tmp->next && tmp->next->next) \
    tmp = tmp->next; \
  to_rm = tmp->next; \
  easy_list_free_node_##type(to_rm); \
  tmp->next = NULL; \
  (*self)->size--; \
  return (*self); \
} \
 \
t_list_##type*   easy_list_remove_at_##type(t_list_##type** self, unsigned int n) \
{ \
  t_list_##type	*tmp; \
  t_list_##type	*to_rm; \
 \
  tmp = (*self); \
 \
  if (!(*self)) \
    return (NULL); \
  else if (n == 0) \
    return (easy_list_remove_first_##type(self)); \
  else if (n == (*self)->size - 1) \
    return (easy_list_remove_last_##type(self)); \
  else if (n > (*self)->size - 1) \
    return (NULL); \
  for (unsigned int i = 0 ; i != n - 1 ; ++i) \
    tmp = tmp->next; \
  to_rm = tmp->next; \
  tmp->next = tmp->next->next; \
  easy_list_free_node_##type(to_rm); \
  (*self)->size--; \
  return (*self); \
} \
 \
t_list_##type*   easy_list_remove_##type(t_list_##type** self, type data) \
{ \
  t_list_##type*  tmp; \
  t_list_##type*  to_rm; \
 \
  tmp = (*self); \
  to_rm = NULL; \
  if (tmp && tmp->data == data) \
    { \
      free(tmp); \
      tmp = NULL; \
      (*self) = NULL; \
    } \
  else \
    { \
      while (tmp && tmp->next && tmp->next->data != data) \
        tmp = tmp->next; \
      if (tmp && tmp->next) \
        { \
          to_rm = tmp; \
          tmp->next = tmp->next->next; \
          free(to_rm); \
          to_rm = NULL; \
        } \
    } \
  return (*self); \
} \
 \
bool    easy_list_is_empty_##type(t_list_##type** self) \
{ \
  if ((*self)->size > 0) \
    return (false); \
  return (true); \
} \
 \
void*   easy_list_add_##type(t_list_##type** self, type data) \
{ \
  t_list_##type*  elem = NULL; \
 \
  if (!(*self)) \
    return (NULL); \
  else \
    if ((*self)->empty_node == true) \
      { \
        (*self)->data = data; \
        (*self)->size++; \
        (*self)->empty_node = false; \
        return (*self); \
      } \
  if ((elem = easy_list_constructor_##type()) == NULL) \
    return (NULL); \
  elem->size = (*self)->size + 1; \
  elem->data = data; \
  elem->next = (*self); \
  elem->empty_node = false; \
  (*self) = elem; \
  return (*self); \
} \
 \
void    easy_list_clear_##type(t_list_##type** self) \
{ \
  t_list_##type*  tmp = NULL; \
 \
  while (*self) \
    { \
      tmp = (*self); \
      (*self) = (*self)->next; \
      tmp->add = NULL; \
      tmp->clear = NULL; \
      tmp->is_empty = NULL; \
      free(tmp); \
      tmp = NULL; \
    } \
  (*self) = easy_list_constructor_##type(); \
}\
\
t_list_##type*		easy_list_constructor_##type() \
{ \
  t_list_##type*	list = NULL; \
  if ((list = malloc(sizeof(t_list_##type))) == NULL) \
    return (NULL); \
  list->empty_node = true; \
  list->remove = &easy_list_remove_##type; \
  list->remove_at = &easy_list_remove_at_##type; \
  list->clear = &easy_list_clear_##type; \
  list->add = &easy_list_add_##type; \
  list->is_empty = &easy_list_is_empty_##type; \
  list->remove_first = &easy_list_remove_first_##type; \
  list->remove_last = &easy_list_remove_last_##type; \
  list->next = NULL; \
  list->size = 0; \
  return (list); \
}

#define List(type) \
    t_list_##type*

#define new_list(type) \
    easy_list_constructor_##type()

#endif /* !LIST_TEMPLATE_H_ */
