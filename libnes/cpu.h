#pragma once

#include <stdbool.h>
#include <stdint.h>

struct cpu {
    uint8_t register_a;
    uint8_t status_register;
    uint16_t program_counter;
};

struct cpu* cpu_init(void);

bool cpu_interpret(struct cpu* cpu, const uint8_t* program);
