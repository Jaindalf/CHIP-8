#include "video/video.h"
#include "event/event.h"
#include "chip_8/chip_8.h"
#include<stdio.h>
#include <stdlib.h>
#include <time.h>

#include "instructions/instructions.h"

void chip_cycle(chip_8 *chip) {
    chip_get_opcode(chip);
    execute_opcode(chip);


}

double get_time_ms(void) {
    struct timespec ts;
    // CLOCK_MONOTONIC represents absolute elapsed time since an arbitrary point
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec * 1000.0 + (double)ts.tv_nsec / 1000000.0;
}
//-----------------------------GLOBALS------------------------------------------------
const metadata mdata={"CHIP-8 EMU","0.0.1","com.emulator.chip-8"};
sdl_vars sv={nullptr,nullptr,{},mdata};
config_vars cv={64,32,10,WHITE,BLACK};
chip_8 chip;
//----------------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
    init_chip_8(&chip);
    chip_load_rom(&chip,argv[1]);
    if (!init_sdl(&sv,cv)) {
        printf("Failed sdl  init");
        return 0;
    }
    //Main loop
    bool isRunning=true;
    double st,pt,cpu_clock;
    st=get_time_ms();
    pt=st;
    cpu_clock=st;;
    printf("%lf st time",st);
    while (isRunning) {

        //get current
        st=get_time_ms();
        poll_Events(chip.Keys,&chip.state.Paused,&chip.state.NextInstruction,&(sv.event),&isRunning);

        //Delay for 1/60s
        //SDL_Delay(atoi(argv[2]));

        if (chip.state.Paused) {
            if (chip.state.NextInstruction) {
                chip_cycle(&chip);
                chip.state.NextInstruction=false;

            }
            else {
                continue;
            }
        }
        //CHIP-8 CYCLE
        //get opcode
        else {
            while (st-cpu_clock>=2) {
                chip_cycle(&chip);
                cpu_clock+=2;
            }
        }

        //DRAW BUFFER
        //only run if delta_time=1/60sec
        while (st-pt>=16.666) {
            if (chip.DelayTimer>0) {
                chip.DelayTimer-=1;
            }

            if (chip.SoundTimer>0) {
                chip.SoundTimer-=1;
            }
            draw_buffer(chip.Display,&sv,&cv);
            pt+=16.666;
        }


    }


        quit_sdl(sv);






}