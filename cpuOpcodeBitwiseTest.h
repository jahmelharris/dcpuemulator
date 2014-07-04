#ifndef CPUOPCODEBITWISETEST_H
#define CPUOPCODEBITWISETEST_H
#include "common.h"
#include "dcpu.h"

TEST(cpu_opcode_bitwise_test, AND_A_B_will_compute_A_and_B)
{
    const int arg1 = 0xAAFF;
    const int arg2 = 0x55FF;
    const int answer = 0x00FF;

    word memory[memorySize] = {0x0409};
    word reg[NUMBEROFREGISTERS] = {arg1, arg2};

    DCPU cpu(memory, reg);
    cpu.execute();

    ASSERT_TRUE(reg[A] == answer);
}

TEST(cpu_opcode_bitwise_test, BOR_A_B_will_compute_A_and_B)
{
    const int arg1 = 0xAAFF;
    const int arg2 = 0x55FF;
    const int answer = 0xFFFF;

    word memory[memorySize] = {0x040a};
    word reg[NUMBEROFREGISTERS] = {arg1, arg2};

    DCPU cpu(memory, reg);
    cpu.execute();

    ASSERT_TRUE(reg[A] == answer);
}

TEST(cpu_opcode_bitwise_test, XOR_A_B_will_compute_A_and_B)
{
    const int arg1 = 0xAAFF;
    const int arg2 = 0x55FF;
    const int answer = 0xFF00;

    word memory[memorySize] = {0x040b};
    word reg[NUMBEROFREGISTERS] = {arg1, arg2};

    DCPU cpu(memory, reg);
    cpu.execute();

    ASSERT_TRUE(reg[A] == answer);
}
#endif // CPUOPCODEBITWISETEST_H
