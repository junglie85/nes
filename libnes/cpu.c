#include "cpu.h"

#include <stdio.h>

static struct cpu internal_cpu = { 0 };

struct cpu* cpu_init(void)
{
    return &internal_cpu;
}

bool cpu_interpret(struct cpu* cpu, const uint8_t* program)
{
    cpu->program_counter = 0;
    bool running = true;
    while (running) {
        uint8_t opcode = program[cpu->program_counter];
        ++cpu->program_counter;

        switch (opcode) {
        case 0xAA: {
            cpu->register_x = cpu->register_a;

            if (cpu->register_x == 0) {
                cpu->processor_status |= CPU_PROCESSOR_STATUS_ZERO_FLAG;
            } else {
                cpu->processor_status &= ~CPU_PROCESSOR_STATUS_ZERO_FLAG;
            }

            if (cpu->register_x & 0b10000000) {
                cpu->processor_status |= CPU_PROCESSOR_STATUS_NEGATIVE_FLAG;
            } else {
                cpu->processor_status &= ~CPU_PROCESSOR_STATUS_NEGATIVE_FLAG;
            }

            break;
        }
        case 0xA9: {
            uint8_t value = program[cpu->program_counter];
            cpu->register_a = value;
            ++cpu->program_counter;

            if (cpu->register_a == 0) {
                cpu->processor_status |= CPU_PROCESSOR_STATUS_ZERO_FLAG;
            } else {
                cpu->processor_status &= ~CPU_PROCESSOR_STATUS_ZERO_FLAG;
            }

            if (cpu->register_a & 0b10000000) {
                cpu->processor_status |= CPU_PROCESSOR_STATUS_NEGATIVE_FLAG;
            } else {
                cpu->processor_status &= ~CPU_PROCESSOR_STATUS_NEGATIVE_FLAG;
            }

            break;
        }
        case 0x00:
            running = false;
            break;
        default:
            printf("Unsupported opcode: 0x%02X\n", opcode);
            return false;
        }
    }

    return true;
}
