#pragma once

#include <stdbool.h>
#include <stdint.h>

enum cpu_processor_status {
    CPU_PROCESSOR_STATUS_ZERO_FLAG = 0b00000010,
    CPU_PROCESSOR_STATUS_NEGATIVE_FLAG = 0b10000000,
};

struct cpu {
    uint8_t register_a;
    uint8_t register_x;
    uint8_t processor_status;
    uint16_t program_counter;
    bool running;
};

struct cpu* cpu_init(void);

bool cpu_interpret(struct cpu* cpu, const uint8_t* program);
