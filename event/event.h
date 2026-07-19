#ifndef event_h
#define event_h
#include <SDL3/SDL_events.h>
#ifdef __cplusplus
extern "C" {
#endif

void poll_Events(bool keys[0xF],bool *paused,bool *next,SDL_Event *event,bool *isRunning);
#ifdef __cplusplus
}
#endif
#endif