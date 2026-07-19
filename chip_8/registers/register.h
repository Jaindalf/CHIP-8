#ifndef register_h
#define register_h
#include <stdint.h>
#include <stdbool.h>
//Clear a register
#ifdef __cplusplus
extern "C" {
#endif
void register_clear(uint8_t *reg);

//Set register to a value b/w 0x00 and  0xff
void register_set(uint8_t* reg,uint8_t value);
uint8_t register_read(const uint8_t* reg);

//Set a single bit of a register
void register_set_bit(uint8_t* reg, const int bit_num);
void register_clear_bit(uint8_t* reg, const int bit_num);
bool register_read_bit(const uint8_t* reg, const int bit_num);
void register_toggle_bit(uint8_t* reg, const int bit_num);
#ifdef __cplusplus
}
#endif

#endif
