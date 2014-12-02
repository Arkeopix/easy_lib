#ifndef		EASY_SDL_
# define	EASY_SDL_

# include	<SD2/SDL.h>

# define	VIDEO	1
# define	SOUND	2

# define	ERROR_SDL_INIT		"SDL could not initialize: error %s\n"
# define	ERROR_WINDOW_CREATE	"SDL could not create window: erroe %s\n"

typedef struct	s_sdl t_sdl;

typedef struct	s_sdl {
  SDL_Window	*_window;
  SDL_Surface	*_surface;
  
}		t_sdl;	

int		t_sdl_init(t_sdl *, const int, const char*);
int		t_sdl_destroy(t_sdl *);

#endif		/* !EASY_SDL */
