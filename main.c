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
//----------------------------------------------------------------------------------------

#define TIMER_FREQ 60.0f
#define CPU_FREQ 500.0f



int main(int argc, char *argv[]) {

    const metadata mdata={"CHIP-8 EMU","0.0.1","com.emulator.chip-8"};
    // ReSharper disable once CppUseInternalLinkage
    sdl_vars sv={nullptr,nullptr,nullptr,{},mdata};
    config_vars cv={64,32,20,WHITE,BLACK,{1,8000,440,0,0}};
    chip_8 chip;

    float  timer_delta=(1/TIMER_FREQ)*1000;
    float cpu_delta=(1/CPU_FREQ)*1000;




    init_chip_8(&chip);
    chip_load_rom(&chip,argv[1]);
    if (!init_sdl(&sv,cv)) {
        printf("Failed sdl  init");
        return 0;
    }
    //Main loop
    bool isRunning=true;
    double now,frame_time,cpu_time;
    now=get_time_ms();
    frame_time=now;
    cpu_time=now;;

    while (isRunning) {

       // play_audio_stream(&sv);
        //get current
        now=get_time_ms();
        poll_Events(chip.Keys,&chip.state.Paused,&chip.state.NextInstruction,&(sv.event),&isRunning);



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
            while (now-cpu_time>=cpu_delta) {
                chip_cycle(&chip);


                cpu_time+=cpu_delta;


            }
        }




        while (now-frame_time>=timer_delta) {
            if (chip.DelayTimer>0) {
                chip.DelayTimer-=1;
            }

            if (chip.SoundTimer>0) {
                fill_audio_stream(&sv, &cv);
                control_audio_stream(&sv,&cv,1);
                chip.SoundTimer-=1;
            }

            else if (chip.SoundTimer==0) {
                control_audio_stream(&sv,&cv,0);

            }

            draw_buffer(chip.Display,&sv,&cv);
            frame_time+=timer_delta;
        }


    }


        quit_sdl(sv);






}


