#ifndef EASY_THREAD
#define EASY_THREAD

#define	INITIALIZED	5

struct			s_easy_thread;

typedef	void*		(*handler)(void*);
typedef	int		(*fptr)(struct s_easy_thread*, ...);

typedef struct		s_easy_thread
{
  pthread_t		thread;
  handler		handle;
  fptr			create;
  fptr			join;
  pthread_attr_t*	attr;
  void*			arg;
  int			ret;
}       		easy_thread;

int			easy_thread_init(easy_thread* self);
int			easy_thread_create(easy_thread* self, handler handle_ptr);
int			easy_thread_join(easy_thread* self);

#endif /* EASY_THREAD */
