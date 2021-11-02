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
        case 0xA9: {
            uint8_t value = program[cpu->program_counter];
            cpu->register_a = value;
            ++cpu->program_counter;

            if (cpu->register_a == 0) {
                cpu->status_register |= 0b00000010;
            } else {
                cpu->status_register &= 0b11111101;
            }

            if (cpu->register_a & 0b10000000) {
                cpu->status_register |= 0b10000000;
            } else {
                cpu->status_register &= 0b01111111;
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
