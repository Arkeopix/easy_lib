#include <pthread.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "easy_thread.h"

pthread_mutex_t	mutex;
int   easy_thread_create(easy_thread* self, handler handle_ptr)
{
  self->handle = handle_ptr;
  self->ret = pthread_create(&(self->thread), self->attr, self->handle, NULL);
  return (self->ret);
}

int   easy_thread_join(easy_thread* self)
{
  self->ret = pthread_join(self->thread, NULL);
  return (self->ret);
}

int   __init(easy_thread* self)
{
  if (!self)
    return (-1);
  self->create = &easy_thread_create;
  self->join = &easy_thread_join;
  self->arg = NULL;
  self->ret = INITIALIZED;
  self->handle = NULL;
  self->attr = NULL;
  return (self->ret);
}

void* lol(void* mabite)
{
  while (1)
    {
      printf("OMG second thread\n");
      sleep(1);
    }
  return (NULL);
}

void* xd(void* mabite)
{
  while (1)
    {
      printf("OMG xd thread\n");
      sleep(1);
    }
  return (NULL);
}

int main(int ac, char** av)
{
  easy_thread thread, mdr;

  if (__init(&thread) != INITIALIZED && __init(&mdr) != INITIALIZED)
    return (-1);
  (*(thread.create))(&thread, &lol);
  (*(mdr.create))(&mdr, &xd);
  (*(thread.join))(&thread);
  (*(mdr.join))(&mdr);
  return (0);
}
