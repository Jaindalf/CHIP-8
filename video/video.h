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
  SDL_AudioStream *stream;
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
  int channels;
  float frequency; //Sampling rate
  float sin_frequency;
  int current_sine_sample;
  bool playing;

}audio_config_vars;


typedef struct {
  int window_width;
  int window_height;
  int scale;
  color fg_color;
  color bg_color;
  audio_config_vars audio_config;

} config_vars;

#define BLACK ((color){0, 0, 0, 255})
#define WHITE ((color){255, 255, 255, 255})



bool init_sdl(sdl_vars *sv, config_vars cv);
void quit_sdl(sdl_vars sv);
void setColor(sdl_vars *sv, color c);
void draw_buffer(bool buffer[64][32], sdl_vars *sv, const config_vars *cv);
//audio stuff
void fill_audio_stream(sdl_vars *sv, config_vars *cv);
void control_audio_stream(sdl_vars *sv, config_vars *cv,bool soundTimer);
//void update(bool buffer[64][32],sdl_vars *sv,const config_vars *cv); //this really should not exist.

#endif
