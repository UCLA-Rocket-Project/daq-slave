#include "Register.h"
Register::Register(word a, word v): addr(a), val(v) {}

bool Register::operator<(Register& const rhs) {
    return addr < rhs.addr;
}

bool Register::operator>(Register& const rhs) {
    return addr > rhs.addr;
}