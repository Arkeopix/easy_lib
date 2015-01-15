#ifndef		EASY_SDL_
# define	EASY_SDL_

# include	<SDL2/SDL.h>

# define	VIDEO	1
# define	SOUND	2
# define	ALL	3

# define	ERROR_SDL_INIT		"SDL could not initialize: error %s\n"
# define	ERROR_WINDOW_CREATE	"SDL could not create window: error %s\n"
# define	ERROR_LOADMEDIA		"SDL could not load media: error %s\n"
# define	ERROR_BLITSURFACE	"SDL could not blit surface: error %s\n"

typedef struct	s_sdl t_sdl;

typedef struct	s_sdl {
  SDL_Window	*_window;
  SDL_Surface	*_surface;
  SDL_Event	_event;
  
  int		(*blit_surface)(t_sdl *, SDL_Surface *);
  int		(*poll_event)(t_sdl *);
}		t_sdl;	

int		t_sdl_init(t_sdl *, const int, const char*, const int, const int);
int		t_sdl_destroy(t_sdl *);
SDL_Surface    	*t_sdl_load_bmp(const char *);

#endif		/* !EASY_SDL */
