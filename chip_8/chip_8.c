#include "chip_8.h"

#include <stdio.h>
#include <stdlib.h>

#include "registers/register.h"
#define FONTSET_SIZE  80

uint8_t fontset[FONTSET_SIZE] =
{
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};



void init_chip_8(chip_8* chip) {
    //Set all registers to zero
    for (int i = 0; i < 16; i++) {
        register_clear(&chip->V[i]);
    }

    //Set Ram to zero
    for (int i = 0; i < 4096; i++) {
        chip->RAM[i]=0;
    }
    //Set pc
    chip->PC=START_ADDRESS;

    //Load font set
    for (unsigned int i = 0; i < FONTSET_SIZE; i++) {
        chip->RAM[0x50+i]=fontset[i];
    }

    //set display buffer to zero
    for (unsigned int i = 0; i < 64; i++) {
        for (unsigned int j = 0; j < 32; j++) {chip->Display[i][j]=0;}
    }

    //set keypad to zero
    for (int i = 0; i < 16; i++) {
        chip->Keys[i]=false;
        chip->PreviousKeys[i]=false;
    }


    //for waiting key release opcode
    chip->isWaitingForKeys=false;
    //set timers
    chip->DelayTimer=chip->SoundTimer=chip->Opcode=0;
    chip->state.Paused=false;
    chip->state.NextInstruction=false;
}

void chip_load_rom(chip_8 *chip,const char *rom_name) {
    FILE *fp = fopen(rom_name, "rb");
    if (!fp) {
        perror("Failed to open ROM");
        return;
    }

    // Move file pointer to the end
    if (fseek(fp, 0, SEEK_END) != 0) {
        perror("Failed to seek to end");
        fclose(fp);
        return;
    }

    long int size = ftell(fp);
    if (size < 0) {
        perror("Failed to determine file size");
        fclose(fp);
        return;
    }

    // Return to the beginning of the file
    if (fseek(fp, 0, SEEK_SET) != 0) {
        perror("Failed to seek to start");
        fclose(fp);
        return;
    }

    // Allocate memory safely on the heap instead of the stack
    unsigned char *buffer = malloc(size);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(fp);
        return;
    }

    // Read the file data into the heap buffer
    size_t bytes_read = fread(buffer, 1, size, fp);
    if (bytes_read < (size_t)size) {
        if (ferror(fp)) {
            perror("Error reading file");
        }
    }

    // Clean up file handle
    fclose(fp);

    /* --- Process your ROM data here --- */
    if (size>(4096-512)) {
        perror("ROM TOO BIG TO FIT INTO CHIP-8");
    }

    for (int i=0; i<size; i++) {
        chip->RAM[START_ADDRESS+i]=buffer[i];
        //printf("Index: %d Instruction:%x\n",(i+1),buffer[i]);
    }

    chip->PC=START_ADDRESS;

    // Always free heap memory when finished
    free(buffer);
}

void chip_get_opcode(chip_8 *chip){

// Do some out-of-bounds checking
   if(chip->PC<0x200 ||(chip->PC+1)>=4096){
       printf("Opcode fetch outside RAM at PC = 0x%03X\n", chip->PC);
	//	return;
   }

	uint16_t high_byte=chip->RAM[chip->PC];
	uint16_t low_byte=chip->RAM[chip->PC +1];
	chip->Opcode=(high_byte<<8u)|low_byte;

	chip->PC+=2;

}
