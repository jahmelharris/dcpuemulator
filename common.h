#ifndef COMMON_H
#define COMMON_H

const int memorySize = 10000;
const int NUMBEROFREGISTERS = 11; //GP and Special registers
/*
struct word{
    unsigned char high;
    unsigned char low;
    int getValue(){return (high<<8)|low;}

    word& operator[](word x)
    {
        return *this;
    }//(high<<8)|low;}

    //These need to overflow to high when incrementing past low
    word& operator++()
    {
        ++low;
        return *this;
    }
    word operator++(int)
    {
        operator++();
        return *this;
    }
};*/

typedef unsigned short word; //this should be uint16_t


/*
inline bool operator==(const word& lhs, const word&rhs)
{
    return lhs.high == rhs.high && lhs.low == rhs.low;
}

inline bool operator!=(const word& lhs, const word&rhs)
{
    return !operator==(lhs,rhs);
}
*/


/*inline word operator&(const word& lhs, const word& rhs)
{
    word w;
    w.high = lhs.high & rhs.high;
    w.low = lhs.low & rhs.low;
    return w;
}*/

enum Opcodes{NONBASIC, SET, ADD, SUB, MUL, DIV, MOD, SHL, SHR, AND, BOR, XOR, IFE, IFN, IFG, IFB};
enum NonBasicOpcodes{JSR = 0x01};
enum GPRegisters{A = 0x00, B, C, X, Y, Z, I, J};
enum {PC=0x08,SP,O};
#endif // COMMON_H
