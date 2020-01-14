#ifndef MODBUS_REGISTER
#define MODBUS_REGISTER
#include <stdint.h>

class Register { 
public:    
    uint16_t addr;
    uint16_t val;
    Register(uint16_t a, uint16_t v = 0): addr(a), val(v) {}
};
#endif