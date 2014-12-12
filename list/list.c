#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int		easy_list_size(t_list **self)
{
  int		i;
  t_list	*tmp;

  tmp = (*self);
  i = 0;
  while (tmp)
    {
      ++i;
      tmp = tmp->next;
    }
  return (i);
}

t_list*		easy_list_remove_at(t_list **self, unsigned int n)
{
  t_list	*tmp;
  t_list	*to_rm;
  unsigned int	i;

  i = 0;
  tmp = (*self);
  to_rm = NULL;
  while (tmp && i < n)
    {
      tmp = tmp->next;
      ++i;
    }
  if (tmp)
    {
      to_rm = tmp;
      to_rm->next = NULL;
      tmp = (tmp->next) ? tmp->next : NULL;
      free(to_rm);
      to_rm = NULL;
      return (*self);
    }
  return (NULL);
}

t_list*		easy_list_remove(t_list **self, void *data)
{
  t_list	*tmp;
  t_list	*to_rm;
  
  tmp = (*self);
  to_rm = NULL;
  if (tmp && tmp->data == data)
    {
      free(tmp);
      tmp = NULL;
      (*self) = NULL;
    }
  else
    {
      while (tmp && tmp->next && tmp->next != data)
	tmp = tmp->next;
      if (tmp && tmp->next)
	{
	  to_rm = tmp;
	  tmp->next = tmp->next->next;
	  free(to_rm);
	  to_rm = NULL;
	}
    }
  return (*self);
}

bool		easy_list_is_empty(t_list **self)
{
  if ((*((*self)->size))(self) > 0)
    return (false);
  return (true);
}

void*		easy_list_add(t_list **self, void* data)
{
  t_list	*elem = NULL;

  if ((*self) && ((*((*self)->size))(self) - 1) == 0)
    elem = (*self);
  else if ((elem = easy_list_construct(&elem)) == NULL)
    return (NULL);
  elem->data = data;  
  elem->next = ((*((*self)->size))(self) > 0) ? (*self) : NULL;
  elem->empty_node = (data == NULL) ? true : false;
  (*self) = elem;
  return (*self);
}

void		easy_list_clear(t_list **self)
{
  t_list	*tmp = NULL;

  while (*self)
    {
      tmp = (*self);
      (*self) = (*self)->next;
      if (tmp->data)
	free(tmp->data);
      tmp->add = NULL;
      tmp->clear = NULL;
      tmp->data = NULL;
      tmp->is_empty = NULL;
      free(tmp);
      tmp = NULL;
    }
  (*self) = easy_list_construct(self);
}

t_list*		easy_list_construct(t_list **list)
{
  if (!(*list))
    {
      if (((*list) = malloc(sizeof(t_list))) == NULL)
	return (NULL);
    }
  (*list)->empty_node = true;
  (*list)->remove = &easy_list_remove;
  (*list)->remove_at = &easy_list_remove_at;
  (*list)->clear = &easy_list_clear;
  (*list)->add = &easy_list_add;
  (*list)->is_empty = &easy_list_is_empty;
  (*list)->size = &easy_list_size;
  (*list)->data = NULL;
  (*list)->next = NULL;
  return (*list);
}

