#include "easy_sdl.h"
#include <stdio.h>

int		t_sdl_init(t_sdl *this, const int init_mod, const char *name,
			   const int screen_x, const int screen_y) {
  if (SDL_Init(init_mod == 1 ? SDL_INIT_VIDEO 
	       : init_mod == 2 ? SDL_INIT_AUDIO 
	       : SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    fprintf(stderr, ERROR_SDL_INIT, SDL_GetError());
  } else {
    if ((this->_window = SDL_CreateWindow(name, 
					 SDL_WINDOWPOS_UNDEFINED, 
					 SDL_WINDOWPOS_UNDEFINED,
					 screen_x, screen_y,
					 SDL_WINDOW_SHOWN)) == NULL) {
      fprintf(stderr, ERROR_WINDOW_CREATE, SDL_GetError());
    } else {
      this->_surface = SDL_GetWindowSurface(this->_window);
    }
  }
  return 0;
}

int		t_sdl_destroy(t_sdl *this) {
  SDL_DestroyWindow(this->_window);
  SDL_Quit();
  return 0;
}

int		t_sdl_load_media(SDL_Surface *surface, const char *path) {
  

  if ((surface = SDL_LoadBMP(path)) == NULL) {
    fprintf(stderr, ERROR_LOADMEDIA, SDL_GetError());
    return -1;
  }
  return 0;
}

int		blit_surface(t_sdl *this, SDL_Surface *surface) {
  if ((SDL_BlitSurface(surface, NULL, this->_surface, NULL)) < 0) {
    fprintf(stderr, ERROR_BLITSURFACE, SDL_GetError());
    return -1;
  }
  SDL_UpdateWindowSurface(this->_window);
  return 0;
}

int main() {
  t_sdl test;

  t_sdl_init(&test, VIDEO, "test", 500, 500);
  SDL_Surface image_test;
  t_sdl_load_BMP(&image_test, "index.jpeg");
  test.blit_surface(&test, &image_test);
  t_sdl_destroy(&test);
  return 0;
}
