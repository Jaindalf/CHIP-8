#include "instructions.h"
#include "registers/register.h"
//#include "chip_8.h"
#include <stdlib.h>
#include <time.h>

#include "memory.h"




void ins_00E0(chip_8 *chip) {
    //Clear the display
    memset(chip->Display,0,sizeof(chip->Display));
}
void ins_00EE(chip_8 *chip) {
    chip->SP--;
    chip->PC=chip->Stack[chip->SP];

}

void ins_1nnn(chip_8 *chip) {
    chip->PC=(chip->Opcode&0x0FFFu);
}

void ins_2nnn(chip_8 *chip) {
    chip->Stack[chip->SP]=chip->PC;
    chip->SP++;
    chip->PC=(chip->Opcode&0x0FFFu);
}

void ins_3xkk(chip_8 *chip) {

    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;
    uint8_t kk=(chip->Opcode & 0x00FFu);

    if (chip->V[x] == kk) {
        chip->PC+=2;
    }
}

void ins_4xkk(chip_8 *chip) {

    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;
    uint8_t kk=(chip->Opcode & 0x00FFu);

    if (chip->V[x] != kk) {
        chip->PC+=2;
    }
}

void ins_5xy0(chip_8 *chip) {
    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;
    uint8_t y=(chip->Opcode & 0x00F0u)>>4u;
    if (chip->V[x] == chip->V[y]) {
        chip->PC+=2;
    }

}

void ins_6xkk(chip_8 *chip) {
    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;
    uint8_t kk=(chip->Opcode & 0x00FFu);

    chip->V[x] = kk;

}

void ins_7xkk(chip_8 *chip) {
    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;
    uint8_t kk=(chip->Opcode & 0x00FFu);

    chip->V[x] =chip->V[x]+ kk;
}

void ins_8xy0(chip_8 *chip) {
    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;
    uint8_t y=(chip->Opcode & 0x00F0u)>>4u;
    chip->V[x] = chip->V[y];
}

void ins_8xy1(chip_8 *chip) {
    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;
    uint8_t y=(chip->Opcode & 0x00F0u)>>4u;
    chip->V[x] = chip->V[x]|chip->V[y];
}
void ins_8xy2(chip_8 *chip) {
    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;
    uint8_t y=(chip->Opcode & 0x00F0u)>>4u;
    chip->V[x] = chip->V[x]& chip->V[y];
}
void ins_8xy3(chip_8 *chip) {
    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;
    uint8_t y=(chip->Opcode & 0x00F0u)>>4u;
    chip->V[x] = chip->V[x]^chip->V[y];
}

void ins_8xy4(chip_8 *chip) {
    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;
    uint8_t y=(chip->Opcode & 0x00F0u)>>4u;
    uint16_t sum =chip->V[x]+chip->V[y];
    if (sum>255u) {
        chip->V[0xF]=1;

    }
    else {
        chip->V[0xF]=0;
    }
    chip->V[x] = sum & 0xFFu;
}

void ins_8xy5(chip_8 *chip) {
    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;
    uint8_t y=(chip->Opcode & 0x00F0u)>>4u;
    if (chip->V[x]>chip->V[y]) {
        chip->V[0xF]=1;

    }
    else {
        chip->V[0xF]=0;
    }
    chip->V[x] = chip->V[x]-chip->V[y];

}

void ins_8xy6(chip_8 *chip) {
    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;
    uint8_t y=(chip->Opcode & 0x00F0u)>>4u;

    bool r=register_read_bit(&chip->V[x],0);
    if (r) {
        chip->V[0xF]=1;
    }
    else {
        chip->V[0xF]=0;
    }
    chip->V[x]>>=1;  //divide vx by 2

}
void ins_8xy7(chip_8 *chip) {
    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;
    uint8_t y=(chip->Opcode & 0x00F0u)>>4u;
    if (chip->V[y]>chip->V[x]) {
        chip->V[0xF]=1;

    }
    else {
        chip->V[0xF]=0;
    }
    chip->V[x] = chip->V[y]-chip->V[x];

}

