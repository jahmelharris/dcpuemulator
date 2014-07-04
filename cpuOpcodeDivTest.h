#ifndef CPUOPCODEDIVTEST_H
#define CPUOPCODEDIVTEST_H
#include "common.h"
#include "dcpu.h"

TEST(cpu_opcode_div_test, DIV_A_B_will_divide_A_and_B_for_legal_values_of_A_and_B)
{
    const int arg1 = 0x0020;
    const int arg2 = 0x0010;

    word memory[memorySize] = {0x0405};
    word reg[NUMBEROFREGISTERS] = {arg1, arg2};

    DCPU cpu(memory, reg);
    cpu.execute();

    ASSERT_TRUE(reg[A] == 0x0002);
}

//NOTE: Not sure what we're setting here. Remainder maybe?
TEST(cpu_opcode_div_test, DIV_A_B_will_set_overflow_flag_correctly)
{
    const int arg1 = 0x0010;
    const int arg2 = 0x0003;

    word memory[memorySize] = {0x0405};
    word reg[NUMBEROFREGISTERS] = {arg1, arg2};

    DCPU cpu(memory, reg);
    cpu.execute();

    ASSERT_TRUE(reg[O] == 0x5555);
}

TEST(cpu_opcode_div_test, DIV_A_0_will_set_A_and_overflow_flag_to_0)
{
    word memory[memorySize] = {0x0405};
    word reg[NUMBEROFREGISTERS] = {0x0000, 0x0000};

    DCPU cpu(memory, reg);
    cpu.execute();
    ASSERT_FALSE(reg[A]);
    ASSERT_FALSE(reg[O]);
}

#endif // CPUOPCODEDIVTEST_H
