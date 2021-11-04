#define MUNIT_ENABLE_ASSERT_ALIASES
#include <munit/munit.h>

#include <libnes/cpu.h>

const uint8_t CPU_PROCESSOR_STATUS_UNSET = 0b00000000;

MunitResult test_0xA9_lda_immediate_load_data(const MunitParameter param[], void* user_data_or_fixture)
{
    uint8_t program[3] = { 0xA9, 0x05, 0x00 };

    struct cpu* cpu = cpu_init();
    bool finished = cpu_interpret(cpu, program);

    assert_true(finished);
    assert_uint8(cpu->register_a, ==, 0x05);
    assert_uint8(cpu->processor_status & CPU_PROCESSOR_STATUS_ZERO_FLAG, ==, CPU_PROCESSOR_STATUS_UNSET);
    assert_uint8(cpu->processor_status & CPU_PROCESSOR_STATUS_NEGATIVE_FLAG, ==, CPU_PROCESSOR_STATUS_UNSET);

    return MUNIT_OK;
}

MunitResult test_0xA9_lda_zero_flag(const MunitParameter param[], void* user_data_or_fixture)
{
    uint8_t program[3] = { 0xA9, 0x00, 0x00 };

    struct cpu* cpu = cpu_init();
    cpu_interpret(cpu, program);

    assert_uint8(cpu->processor_status & CPU_PROCESSOR_STATUS_ZERO_FLAG, ==, CPU_PROCESSOR_STATUS_ZERO_FLAG);

    return MUNIT_OK;
}

MunitResult test_0xA9_lda_negative_flag(const MunitParameter param[], void* user_data_or_fixture)
{
    uint8_t program[3] = { 0xA9, 0xFF, 0x00 };

    struct cpu* cpu = cpu_init();
    cpu_interpret(cpu, program);

    assert_uint8(cpu->processor_status & CPU_PROCESSOR_STATUS_NEGATIVE_FLAG, ==, CPU_PROCESSOR_STATUS_NEGATIVE_FLAG);

    return MUNIT_OK;
}

MunitResult test_0xAA_tax_transfer_data(const MunitParameter param[], void* user_data_or_fixture)
{
    uint8_t program[2] = { 0xAA, 0x00 };

    struct cpu* cpu = cpu_init();
    cpu->register_a = 99;

    cpu_interpret(cpu, program);

    assert_uint8(cpu->register_x, ==, 99);
    assert_uint8(cpu->processor_status & CPU_PROCESSOR_STATUS_ZERO_FLAG, ==, CPU_PROCESSOR_STATUS_UNSET);
    assert_uint8(cpu->processor_status & CPU_PROCESSOR_STATUS_NEGATIVE_FLAG, ==, CPU_PROCESSOR_STATUS_UNSET);

    return MUNIT_OK;
}

MunitResult test_0xAA_tax_zero_flag(const MunitParameter param[], void* user_data_or_fixture)
{
    uint8_t program[2] = { 0xAA, 0x00 };

    struct cpu* cpu = cpu_init();
    cpu->register_a = 0;

    cpu_interpret(cpu, program);

    assert_uint8(cpu->processor_status & CPU_PROCESSOR_STATUS_ZERO_FLAG, ==, CPU_PROCESSOR_STATUS_ZERO_FLAG);

    return MUNIT_OK;
}

MunitResult test_0xAA_tax_negative_flag(const MunitParameter param[], void* user_data_or_fixture)
{
    uint8_t program[2] = { 0xAA, 0x00 };

    struct cpu* cpu = cpu_init();
    cpu->register_a = -127;

    cpu_interpret(cpu, program);

    assert_uint8(cpu->processor_status & CPU_PROCESSOR_STATUS_NEGATIVE_FLAG, ==, CPU_PROCESSOR_STATUS_NEGATIVE_FLAG);

    return MUNIT_OK;
}

MunitResult test_0xE8_inx_increment_x(const MunitParameter param[], void* user_data_or_fixture)
{
    uint8_t program[2] = { 0xE8, 0x00 };

    struct cpu* cpu = cpu_init();
    cpu->register_x = 99;

    cpu_interpret(cpu, program);

    assert_uint8(cpu->register_x, ==, 100);
    assert_uint8(cpu->processor_status & CPU_PROCESSOR_STATUS_ZERO_FLAG, ==, CPU_PROCESSOR_STATUS_UNSET);
    assert_uint8(cpu->processor_status & CPU_PROCESSOR_STATUS_NEGATIVE_FLAG, ==, CPU_PROCESSOR_STATUS_UNSET);

    return MUNIT_OK;
}

MunitResult test_0xE8_inx_zero_flag(const MunitParameter param[], void* user_data_or_fixture)
{
    uint8_t program[2] = { 0xE8, 0x00 };

    struct cpu* cpu = cpu_init();
    cpu->register_x = -1;

    cpu_interpret(cpu, program);

    assert_uint8(cpu->register_x, ==, 0);
    assert_uint8(cpu->processor_status & CPU_PROCESSOR_STATUS_ZERO_FLAG, ==, CPU_PROCESSOR_STATUS_ZERO_FLAG);

    return MUNIT_OK;
}

MunitResult test_0xE8_inx_negative_flag(const MunitParameter param[], void* user_data_or_fixture)
{
    uint8_t program[2] = { 0xE8, 0x00 };

    struct cpu* cpu = cpu_init();
    cpu->register_x = -2;

    cpu_interpret(cpu, program);

    assert_uint8(cpu->register_x, ==, -1);
    assert_uint8(cpu->processor_status & CPU_PROCESSOR_STATUS_NEGATIVE_FLAG, ==, CPU_PROCESSOR_STATUS_NEGATIVE_FLAG);

    return MUNIT_OK;
}

MunitResult test_0xE8_inx_overflow(const MunitParameter param[], void* user_data_or_fixture)
{
    uint8_t program[3] = { 0xE8, 0xE8, 0x00 };

    struct cpu* cpu = cpu_init();
    cpu->register_x = 0xFF;

    cpu_interpret(cpu, program);

    assert_uint8(cpu->register_x, ==, 1);

    return MUNIT_OK;
}

int main(int argc, const char* argv[])
{
    MunitTest tests[] = {
        {
            "/test-0xA9-lda-immediate-load-data",
            test_0xA9_lda_immediate_load_data,
        },
        {
            "/test-0xA9-lda-zero-flag",
            test_0xA9_lda_zero_flag,
        },
        {
            "/test-0xA9-lda-negative-flag",
            test_0xA9_lda_negative_flag,
        },
        {
            "/test-0xAA-tax-transfer-data",
            test_0xAA_tax_transfer_data,
        },
        {
            "/test-0xAA-tax-zero-flag",
            test_0xAA_tax_zero_flag,
        },
        {
            "/test-0xAA-tax-negative-flag",
            test_0xAA_tax_negative_flag,
        },
        {
            "/test-0xE8-inx-increment-x",
            test_0xE8_inx_increment_x,
        },
        {
            "/test-0xE8-inx-zero-flag",
            test_0xE8_inx_zero_flag,
        },
        {
            "/test-0xE8-inx-negative-flag",
            test_0xE8_inx_negative_flag,
        },
        {
            "/test-0xE8-inx-overflow",
            test_0xE8_inx_overflow,
        },
        { 0 }
    };

    MunitSuite suite = {
        "/test-cpu",
        tests,
        NULL,
        1,
        MUNIT_SUITE_OPTION_NONE,
    };

    return munit_suite_main(&suite, NULL, argc, argv);
}