void ins_8xyE(chip_8 *chip) {
    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;
    uint8_t y=(chip->Opcode & 0x00F0u)>>4u;

    bool r=register_read_bit(&chip->V[x],7);
    if (r) {
        chip->V[0xF]=1;
    }
    else {
        chip->V[0xF]=0;
    }
    chip->V[x]<<=1;  //divide vx by 2

}

void ins_9xy0(chip_8 *chip) {
    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;
    uint8_t y=(chip->Opcode & 0x00F0u)>>4u;
    if (chip->V[x] != chip->V[y]) {
        chip->PC+=2;
    }

}
void ins_Annn(chip_8 *chip) {
    chip->IR=(chip->Opcode&0x0FFFu);
}

void ins_Bnnn(chip_8 *chip) {
    chip->PC=(chip->Opcode&0x0FFFu)+chip->V[0];
}

void ins_Cxkk(chip_8 *chip) {
    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;
    uint8_t kk=(chip->Opcode & 0x00FFu);
    srand(time(nullptr));
    uint8_t random_byte = (rand() % (255 - 0 + 1)) + 0;

    chip->V[x] = random_byte & kk;
}

//to do Dxyn

void ins_Dxyn(chip_8 *chip) {
    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;
    uint8_t y=(chip->Opcode & 0x00F0u)>>4u;
    uint8_t n=chip->Opcode & 0x000Fu;

    uint8_t xPos=chip->V[x]%64;
    uint8_t yPos=chip->V[y]%32;

    //maybe
    chip->V[0xF] = 0;
    for (int i=0;i<n;i++) {
        uint8_t spriteRow=chip->RAM[(chip->IR)+i];
        //Since each row is only 1 byte
        for (int j=0;j<8;j++) {

            bool spritePixel = (spriteRow & (0x80 >> j)) != 0;

            if (!spritePixel) {
                continue;
            }
            uint8_t px = (xPos + j) % 64;
            uint8_t py = (yPos + i) % 32;

            if (chip->Display[px][py])
                chip->V[0xF] = 1;

            chip->Display[px][py] ^= 1;
        }
    }
}

void ins_Ex9E(chip_8 *chip) {
    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;
    if (chip->Keys[chip->V[x]]) {
        chip->PC+=2;
    }
}

void ins_ExA1(chip_8 *chip) {
    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;
    if (!(chip->Keys[chip->V[x]])) {
        chip->PC+=2;
    }
}

void ins_Fx07(chip_8 *chip) {
    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;
   chip->V[x] = chip->DelayTimer;
}

//Fx0A
void ins_Fx0A(chip_8 *chip) {
    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;

    //Check if this is the first instance of encountering
    if (!chip->isWaitingForKeys) {
        memcpy(chip->PreviousKeys,chip->Keys,16);
        chip->isWaitingForKeys=true;
    }

    bool key_released=false;
    for (int i = 0; i < 16; i++) {
        if (chip->Keys[i] != chip->PreviousKeys[i]) {
            chip->V[x]=i;
            key_released=true;
            break;
        }
    }
    //update the prevkeys for the next cycle
    memcpy(chip->PreviousKeys,chip->Keys,16);

    if (!key_released) {
        chip->PC-=2;
    }
    else {
        chip->isWaitingForKeys=false;
    }
}




void ins_Fx15(chip_8 *chip) {
    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;
    chip->DelayTimer=chip->V[x];
}

void ins_Fx18(chip_8 *chip) {
    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;
    chip->SoundTimer=chip->V[x];
}

void ins_Fx1E(chip_8 *chip) {
    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;
    chip->IR+=chip->V[x];
}

//Fx29
void ins_Fx29(chip_8 *chip) {
    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;
    uint8_t digit=chip->V[x];
    chip->IR=0x50+(digit*5);
}




void ins_Fx33(chip_8 *chip) {
    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;
    uint8_t v=chip->V[x];

    //ones place
    for (int i=2;i>=0;i--) {
        chip->RAM[(chip->IR)+i]=v%10;
        v/=10;
    }

}

void ins_Fx55(chip_8 *chip) {
    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;
    for (int i=0;i<=x;i++) {
        chip->RAM[chip->IR+i]=chip->V[i];
    }

}

void ins_Fx65(chip_8 *chip) {
    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;
    for (int i=0;i<=x;i++) {
        chip->V[i]=chip->RAM[chip->IR+i];
    }

}