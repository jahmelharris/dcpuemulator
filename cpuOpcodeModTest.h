#ifndef CPUOPCODESMODTEST_H
#define CPUOPCODESMODTEST_H
#include "common.h"
#include "dcpu.h"

TEST(cpu_opcode_mod_test, MOD_A_B_will_calculate_A_MOD_B)
{
    const int arg1 = 0x0006;
    const int arg2 = 0x0005;
    const int answer = 0x0001;

    word memory[memorySize] = {0x0406};
    word reg[NUMBEROFREGISTERS] = {arg1, arg2};

    DCPU cpu(memory, reg);
    cpu.execute();

    ASSERT_TRUE(reg[A] == answer);
}

TEST(cpu_opcode_mod_test, MOD_A_0_set_A_to_0)
{
    const int arg1 = 0x0006;
    const int arg2 = 0x0000;
    const int answer = 0x0000;

    word memory[memorySize] = {0x0406};
    word reg[NUMBEROFREGISTERS] = {arg1, arg2};

    DCPU cpu(memory, reg);
    cpu.execute();

    ASSERT_TRUE(reg[A] == answer);
}
#endif // CPUOPCODESMODTEST_H
