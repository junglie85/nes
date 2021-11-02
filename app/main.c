#include <libnes/cpu.h>

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    uint8_t program[3] = { 0xA9, 0x05, 0x00 };

    struct cpu* cpu = cpu_init();
    bool finished = cpu_interpret(cpu, program);

    printf("Register A: 0x%02X\n", cpu->register_a);

    if (finished) {
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}
