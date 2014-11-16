#include <pthread.h>
#include <stdarg.h>

#include "easy_thread.h"

int		create(easy_thread* self, handler handle_ptr)
{
  self->handle = handle_ptr;
  self->ret = pthread_create(&self->thread, self->attr, self->handle, NULL);
  return (self->ret);
}

int		join(easy_thread* self)
{
  self->ret = pthread_join(self->thread, NULL);
  return (self->ret);
}

int		__init(easy_thread* self)
{
  self->create = &easy_thread_create;
  self->join = &easy_thread_join;
  self->arg = NULL;
  self->ret = INITIALIZED;
  self->handle = NULL;
  self->attr = NULL;
  return (self->ret);
}
