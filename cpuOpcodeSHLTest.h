#ifndef CPUOPCODESHLTEST_H
#define CPUOPCODESHLTEST_H
#include "common.h"
#include "dcpu.h"

TEST(cpu_opcode_shl_test, SHL_A_B_will_calculate_A_left_shifted_B_bits)
{
    const int arg1 = 0x0001;
    const int arg2 = 0x0004;
    const int answer = 0x0010;

    word memory[memorySize] = {0x0407};
    word reg[NUMBEROFREGISTERS] = {arg1, arg2};

    DCPU cpu(memory, reg);
    cpu.execute();

    ASSERT_TRUE(reg[A] == answer);
}

TEST(cpu_opcode_shl_test, SHL_A_B_will_set_the_overflow_flag_to_overflow_result_when_using_large_values_of_A_or_B)
{
    const int arg1 = 0xFFFF;
    const int arg2 = 0x0004;
    const int answer = 0x000F;

    word memory[memorySize] = {0x0407};
    word reg[NUMBEROFREGISTERS] = {arg1, arg2};

    DCPU cpu(memory, reg);
    cpu.execute();
    ASSERT_TRUE(reg[O] == answer);

}
     #endif // CPUOPCODESHLTEST_H
