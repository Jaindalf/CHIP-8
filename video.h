#ifndef video_h
#define video_h
#include<SDL3/SDL.h>
typedef struct {
  char *name;
  char *version;
  char *domain;

} metadata;

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Event event;
  metadata mdata;
} sdl_vars;

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} color;

typedef struct {
  int window_width;
  int window_height;
  int scale;
  color fg_color;
  color bg_color;

} config_vars;

#define BLACK {0, 0, 0, 255}
#define WHITE {255, 255, 255, 255}



bool init_sdl(sdl_vars *sv, config_vars cv);
void quit_sdl(sdl_vars sv);
void setColor(sdl_vars *sv, color c);
void draw_buffer(bool buffer[64][32], sdl_vars *sv, const config_vars *cv);

#endif
