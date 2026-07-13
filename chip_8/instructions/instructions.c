#include "instructions.h"
#include "registers/register.h"
//#include "chip_8.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

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
    chip->V[x] = sum & 0xFFu; //the operation must be done b/4 setting the flag because one of the operands  may be v[f]
    if (sum>255u) {
        chip->V[0xF]=1;

    }
    else {
        chip->V[0xF]=0;
    }

}

void ins_8xy5(chip_8 *chip) {
    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;

    uint8_t y=(chip->Opcode & 0x00F0u)>>4u;
   // printf("x:%x y:%x\n",x,y);
   // printf("V[x]:%x V[y]:%x\n",chip->V[x],chip->V[y]);
    bool f=(chip->V[x]>=chip->V[y]);

    chip->V[x] = chip->V[x]-chip->V[y];

    chip->V[0xF]=f;

}

void ins_8xy6(chip_8 *chip) {
    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;
    uint8_t y=(chip->Opcode & 0x00F0u)>>4u;

    bool r=register_read_bit(&chip->V[x],0);
    chip->V[x]>>=1;  //divide vx by 2

    if (r) {
        chip->V[0xF]=1;
    }
    else {
        chip->V[0xF]=0;
    }

}
//Possible bug
void ins_8xy7(chip_8 *chip) {
    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;
    uint8_t y=(chip->Opcode & 0x00F0u)>>4u;
    chip->V[x] = chip->V[y]-chip->V[x];
    if (chip->V[y]>chip->V[x]) {
        chip->V[0xF]=1;

    }
    else {
        chip->V[0xF]=0;
    }


}

void ins_8xyE(chip_8 *chip) {

    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;
    uint8_t y=(chip->Opcode & 0x00F0u)>>4u;

    bool r=register_read_bit(&chip->V[x],7);
    chip->V[x]<<=1;  //divide vx by 2
    if (r) {
        chip->V[0xF]=1;
    }
    else {
        chip->V[0xF]=0;
    }


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
    //sleep(5);
    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;


    if (chip->Keys[chip->V[x]]==1) {
        chip->PC+=2;
    }
}

void ins_ExA1(chip_8 *chip) {
    //sleep(5);
    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;
    if ((chip->Keys[chip->V[x]])==0) {
        chip->PC+=2;
    }
}

void ins_Fx07(chip_8 *chip) {
    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;
   chip->V[x] = chip->DelayTimer;
}

//Fx0A
void ins_Fx0A(chip_8 *chip) {
    sleep(5);
    printf("OPCODE: %x\n",chip->Opcode);
    printf("chip waiting for key flag:%d\n",chip->isWaitingForKeys);
   // sleep(3);
    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;
    printf("Value of x: %x\n",x);

    //Check if this is the first instance of encountering
    if (!chip->isWaitingForKeys) {

        memcpy(chip->PreviousKeys,chip->Keys,16);

        chip->isWaitingForKeys=true;
    }

    printf("Chip Keys:");
    for (int i = 0; i < 16; i++) {
        printf(" %x",chip->Keys[i]);
    }
    printf("\n");
    printf("Previous Keys:");
    for (int i = 0; i < 16; i++) {
        printf(" %x",chip->PreviousKeys[i]);
    }
    printf("\n");

    bool key_released=false;
    for (int i = 0; i < 16; i++) {
        if (chip->Keys[i] != chip->PreviousKeys[i]) {
            chip->V[x]=i;
            key_released=true;
            sleep(1);
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

void ins_altFx0A(chip_8 *chip) {
    uint8_t x=(chip->Opcode & 0x0F00u)>>8u;
    bool key_pressed=false;
    for (int i = 0; i < 16; i++) {
        if (chip->Keys[i]==1) {
            chip->V[x]=i;


            key_pressed=true;
           // sleep(20);
        }
    }
    if (key_pressed==false) {

        chip->PC-=2;
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

//---------------------------------------------------------------------//
void execute_opcode(chip_8 *chip)
{
    printf("OPCODE :%x\n",chip->Opcode);

    switch ((chip->Opcode & 0xF000) >> 12)
    {
        case 0x0:
            switch (chip->Opcode & 0x00FF)
            {
                case 0xE0: ins_00E0(chip); break;
                case 0xEE: ins_00EE(chip); break;
                default:   printf("Unknown opcode\n"); break;
            }
            break;

        case 0x1: ins_1nnn(chip); break;
        case 0x2: ins_2nnn(chip); break;
        case 0x3: ins_3xkk(chip); break;
        case 0x4: ins_4xkk(chip); break;
        case 0x5: ins_5xy0(chip); break;
        case 0x6: ins_6xkk(chip); break;
        case 0x7: ins_7xkk(chip); break;

        case 0x8:
            switch (chip->Opcode & 0x000F)
            {
                case 0x0: ins_8xy0(chip); break;
                case 0x1: ins_8xy1(chip); break;
                case 0x2: ins_8xy2(chip); break;
                case 0x3: ins_8xy3(chip); break;
                case 0x4: ins_8xy4(chip); break;
                case 0x5: ins_8xy5(chip); break;
                case 0x6: ins_8xy6(chip); break;
                case 0x7: ins_8xy7(chip); break;
                case 0xE: ins_8xyE(chip); break;
                default:  printf("Unknown opcode\n"); break;
            }
            break;

        case 0x9: ins_9xy0(chip); break;
        case 0xA: ins_Annn(chip); break;
        case 0xB: ins_Bnnn(chip); break;
        case 0xC: ins_Cxkk(chip); break;
        case 0xD: ins_Dxyn(chip); break;

        case 0xE:
            switch (chip->Opcode & 0x00FF)
            {
                case 0x9E: ins_Ex9E(chip); break;
                case 0xA1: ins_ExA1(chip); break;
                default:   printf("Unknown opcode\n"); break;
            }
            break;

        case 0xF:
            switch (chip->Opcode & 0x00FF)
            {
                case 0x07: ins_Fx07(chip); break;
                case 0x0A: ins_altFx0A(chip); break;
                case 0x15: ins_Fx15(chip); break;
                case 0x18: ins_Fx18(chip); break;
                case 0x1E: ins_Fx1E(chip); break;
                case 0x29: ins_Fx29(chip); break;
                case 0x33: ins_Fx33(chip); break;
                case 0x55: ins_Fx55(chip); break;
                case 0x65: ins_Fx65(chip); break;
                default:   printf("Unknown opcode\n"); break;
            }
            break;

        default:
            printf("Unknown opcode\n");
            break;
    }
}
