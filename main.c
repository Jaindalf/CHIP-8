#include "video/video.h"
#include "event/event.h"
#include<stdio.h>
int main(){
    const metadata mdata={"CHIP-8 EMU","0.0.1","com.emulator.chip-8"};
    sdl_vars sv={NULL,NULL,{},mdata};
    config_vars cv={64,32,10,WHITE,BLACK};
    bool buf[64][32];

    bool keys[0xF];
    for(int i=0;i<0xF;i++) {
        keys[i]=false;
    }


    for (int i=0;i<64;i++) {
        for (int j=0;j<32;j++) {
            if (i%4==0 && j%2==0) {
                buf[i][j]=1;
            }
            else {
                buf[i][j]=0;
            }
        }
    }

    if (!init_sdl(&sv,cv)) {
        printf("Failed sdl  init");
        return 0;
    }
    //Main loop
    bool isRunning=true;
    while (isRunning) {
        //Delay for 1/60s
        SDL_Delay(1000/60);

        //Get input event and set keys[]
        poll_Events(keys,&(sv.event),&isRunning);

        //CHIP-8 CYCLE


        //DRAW BUFFER
        draw_buffer(buf,&sv,&cv);
    }




    quit_sdl(sv);





}
