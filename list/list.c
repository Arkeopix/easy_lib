#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"

t_list* easy_list_remove_first(t_list** self)
{
  t_list*  tmp;

  if (!(*self))
    return (NULL);
  tmp = (*self);
  (*self) = (*self)->next;
  if (tmp->data)
    free(tmp->data);
  free(tmp);
  tmp = NULL;
  if (*self)
    (*self)->size--;
  return (*self);
}

t_list* easy_list_free_node(t_list* node)
{
  node->next = NULL;
  if (node->data)
  {
    free(node->data);
    node->data = NULL;
  }
  free(node);
  node = NULL;
  return (node);
}

t_list* easy_list_remove_last(t_list** self)
{
  t_list*  tmp;
  t_list*  to_rm;

  if (!(*self))
    return (NULL);
  tmp = (*self);
  if ((*self)->next == NULL)
    return (easy_list_free_node(*self));
  while (tmp && tmp->next && tmp->next->next)
    tmp = tmp->next;
  to_rm = tmp->next;
  easy_list_free_node(to_rm);
  tmp->next = NULL;
  (*self)->size--;
  return (*self);
}

t_list*   easy_list_remove_at(t_list** self, unsigned int n)
{
  t_list	*tmp;
  t_list	*to_rm;

  tmp = (*self);

  if (!(*self))
    return (NULL);
  else if (n == 0)
    return (easy_list_remove_first(self));
  else if (n == (*self)->size - 1)
    return (easy_list_remove_last(self));
  else if (n > (*self)->size - 1)
    return (NULL);
  for (unsigned int i = 0 ; i != n - 1 ; ++i)
    tmp = tmp->next;
  to_rm = tmp->next;
  tmp->next = tmp->next->next;
  easy_list_free_node(to_rm);
  (*self)->size--;
  return (*self);
}

t_list*   easy_list_remove(t_list** self, void* data)
{
  t_list*  tmp;
  t_list*  to_rm;

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

bool    easy_list_is_empty(t_list** self)
{
  if ((*self)->size > 0)
    return (false);
  return (true);
}

void*   easy_list_add(t_list** self, void* data)
{
  t_list*  elem = NULL;

  if (!(*self))
    return (NULL);
  else
    if ((*self)->empty_node == true)
      {
        (*self)->data = data;
        (*self)->size++;
        (*self)->empty_node = false;
        return (*self);
      }
  if ((elem = easy_list_constructor(&elem)) == NULL)
    return (NULL);
  elem->size = (*self)->size + 1;
  elem->data = data;
  elem->next = (*self);
  elem->empty_node = false;
  (*self) = elem;
  return (*self);
}

void    easy_list_clear(t_list** self)
{
  t_list*  tmp = NULL;

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
  (*self) = easy_list_constructor(self);
}

t_list*   easy_list_constructor(t_list** list)
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
  (*list)->remove_first = &easy_list_remove_first;
  (*list)->remove_last = &easy_list_remove_last;
  (*list)->data = NULL;
  (*list)->next = NULL;
  (*list)->size = 0;
  return (*list);
}

