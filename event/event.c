#include "event.h"
#include<stdio.h>
void poll_Events(bool keys[0xF],bool *paused,bool *next,SDL_Event *event,bool *isRunning) {


    while (SDL_PollEvent(event))
    {
        switch (event->type)
        {
            case SDL_EVENT_QUIT:
                *isRunning = false;
                break;

            case SDL_EVENT_KEY_DOWN:
            {
                switch (event->key.key)
                {
                    case SDLK_ESCAPE:
                        *isRunning = false;
                        break;

                    case SDLK_X:
                    {
                        keys[0] = 1;
                        printf("x pressed\n");

                    } break;

                    case SDLK_1:
                    {
                        keys[1] = 1;
                        printf("1 pressed\n");
                    } break;

                    case SDLK_2:
                    {
                        keys[2] = 1;
                    } break;

                    case SDLK_3:
                    {
                        keys[3] = 1;
                    } break;

                    case SDLK_Q:
                    {
                        keys[4] = 1;
                    } break;

                    case SDLK_W:
                    {
                        keys[5] = 1;
                    } break;

                    case SDLK_E:
                    {
                        keys[6] = 1;
                    } break;

                    case SDLK_A:
                    {
                        keys[7] = 1;
                    } break;

                    case SDLK_S:
                    {
                        keys[8] = 1;
                    } break;

                    case SDLK_D:
                    {
                        keys[9] = 1;
                    } break;

                    case SDLK_Z:
                    {
                        keys[0xA] = 1;
                    } break;

                    case SDLK_C:
                    {
                        keys[0xB] = 1;
                    } break;

                    case SDLK_4:
                    {
                        keys[0xC] = 1;
                    } break;

                    case SDLK_R:
                    {
                        keys[0xD] = 1;
                    } break;

                    case SDLK_F:
                    {
                        keys[0xE] = 1;
                    } break;

                    case SDLK_V:
                    {
                        keys[0xF] = 1;
                    } break;

                    case  SDLK_P: {
                        *paused=!(*paused);
                    }

                    case  SDLK_N: {
                        *next=1;
                    }


                    default:
                        break;
                }
                break;
            }



            case SDL_EVENT_KEY_UP:
            {
                switch (event->key.key)
                {
                    /*case SDLK_ESCAPE:
                        *isRunning = true;
                        break;*/

                    case SDLK_X:
                    {
                        keys[0] = 0;
                        printf("x released\n");

                    } break;

                    case SDLK_1:
                    {
                        keys[1] = 0;
                        printf("1 released\n");
                    } break;

                    case SDLK_2:
                    {
                        keys[2] = 0;
                    } break;

                    case SDLK_3:
                    {
                        keys[3] = 0;
                    } break;

                    case SDLK_Q:
                    {
                        keys[4] = 0;
                    } break;

                    case SDLK_W:
                    {
                        keys[5] = 0;
                    } break;

                    case SDLK_E:
                    {
                        keys[6] = 0;
                    } break;

                    case SDLK_A:
                    {
                        keys[7] = 0;
                    } break;

                    case SDLK_S:
                    {
                        keys[8] = 0;
                    } break;

                    case SDLK_D:
                    {
                        keys[9] = 0;
                    } break;

                    case SDLK_Z:
                    {
                        keys[0xA] = 0;
                    } break;

                    case SDLK_C:
                    {
                        keys[0xB] = 0;
                    } break;

                    case SDLK_4:
                    {
                        keys[0xC] = 0;
                    } break;

                    case SDLK_R:
                    {
                        keys[0xD] = 0;
                    } break;

                    case SDLK_F:
                    {
                        keys[0xE] = 0;
                    } break;

                    case SDLK_V:
                    {
                        keys[0xF] = 0;
                    } break;


                    default:
                        break;
                }
                break;
            }
            default:
                break;
        }
    }





}
