#include "cpu.h"

#include <stdio.h>

static void brk(struct cpu* cpu);
static void inx(struct cpu* cpu);
static void lda(struct cpu* cpu, uint8_t value);
static void tax(struct cpu* cpu);
static void update_program_status(struct cpu* cpu, uint8_t register_value);

static struct cpu internal_cpu = { 0 };

struct cpu* cpu_init(void)
{
    internal_cpu.running = true;
    return &internal_cpu;
}

bool cpu_interpret(struct cpu* cpu, const uint8_t* program)
{
    cpu->program_counter = 0;
    while (cpu->running) {
        uint8_t opcode = program[cpu->program_counter];
        ++cpu->program_counter;

        switch (opcode) {
        case 0xAA: {
            tax(cpu);
            break;
        }
        case 0xA9: {
            uint8_t value = program[cpu->program_counter];
            ++cpu->program_counter;

            lda(cpu, value);
            break;
        }
        case 0xE8: {
            inx(cpu);
            break;
        }
        case 0x00:
            brk(cpu);
            break;
        default:
            printf("Unsupported opcode: 0x%02X\n", opcode);
            return false;
        }
    }

    return true;
}

static void brk(struct cpu* cpu)
{
    cpu->running = false;
}

static void inx(struct cpu* cpu)
{
    cpu->register_x += 1;
    update_program_status(cpu, cpu->register_x);
}

static void lda(struct cpu* cpu, uint8_t value)
{
    cpu->register_a = value;
    update_program_status(cpu, cpu->register_a);
}

static void tax(struct cpu* cpu)
{
    cpu->register_x = cpu->register_a;
    update_program_status(cpu, cpu->register_x);
}

static void update_program_status(struct cpu* cpu, uint8_t register_value)
{
    if (register_value == 0) {
        cpu->processor_status |= CPU_PROCESSOR_STATUS_ZERO_FLAG;
    } else {
        cpu->processor_status &= ~CPU_PROCESSOR_STATUS_ZERO_FLAG;
    }

    if (register_value & 0b10000000) {
        cpu->processor_status |= CPU_PROCESSOR_STATUS_NEGATIVE_FLAG;
    } else {
        cpu->processor_status &= ~CPU_PROCESSOR_STATUS_NEGATIVE_FLAG;
    }
}
