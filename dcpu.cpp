#include "dcpu.h"

DCPU::DCPU(word* memory, word* reg)
{
    m_memory = memory;
    m_register = reg;

}

DCPU::DCPU(word* memory)
{
    m_memory = memory;

    m_register = new word[NUMBEROFREGISTERS];
    for(int i=0;i<NUMBEROFREGISTERS;++i)
    {
        m_register[i] = 0;  //clear registers
    }

}

void DCPU::execute()
{

    unsigned char opcode, operandA, operandB = 0;
    word* src, *dst;

    decodeOpcode(m_memory[m_register[PC]], opcode, operandB, operandA);
    dst = setTarget(operandA,DST);
    src = setTarget(operandB,SRC);

    ++m_register[PC];

    switch(opcode)
    {
        case NONBASIC:
            switch(operandA)
            {
                case JSR:
                    m_memory[m_register[SP]--] = m_register[PC];
                    m_register[PC] = *src;
                break;
            }
        break;
        case SET:
            *dst = *src;
        break;
        case ADD:
            if((*dst + *src)>>16)   //if overflow
                m_register[O] = 1;
            else
                m_register[O] = 0;
            *dst += *src;
        break;
        case SUB:
            if((word)(*dst - *src)>*dst) //if underflow
                m_register[O] = 0xFFFF;
            else
                m_register[O] = 0;
            *dst -= *src;
        break;
        case MUL:
            m_register[O] = ((*dst * *src) >> 16) & 0xFFFF;
            *dst *= *src;
        break;
        case DIV:
            if(*src == 0)
                *dst = m_register[O] = 0;
            else
            {
                m_register[O] = ((*dst<<16) / *src)&0xFFFF;
                *dst /= *src;
            }
        break;
        case MOD:
            if(*src == 0)
                *dst = m_register[O] = 0;
            else
                *dst %= *src;
        break;
        case SHL:
            m_register[O] = ((*dst << *src)>>16)&0xFFFF;
            *dst <<= *src;
        break;
        case SHR:
            m_register[O] = ((*dst << 16)>>*src)&0xFFFF;
            *dst >>= *src;
        break;
        case AND:
            *dst &= *src;
        break;
        case BOR:
            *dst |= *src;
        break;
        case XOR:
            *dst ^= *src;
        break;
        case IFE:
        if(!(*dst == *src))
        {
            decodeOpcode(m_memory[m_register[PC]], opcode, operandB, operandA);
            setTarget(operandA,DST);
            setTarget(operandB,SRC);
            ++m_register[PC];   //skip next instruction if equal
        }
        break;
        case IFN:
            if(!(*dst != *src))
            {
                decodeOpcode(m_memory[m_register[PC]], opcode, operandB, operandA);
                setTarget(operandA,DST);
                setTarget(operandB,SRC);
                ++m_register[PC];   //skip next instruction if equal
            }
        break;
        case IFG:
            if(!(*dst > *src))
            {
                decodeOpcode(m_memory[m_register[PC]], opcode, operandB, operandA);
                setTarget(operandA,DST);
                setTarget(operandB,SRC);
                ++m_register[PC];   //skip next instruction if equal
            }
        break;
        case IFB:
            if((!(*dst & *src)!=0))
            {
                decodeOpcode(m_memory[m_register[PC]], opcode, operandB, operandA);
                setTarget(operandA,DST);
                setTarget(operandB,SRC);
                ++m_register[PC];   //skip next instruction if equal
            }
        break;
    }
}

word DCPU::getRegister(int registerName)
{
    return m_register[registerName];
}

void DCPU::setRegister(int registerName, word value)
{
    m_register[registerName] = value;
}

void DCPU::decodeOpcode(word w, unsigned char &opcode, unsigned char &src, unsigned char &dst)
{
    opcode = w & 0xF;
    //dst = (w.high & w.low) & 0x3F0;
    dst = (w >> 4) & 0x3F;
    src = (w >> 10) & 0x3F;
}

word* DCPU::setTarget(unsigned char operand, target t)
{
    //register
    if(operand <= 0x07)
        return &m_register[operand];
    //[register]
    else if(operand <=0x0f)
    {
        int val = (m_register[operand%8]);
        return &m_memory[val];
    }
    //[next word+register]
    else if(operand <=0x17)
    {
        return &m_memory[m_memory[(++m_register[PC])]+(m_register[operand%8])];
    }
    //pop
    else if (operand == 0x18)
    {
        ++m_register[SP];
        return &m_memory[m_register[SP]];
    }
    //peek
    else if(operand == 0x19)
    {
        return &m_memory[m_register[SP]];
    }
    //push
    else if (operand == 0x1a)//TODO:Fix
    {
        word* ret = &m_memory[m_register[SP]];
        --m_register[SP];
        return ret;
    }
    //PC
    else if(operand == 0x1c)
    {
        return &m_register[PC];
    }
    //Overflow
    else if(operand == 0x1d)
    {
        return &m_register[O];
    }
    else if(operand == 0x1e)    //TODO:add test for this
    {
        return &m_memory[m_memory[(++m_register[PC])]];
    }
    //next word (literal)
    else if(operand == 0x1f)
    {
        return &m_memory[(++m_register[PC])];
    }
    else if(operand <=0x3f) //TODOL add test for this
    {
        literal = operand - 0x20;
        return &literal;
    }

    else
        return 0;
}
