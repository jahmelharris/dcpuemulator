#ifndef CPUOPCODEIFTEST_H
#define CPUOPCODEIFTEST_H
#include "common.h"
#include "dcpu.h"

TEST(cpu_opcode_if_test, IFE_A_B_will_only_run_the_next_instruction_if_A_and_B_are_equal)
{
    const int arg1 = 0x0001;
    const int arg2 = 0x0001;
    int answer = 0x0002;

    word memory[memorySize] = {0x040c, 0x0401 , 0x0011};
    word reg[NUMBEROFREGISTERS] = {arg1, arg2};

    DCPU cpu(memory, reg);
    cpu.execute();
    ASSERT_TRUE(reg[PC] == answer-1);
    reg[PC] = 0;
    reg[B] = arg1+1;
    cpu.execute();
    ASSERT_TRUE(reg[PC] == answer);
}

TEST(cpu_opcode_if_test, IFN_A_B_will_only_run_the_next_instruction_if_A_and_B_are_not_equal)
{
    //IFN A B
    //  SET X, Y
    //SET Y, X
    const int arg1 = 0x0001;
    const int arg2 = 0x0000;
    const int answer = 0x0002;

    word memory[memorySize] = {0x040d, 0x0401 , 0x0011};
    word reg[NUMBEROFREGISTERS] = {arg1, arg2};
    DCPU cpu(memory, reg);
    cpu.execute();
    ASSERT_TRUE(reg[PC] == answer-1);
    reg[PC] = 0;
    reg[A] = arg1-1;    //make them equal
    cpu.execute();
    ASSERT_TRUE(reg[PC] == answer);
}

TEST(cpu_opcode_if_test, IFG_A_B_will_only_run_the_next_instruction_if_A_is_greater_than_B)
{
    const int arg1 = 0x0001;
    const int arg2 = 0x0000;
    const int answer = 0x0002;

    word memory[memorySize] = {0x040e, 0x0401 , 0x0011};
    word reg[NUMBEROFREGISTERS] = {arg1, arg2};

    DCPU cpu(memory, reg);
    cpu.execute();
    ASSERT_TRUE(reg[PC] == answer-1);
    reg[PC] = 0;
    reg[A] = arg1-1;
    cpu.execute();
    ASSERT_TRUE(reg[PC] == answer);
}

TEST(cpu_opcode_if_test, IFB_A_B_will_only_run_the_next_instruction_if_A_and_B_is_not_equal_to_0) //correct?
{
    const int arg1 = 0x00FF;
    const int arg2 = 0x0FF0;
    const int answer = 0x0002;

    word memory[memorySize] = {0x040f, 0x0401 , 0x0011};
    word reg[NUMBEROFREGISTERS] = {arg1, arg2};

    DCPU cpu(memory, reg);
    cpu.execute();
    ASSERT_TRUE(reg[PC] == answer-1);
    reg[PC] = 0;
    reg[B] = 0xFF00;
    cpu.execute();
    ASSERT_TRUE(reg[PC] == answer);
}


#endif // CPUOPCODEIFTEST_H
