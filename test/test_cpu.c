#include "unity.h"

#include <libnes/cpu.h>

#include <stdbool.h>

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

const uint8_t CPU_PROCESSOR_STATUS_UNSET = 0b00000000;

void test_0xa9_lda_immediate_load_data(void)
{
    uint8_t program[3] = { 0xa9, 0x05, 0x00 };

    struct cpu* cpu = cpu_init();
    bool finished = cpu_interpret(cpu, program);

    TEST_ASSERT_MESSAGE(finished, "Expected to be finished but was not");
    TEST_ASSERT_EQUAL(0x05, cpu->register_a);
    TEST_ASSERT_EQUAL(CPU_PROCESSOR_STATUS_UNSET, cpu->processor_status & CPU_PROCESSOR_STATUS_ZERO_FLAG);
    TEST_ASSERT_EQUAL(CPU_PROCESSOR_STATUS_UNSET, cpu->processor_status & CPU_PROCESSOR_STATUS_NEGATIVE_FLAG);
}

void test_0xa9_lda_zero_flag(void)
{
    uint8_t program[3] = { 0xa9, 0x00, 0x00 };

    struct cpu* cpu = cpu_init();
    cpu_interpret(cpu, program);

    TEST_ASSERT_EQUAL(CPU_PROCESSOR_STATUS_ZERO_FLAG, cpu->processor_status & CPU_PROCESSOR_STATUS_ZERO_FLAG);
}

void test_0xa9_lda_negative_flag(void)
{
    uint8_t program[3] = { 0xa9, 0xff, 0x00 };

    struct cpu* cpu = cpu_init();
    cpu_interpret(cpu, program);

    TEST_ASSERT_EQUAL(CPU_PROCESSOR_STATUS_NEGATIVE_FLAG, cpu->processor_status & CPU_PROCESSOR_STATUS_NEGATIVE_FLAG);
}

void test_0xaa_tax_transfer_data(void)
{
    uint8_t program[2] = { 0xaa, 0x00 };

    struct cpu* cpu = cpu_init();
    cpu->register_a = 99;

    cpu_interpret(cpu, program);

    TEST_ASSERT_EQUAL(99, cpu->register_x);
    TEST_ASSERT_EQUAL(CPU_PROCESSOR_STATUS_UNSET, cpu->processor_status & CPU_PROCESSOR_STATUS_ZERO_FLAG);
    TEST_ASSERT_EQUAL(CPU_PROCESSOR_STATUS_UNSET, cpu->processor_status & CPU_PROCESSOR_STATUS_NEGATIVE_FLAG);
}

void test_0xaa_tax_zero_flag(void)
{
    uint8_t program[2] = { 0xaa, 0x00 };

    struct cpu* cpu = cpu_init();
    cpu->register_a = 0;

    cpu_interpret(cpu, program);

    TEST_ASSERT_EQUAL(CPU_PROCESSOR_STATUS_ZERO_FLAG, cpu->processor_status & CPU_PROCESSOR_STATUS_ZERO_FLAG);
}

void test_0xaa_tax_negative_flag(void)
{
    uint8_t program[2] = { 0xaa, 0x00 };

    struct cpu* cpu = cpu_init();
    cpu->register_a = -127;

    cpu_interpret(cpu, program);

    TEST_ASSERT_EQUAL(CPU_PROCESSOR_STATUS_NEGATIVE_FLAG, cpu->processor_status & CPU_PROCESSOR_STATUS_NEGATIVE_FLAG);
}

void test_0xe8_inx_increment_x(void)
{
    uint8_t program[2] = { 0xe8, 0x00 };

    struct cpu* cpu = cpu_init();
    cpu->register_x = 99;

    cpu_interpret(cpu, program);

    TEST_ASSERT_EQUAL(100, cpu->register_x);
    TEST_ASSERT_EQUAL(CPU_PROCESSOR_STATUS_UNSET, cpu->processor_status & CPU_PROCESSOR_STATUS_ZERO_FLAG);
    TEST_ASSERT_EQUAL(CPU_PROCESSOR_STATUS_UNSET, cpu->processor_status & CPU_PROCESSOR_STATUS_NEGATIVE_FLAG);
}

void test_0xe8_inx_zero_flag(void)
{
    uint8_t program[2] = { 0xe8, 0x00 };

    struct cpu* cpu = cpu_init();
    cpu->register_x = -1;

    cpu_interpret(cpu, program);

    TEST_ASSERT_EQUAL(0, cpu->register_x);
    TEST_ASSERT_EQUAL(CPU_PROCESSOR_STATUS_ZERO_FLAG, cpu->processor_status & CPU_PROCESSOR_STATUS_ZERO_FLAG);
}

void test_0xe8_inx_negative_flag(void)
{
    uint8_t program[2] = { 0xe8, 0x00 };

    struct cpu* cpu = cpu_init();
    cpu->register_x = -2;

    cpu_interpret(cpu, program);

    TEST_ASSERT_EQUAL((uint8_t)-1, cpu->register_x);
    TEST_ASSERT_EQUAL(CPU_PROCESSOR_STATUS_NEGATIVE_FLAG, cpu->processor_status & CPU_PROCESSOR_STATUS_NEGATIVE_FLAG);
}

void test_0xe8_inx_overflow(void)
{
    uint8_t program[3] = { 0xe8, 0xe8, 0x00 };

    struct cpu* cpu = cpu_init();
    cpu->register_x = 0xff;

    cpu_interpret(cpu, program);

    TEST_ASSERT_EQUAL(1, cpu->register_x);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_0xa9_lda_immediate_load_data);
    RUN_TEST(test_0xa9_lda_zero_flag);
    RUN_TEST(test_0xa9_lda_negative_flag);
    RUN_TEST(test_0xaa_tax_transfer_data);
    RUN_TEST(test_0xaa_tax_zero_flag);
    RUN_TEST(test_0xaa_tax_negative_flag);
    RUN_TEST(test_0xe8_inx_increment_x);
    RUN_TEST(test_0xe8_inx_zero_flag);
    RUN_TEST(test_0xe8_inx_negative_flag);
    RUN_TEST(test_0xe8_inx_overflow);
    return UNITY_END();
}
