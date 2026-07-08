#include "SDL3/SDL.h"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_test_font.h"
#include "SDL3/SDL_video.h"
#include <stdio.h>

bool init_sdl(SDL_Window **window, SDL_Renderer **ren) {

  if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO)) {

    SDL_Log("Error initializing SDL %s:", SDL_GetError());
    return false;
  }

  if (!SDL_SetAppMetadata("CHIP-8 EMULATOR", "0.0.1", "com.emulator.chip-8")) {

    SDL_Log("Error setting app metadata %s", SDL_GetError());
    return false;
  }

  *window = SDL_CreateWindow("CHIP-8 EMULATOR", 640, 320, SDL_WINDOW_RESIZABLE);
  if (*window == NULL) {
    SDL_Log("Error creating window %s", SDL_GetError());
    return false;
  }

  *ren = SDL_CreateRenderer(*window, NULL);
  if (*ren == NULL) {
    SDL_Log("Error creating Renderer %s", SDL_GetError());
    return false;
  }

  return true;
}

void quit_sdl(SDL_Window *window, SDL_Renderer *ren) {

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(ren);
  SDL_Quit();
}

int main() {
  SDL_Window *win = NULL;
  SDL_Renderer *ren = NULL;
  SDL_Event event;
  bool isRunning = true;

  bool buf[64][32];

  for (int i = 0; i < 64; i++) {
    for (int j = 0; j < 32; j++) {
      if (i % 4 == 0 & j % 2 == 0) {
        buf[i][j] = true;

      } else {
        buf[i][j] = false;
      }
    }
  }
  if (init_sdl(&win, &ren)) {
    while (isRunning) {
      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
          isRunning = false;
        }

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        SDL_RenderPresent(ren);
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        int sc = 10;
        SDL_FRect r;
        for (int i = 0; i < 64; i++) {
          for (int j = 0; j < 32; j++) {
            if (buf[i][j]) {
              r.x = i * sc;
              r.y = j * sc;
              r.h = sc;
              r.w = sc;
              SDL_RenderFillRect(ren, &r);
            }
          }
        }
        SDL_RenderPresent(ren);
      }
    }
    quit_sdl(win, ren);
  }

  return 0;
}
