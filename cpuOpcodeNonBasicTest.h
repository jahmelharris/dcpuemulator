#ifndef CPUOPCODENONBASICTEST_H
#define CPUOPCODENONBASICTEST_H
#include "common.h"
#include "dcpu.h"

TEST(cpu_opcode_non_basic_test, JSR_A_will_put_the_address_of_the_next_instruction_on_the_stack_then_run_the_instruction_at_A)
{

    int answer = 0x0001;

    word memory[memorySize] = {0x0010};
    word reg[NUMBEROFREGISTERS] = {0x000f};
    reg[SP] = 0xFF;

    DCPU cpu(memory, reg);
    cpu.execute();

    ASSERT_TRUE(memory[reg[SP]+1] == answer);
    answer = 0x000f;
    ASSERT_TRUE(reg[PC] == answer);

}

#endif
