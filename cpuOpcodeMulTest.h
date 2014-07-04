#ifndef CPUOPCODESMULTEST_H
#define CPUOPCODESMULTEST_H
#include "common.h"
#include "dcpu.h"

TEST(cpu_opcode_mul_test, MUL_A_B_will_multiply_A_and_B)
{
    const int arg1 = 0x0010;
    const int arg2 = 0x0020;

    word memory[memorySize] = {0x0404};
    word reg[NUMBEROFREGISTERS] = {arg1, arg2};

    DCPU cpu(memory, reg);
    cpu.execute();

    ASSERT_TRUE(reg[A] == arg1*arg2);
}

TEST(cpu_opcode_mul_test, MUL_A_B_will_set_overflow_flag_to_overflown_word_if_overflow_occurs)
{
    const int arg1 = 0xFFFF;
    const int arg2 = 0x0005;

    word memory[memorySize] = {0x0404};
    word reg[NUMBEROFREGISTERS] = {arg1, arg2};

    DCPU cpu(memory, reg);
    cpu.execute();

    ASSERT_TRUE(reg[O] == 0x0004);
}


TEST(cpu_opcode_mul_test, MUL_A_B_of_small_values_will_set_the_overflow_flag_to_false)
{
    const int arg1 = 0x00FF;
    const int arg2 = 0x0001;

    word memory[memorySize] = {0x0404};
    word reg[NUMBEROFREGISTERS] = {arg1, arg2};
    reg[O] = 1;
    DCPU cpu(memory, reg);
    cpu.execute();

    ASSERT_TRUE(reg[O] == 0);
}

#endif // CPUOPCODESMULTEST_H
