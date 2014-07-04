//TODO: These tests should be split into SET tests and src/dst tests

#ifndef CPUTESTS_H
#define CPUTESTS_H

#include "common.h"
#include "dcpu.h"

TEST(cpu_test,given_memory_containing_SET_A_Literal_opcode_register_A_will_contain_the_value_of_the_literal)
{
    word memory[memorySize] = {0x7c01, 0x0030};
    DCPU cpu(memory);
    cpu.execute();
    word val = cpu.getRegister(A);
    ASSERT_TRUE(val== memory[1]);
}

TEST(cpu_test,given_memory_containing_SET_A_B_opcode_register_A_will_contain_the_value_of_B)
{
    word memory[memorySize] = {0x0401};
    DCPU cpu(memory);
    cpu.execute();
    ASSERT_TRUE(cpu.getRegister(A) == cpu.getRegister(B));
}

TEST(cpu_test,given_memory_containing_SET_A_BPointer_opcode_register_A_will_contain_the_value_at_memory_location_B)
{
    word memory[memorySize] = {0x2401, 0xFFFF};
    word pointer = {0x00f0};
    DCPU cpu(memory);
    cpu.setRegister(B,pointer);
    cpu.execute();
    ASSERT_TRUE(cpu.getRegister(A) == memory[0xf]);
}

TEST(cpu_test,given_memory_containing_SET_LITERALPlusRegisterPointer_Register_opcodes_LITERALPlusRegister_memory_location_will_equal_register)
{
    //SET [0x2000+A], B
    word value = {0x000f};
    word memory[memorySize] = {0x0501, 0x0200};
    DCPU cpu(memory);
    cpu.setRegister(A,value);   //A = 0x000f
    value = 0x1234;
    cpu.setRegister(B,value);   //B = 0x1245
    cpu.execute();
    ASSERT_TRUE(memory[memory[1]+0x0f] == 0x1234);
}

//SET X, POP
TEST(cpu_test, given_memory_containing_SET_A_POP_and_data_pushed_onto_the_stack_then_excuting_the_cpu_will_put_the_pushed_data_into_A)
{
    word memory[memorySize] = {0x6001};
    word reg[NUMBEROFREGISTERS] = {0};
    memory[9999] = 0x1234;
    reg[SP] = 9998;
    DCPU cpu(memory,reg);
    cpu.execute();

    ASSERT_TRUE(reg[A]== 0x1234);
    ASSERT_TRUE(reg[SP] == 9999);
}

TEST(cpu_test,given_memory_containing_SET_A_PEEK_the_data_at_SP_should_be_placed_in_A)
{
    word memory[memorySize] = {0x6401};
    memory[9999] = 0x1234;
    word reg[NUMBEROFREGISTERS] = {0};
    reg[SP] = 9999;
    DCPU cpu(memory, reg);
    cpu.execute();
    ASSERT_TRUE(reg[A] == memory[9999]);
}


TEST(cpu_test, given_memory_containing_SET_PUSH_A_the_data_in_A_should_be_put_onto_the_stack)
{
    word memory[memorySize] = {0x01A1};
    word reg[NUMBEROFREGISTERS] = {0};

    reg[A] = 0x1234;
    reg[SP] = 9999;

    DCPU cpu(memory, reg);
    cpu.execute();

    ASSERT_TRUE(reg[A] == memory[9999]);
    ASSERT_TRUE(reg[SP] == 9998);
}

TEST(cpu_test, given_memory_containing_SET_PC_A_the_value_in_A_should_be_put_into_register_PC)
{
    word memory[memorySize] = {0x01C1};
    word reg[NUMBEROFREGISTERS] = {0};
    reg[A] = 0x1234;

    DCPU cpu(memory, reg);// = DCPU(memory, reg);
    cpu.execute();
    ASSERT_TRUE(reg[PC] == reg[A]);
}

TEST(cpu_test, given_memory_containing_SET_A_O_the_value_of_O_will_be_put_in_register_A)
{
    word memory[memorySize] = {0x01D1};
    word reg[NUMBEROFREGISTERS] = {0};
    reg[O] = 1;
    DCPU cpu(memory, reg);// = DCPU(memory, reg);
    cpu.execute();
    ASSERT_TRUE(reg[O] == reg[A]);
}

#endif // CPUTESTS_H
