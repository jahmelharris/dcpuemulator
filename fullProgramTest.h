#ifndef FULLPROGRAMTEST_H
#define FULLPROGRAMTEST_H
#include "common.h"
#include "dcpu.h"




TEST(full_program_test,program_in_produces_correct_output)
{
    word prog[memorySize]  =
    {
     0x7c01, 0x0030, 0x7de1, 0x1000, 0x0020, 0x7803, 0x1000, 0xc00d,
     0x7dc1, 0x001a, 0xa861, 0x7c01, 0x2000, 0x2161, 0x2000, 0x8463,
     0x806d, 0x7dc1, 0x000d, 0x9031, 0x7c10, 0x0018, 0x7dc1, 0x001a,
     0x9037, 0x61c1, 0x7dc1, 0x001a, 0x0000, 0x0000, 0x0000, 0x0000
    };

    word reg[NUMBEROFREGISTERS] = {0};
    reg[SP] = 9999;
    DCPU cpu(prog, reg);
    while(reg[PC] < 26)
        cpu.execute();
    ASSERT_TRUE(reg[X] ==  0x40);

}

#endif // FULLPROGRAMTEST_H
