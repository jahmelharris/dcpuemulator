#ifndef CPUOPCODESUBTEST_H
#define CPUOPCODESUBTEST_H
#include "common.h"
#include "dcpu.h"

TEST(cpu_opcode_sub_test, SUB_A_B_will_compute_A_minus_B)
{
    const int arg1 = 0x0030;
    const int arg2 = 0x0020;

    word memory[memorySize] = {0x0403};
    word reg[NUMBEROFREGISTERS] = {arg1, arg2};

    DCPU cpu(memory, reg);
    cpu.execute();

    ASSERT_TRUE(reg[A] == arg1-arg2);
}

TEST(cpu_opcode_sub_test, SUB_A_B_where_B_is_larger_than_A_will_result_in_an_underflow_setting_the_underflow_flag_to_oxffff)
{
    const int arg1 = 0x0001;
    const int arg2 = 0x0002;

    word memory[memorySize] = {0x0403};
    word reg[NUMBEROFREGISTERS] = {arg1, arg2};

    DCPU cpu(memory, reg);
    cpu.execute();

    ASSERT_TRUE(reg[O] == 0xffff);
}

TEST(cpu_opcode_sub_test, SUB_A_B_where_B_is_smaller_than_A_will_set_the_underflow_flag_to_0)
{

    const int arg1 = 0x0002;
    const int arg2 = 0x0001;

    word memory[memorySize] = {0x0403};
    word reg[NUMBEROFREGISTERS] = {arg1, arg2};
    reg[O] = 0xFFFF;
    DCPU cpu(memory, reg);
    cpu.execute();

    ASSERT_TRUE(reg[O] == 0);
}

#endif // CPUOPCODESUBTEST_H
