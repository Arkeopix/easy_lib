#include "easy_sdl.h"
#include <stdio.h>

int		blit_surface(t_sdl *this, SDL_Surface *surface) {
  if ((SDL_BlitSurface(surface, NULL, this->_surface, NULL)) < 0) {
    fprintf(stderr, ERROR_BLITSURFACE, SDL_GetError());
    return -1;
  }
  SDL_UpdateWindowSurface(this->_window);
  return 0;
}

int		poll_event(t_sdl *this) {
  SDL_PollEvent(&this->_event);
  return this->_event.type;
}

SDL_Surface	*load_bmp_stretch(t_sdl *this, const char *path) {
  SDL_Surface	*opti_surface = NULL;
  SDL_Surface	*loaded_surface = NULL;

  if (loaded_surface = t_sdl_load_bmp(path)) {
    if ((opti_surface = SDL_ConvertSurface(loaded_surface, this->_surface->format, 0)) == NULL) {
      fprintf(stderr, ERROR_LOADMEDIA, SDL_GetError());
    }
    SDL_FreeSurface(loaded_surface);
  }
  return opti_surface;
}

int		apply_bmp_stretch(t_sdl *this, SDL_Surface *surface) {
  SDL_Rect	stretch_rect;

  stretch_rect.x = 0;
  stretch_rect.y = 0;
  stretch_rect.w = SCREEN_WIDTH;
  stretch_rect.h = SCREEN_HEIGHT;
  SDL_BlitScaled(surface, NULL, this->_surface, &stretch_rect);
  return 0;
}

SDL_Surface	*t_sdl_load_bmp(const char *path) {  
  SDL_Surface	*surface;

  if ((surface = SDL_LoadBMP(path)) == NULL) {
    fprintf(stderr, ERROR_LOADMEDIA, SDL_GetError());
    return NULL;
  }
  return surface;
}

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
  this->blit_surface = &(blit_surface);
  this->poll_event = &(poll_event);
  this->load_bmp_stretch = &(load_bmp_stretch);
  this->apply_bmp_stretch = &(apply_bmp_stretch);
  return 0;
}

int		t_sdl_destroy(t_sdl *this) {
  SDL_DestroyWindow(this->_window);
  SDL_Quit();
  return 0;
}

int main() {
  t_sdl test;

  t_sdl_init(&test, VIDEO, "test", 500, 500);
  SDL_Surface *image_test = test.load_bmp_stretch(&test, "index.bmp");
  test.blit_surface(&test, image_test);
  int event_type;
  while (event_type = test.poll_event(&test)) {
    if (event_type == SDL_QUIT) {
      t_sdl_destroy(&test);
      exit(0);
    }
  }
  t_sdl_destroy(&test);
  return 0;
}
