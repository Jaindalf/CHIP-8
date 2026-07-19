#include "video/video.h"
#include "event/event.h"
#include "chip_8/chip_8.h"
#include<stdio.h>
#include <stdlib.h>
#include <time.h>

#include "chip_8/instructions/instructions.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_sdl3.h"
#include "imgui/backends/imgui_impl_sdlrenderer3.h"


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
    config_vars cv={64,32,10,WHITE,BLACK,{1,8000,440,0,0}};
    chip_8 chip;

    float  timer_delta=(1/TIMER_FREQ)*1000;
    float cpu_delta=(1/CPU_FREQ)*1000;




    init_chip_8(&chip);
    chip_load_rom(&chip,argv[1]);
    if (!init_sdl(&sv,cv)) {
        printf("Failed sdl  init");
        return 0;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();

    // Setup scaling
    float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale);        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
    style.FontScaleDpi = main_scale;        // Set initial font scale. (in docking branch: using io.ConfigDpiScaleFonts=true automatically overrides this for every window depending on the current monitor)

    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForSDLRenderer(sv.window, sv.renderer);
    ImGui_ImplSDLRenderer3_Init(sv.renderer);



    //Main loop
    bool isRunning=true;
    double now,frame_time,cpu_time;
    now=get_time_ms();
    frame_time=now;
    cpu_time=now;

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
            setColor(&sv, cv.bg_color);
            SDL_RenderClear(sv.renderer);

            setColor(&sv, cv.fg_color);


            draw_buffer(chip.Display,&sv,&cv);

          //  setColor(&sv, cv.bg_color);

            bool show_demo_window=true;
            ImGui_ImplSDLRenderer3_NewFrame();
            ImGui_ImplSDL3_NewFrame();
            ImGui::NewFrame();
            ImGui::Begin("Another Window");//, &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            ImGui::End();
            ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
            ImGui::Render();
            SDL_SetRenderScale(sv.renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
            SDL_SetRenderDrawColorFloat(sv.renderer, clear_color.x, clear_color.y, clear_color.z, clear_color.w);
           // SDL_RenderClear(sv.renderer);
            ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), sv.renderer);
            SDL_RenderPresent(sv.renderer);

            frame_time+=timer_delta;
        }


    }


        quit_sdl(sv);






}


