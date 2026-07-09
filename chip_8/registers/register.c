#include"register.h"
void register_clear(uint8_t *reg) {

    *reg = 0;
}
uint8_t register_read(const uint8_t* reg) {
    return *reg;
}

void register_set(uint8_t* reg,uint8_t value) {
    *reg = value;
}

void register_set_bit(uint8_t *reg, const int bit_num) {

    (*reg)=(*reg)|(1<<bit_num);

}

void register_clear_bit(uint8_t *reg, const int bit_num) {
    (*reg)=(*reg)&(~(1<<bit_num));
}

void register_toggle_bit(uint8_t* reg, const int bit_num) {
    (*reg)=(*reg)^(1<<bit_num);
}
bool register_read_bit(const uint8_t* reg, const int bit_num) {

    return ((*reg)>>bit_num)&1;
}