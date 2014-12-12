#ifndef EASY_THREAD
#define EASY_THREAD

#define	INITIALIZED	5

struct			s_easy_thread;

typedef union {
  double (*func_one)(void*);
  double (*func_multiple)(void*, ...);
} fptrs;

typedef	void*		(*handler)(void*);
typedef	int		(*fptr)(void*);
typedef	int		(*mptr)(void*, void*);

typedef struct		s_easy_thread
{
  pthread_t		thread;
  handler		handle;
  mptr			create;
  fptr			join;
  pthread_attr_t*	attr;
  void*			arg;
  int			ret;
}       		easy_thread;

int			easy_thread_init(easy_thread* self);
int			easy_thread_create(easy_thread* self, handler handle_ptr);
int			easy_thread_join(easy_thread* self);

#endif /* EASY_THREAD */
