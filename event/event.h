#ifndef event_h
#define event_h
#include <SDL3/SDL_events.h>
void poll_Events(bool keys[0xF],bool *paused,bool *next,SDL_Event *event,bool *isRunning);

#endif