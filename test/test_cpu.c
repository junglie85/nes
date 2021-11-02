#define MUNIT_ENABLE_ASSERT_ALIASES
#include <munit/munit.h>

#include <libnes/cpu.h>

MunitResult test_0xA9_lda_immediate_load_data(const MunitParameter param[], void* user_data_or_fixture)
{
    uint8_t program[3] = { 0xA9, 0x05, 0x00 };

    struct cpu* cpu = cpu_init();
    bool finished = cpu_interpret(cpu, program);

    assert_true(finished);
    assert_uint8(cpu->register_a, ==, 0x05);
    assert_uint8(cpu->status_register & 0b00000010, ==, 0b00);
    assert_uint8(cpu->status_register & 0b10000000, ==, 0b00);

    return MUNIT_OK;
}

MunitResult test_0xA9_lda_zero_flag(const MunitParameter param[], void* user_data_or_fixture)
{
    uint8_t program[3] = { 0xA9, 0x00, 0x00 };

    struct cpu* cpu = cpu_init();
    cpu_interpret(cpu, program);

    assert_uint8(cpu->status_register & 0b00000010, ==, 0b10);

    return MUNIT_OK;
}

MunitResult test_0xA9_lda_negative_flag(const MunitParameter param[], void* user_data_or_fixture)
{
    uint8_t program[3] = { 0xA9, 0xFF, 0x00 };

    struct cpu* cpu = cpu_init();
    cpu_interpret(cpu, program);

    assert_uint8(cpu->status_register & 0b10000000, ==, 0b10000000);

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
