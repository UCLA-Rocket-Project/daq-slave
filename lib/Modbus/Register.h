#ifndef MODBUS_REGISTER
#define MODBUS_REGISTER
#include <stdint.h>
#define word uint16_t

class Register { 
public:    
    word addr;
    word val;
    Register(word a, word v = 0);
    bool operator < (const Register& rhs) const;
    bool operator > (const Register& rhs) const;
};
#undef word
#endif