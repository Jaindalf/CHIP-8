#include "video.h"
#include "SDL3/SDL_error.h"
//#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
//#include "SDL3/SDL_test_font.h"
#include "SDL3/SDL_video.h"
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>

bool init_sdl(sdl_vars *sv, config_vars cv) {

  if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO)) {

    SDL_Log("Error initializing SDL %s:", SDL_GetError());
    return false;
  }

  if (!SDL_SetAppMetadata(sv->mdata.name, sv->mdata.version,
                          sv->mdata.domain)) {

    SDL_Log("Error setting app metadata %s", SDL_GetError());
    return false;
  }

  sv->window =
      SDL_CreateWindow(sv->mdata.name, (cv.scale) * (cv.window_width),
                       (cv.scale) * (cv.window_height), SDL_WINDOW_RESIZABLE);
  if (sv->window == NULL) {
    SDL_Log("Error creating window %s", SDL_GetError());
    return false;
  }

  sv->renderer = SDL_CreateRenderer(sv->window, NULL);
  if (sv->renderer == NULL) {
    SDL_Log("Error creating Renderer %s", SDL_GetError());
    return false;
  }

  return true;
}

void quit_sdl(sdl_vars sv) {

  SDL_DestroyRenderer(sv.renderer);

  SDL_DestroyWindow(sv.window);
  SDL_Quit();
}

void setColor(sdl_vars *sv, color c) {

  SDL_SetRenderDrawColor(sv->renderer, c.r, c.g, c.b, c.a);
}




void draw_buffer(bool buffer[64][32], sdl_vars *sv, const config_vars *cv)
{
    setColor(sv, cv->bg_color);
    SDL_RenderClear(sv->renderer);

    setColor(sv, cv->fg_color);

    SDL_FRect r;
	r.w=r.h=cv->scale;

    for (int i = 0; i < 64; i++)
    {
		float x_val=i*cv->scale;
        for (int j = 0; j < 32; j++)
        {
            if (buffer[i][j])
            {
                r.x = x_val;
                r.y = j * cv->scale;

                SDL_RenderFillRect(sv->renderer, &r);
            }
        }
    }

    SDL_RenderPresent(sv->renderer);
}


