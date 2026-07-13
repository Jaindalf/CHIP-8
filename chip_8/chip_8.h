#ifndef chip_8_h
#define chip_8_h
#include <stdint.h>
#include<stdbool.h>
typedef struct  {
	bool Paused;
	bool NextInstruction;

}chip_8_state;
typedef struct  {
    uint8_t V[16]; //16 8 bit registers
    uint8_t RAM[4096]; //4096 bytes of memory
    uint16_t IR ; //Index register(holds address of RAM to be used)
    uint16_t PC ; //Program counter(holds address of next instruction to be executed)
    uint16_t Stack[16]; //16 level stack(each value holds the PC value when a call was executed)
    uint8_t SP; //Stack pointer(holds index of the topmost stack element)
    uint8_t DelayTimer;
    uint8_t SoundTimer;
    bool Keys[16]; //input keys
	//specially for release key instruction
	bool PreviousKeys[16];
	bool isWaitingForKeys;
	//
    bool Display[64][32];
	uint16_t Opcode; //Current instruction chip_8 is to be executing.
	chip_8_state state;

}chip_8;




#define START_ADDRESS 0x200



void init_chip_8(chip_8* chip);
void chip_load_rom(chip_8 *chip,char const *rom_name);
void chip_get_opcode(chip_8 *chip);

#endif
