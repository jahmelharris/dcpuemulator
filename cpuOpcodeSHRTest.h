#ifndef CPUOPCODERHLTEST_H
#define CPUOPCODERHLTEST_H
#include "common.h"
#include "dcpu.h"

TEST(cpu_opcode_shr_test, SHR_A_B_will_calculate_A_right_shifted_B_bits)
{
    const int arg1 = 0x0010;
    const int arg2 = 0x0004;
    const int answer = 0x0001;

    word memory[memorySize] = {0x0408};
    word reg[NUMBEROFREGISTERS] = {arg1, arg2};

    DCPU cpu(memory, reg);
    cpu.execute();

    ASSERT_TRUE(reg[A] == answer);
}

TEST(cpu_opcode_shr_test, SHR_A_B_will_set_the_overflow_flag_value_shifted_past_end_of_word)
{
    const int arg1 = 0xFFFF;
    const int arg2 = 0x0004;
    const int answer = 0xF000;

    word memory[memorySize] = {0x0408};
    word reg[NUMBEROFREGISTERS] = {arg1, arg2};

    DCPU cpu(memory, reg);
    cpu.execute();
    ASSERT_TRUE(reg[O] == answer);
}
#endif // CPUOPCODERHLTEST_H
