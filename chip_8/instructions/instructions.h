#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
#include "chip_8.h"

/* System Instructions */

#ifdef __cplusplus
extern "C" {
#endif

void ins_00E0(chip_8 *chip);
void ins_00EE(chip_8 *chip);

/* Jump / Call */
void ins_1nnn(chip_8 *chip);
void ins_2nnn(chip_8 *chip);

/* Skip Instructions */
void ins_3xkk(chip_8 *chip);
void ins_4xkk(chip_8 *chip);
void ins_5xy0(chip_8 *chip);
void ins_9xy0(chip_8 *chip);

/* Load / Arithmetic */
void ins_6xkk(chip_8 *chip);
void ins_7xkk(chip_8 *chip);

void ins_8xy0(chip_8 *chip);
void ins_8xy1(chip_8 *chip);
void ins_8xy2(chip_8 *chip);
void ins_8xy3(chip_8 *chip);
void ins_8xy4(chip_8 *chip);
void ins_8xy5(chip_8 *chip);
void ins_8xy6(chip_8 *chip);
void ins_8xy7(chip_8 *chip);
void ins_8xyE(chip_8 *chip);

/* Index / Jump */
void ins_Annn(chip_8 *chip);
void ins_Bnnn(chip_8 *chip);

/* Random */
void ins_Cxkk(chip_8 *chip);

/* Display */
void ins_Dxyn(chip_8 *chip);

/* Keyboard */
void ins_Ex9E(chip_8 *chip);
void ins_ExA1(chip_8 *chip);

/* Timers */
void ins_Fx07(chip_8 *chip);
void ins_Fx15(chip_8 *chip);
void ins_Fx18(chip_8 *chip);

/* Index Register */
void ins_Fx1E(chip_8 *chip);
void ins_Fx29(chip_8 *chip);

/* Input */
void ins_Fx0A(chip_8 *chip);

/* Memory */
void ins_Fx33(chip_8 *chip);
void ins_Fx55(chip_8 *chip);
void ins_Fx65(chip_8 *chip);
void execute_opcode(chip_8 *chip);
void ins_altFx0A(chip_8 *chip);

#ifdef __cplusplus
}
#endif
#endif /* INSTRUCTIONS_H */
