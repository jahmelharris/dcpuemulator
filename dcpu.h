#ifndef DCPU_H
#define DCPU_H
#include "common.h"
class DCPU
{
public:
    //DCPU();
    DCPU(word*, word*);
    DCPU(word*);
    void execute();
    word getRegister(int);
    void setRegister(int registerName, word value);

private:
    enum target{SRC,DST};
    word* m_memory;
    word* m_register;//[NUMBEROFREGISTERS];
    void decodeOpcode(word w, unsigned char &opcode, unsigned char &src, unsigned char &dst);
    word* setTarget(unsigned char, target);
    word literal;

};

#endif // DCPU_H
