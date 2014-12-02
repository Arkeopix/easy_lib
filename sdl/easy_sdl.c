#include "easy_sdl.h"
#include <stdio.h>



int		t_sdl_init(t_sdl *this, const int *init_mod, const char *name) {
  if (SDL_Init(init_mod == 1 ? SDL_INIT_VIDEO 
	       : init_mod == 2 ? SDL_INIT_SOUND 
	       : SDL_INIT_VIDEO | SDL_INIT_SOUND) < 0) {
    fprintf(stderr, ERROR_SDL_INIT, SDL_GetError());
  } else {
    if (this->_window = SDL_CreateWindow(name, 
					 SDL_WINDOWPOS_UNDEFINED, 
					 SDL_WINDOWPOS_UNDEFINED,
					 screen_x, screen_y,
					 SDL_WINDOW_SHOWN) == NULL) {
      fprintf(stderr, ERROR_WINDOW_CREATE, SDL_GetError());
    } else {
      this->_surface = SDL_GetWindowSurface(this->_window);
    }
  }
}

int		t_sdl_destroy(t_sdl *this) {
  SDL_DestroyWindow(this->_window);
  SDL_Quit();
}
