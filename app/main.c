#include <libnes/cpu.h>

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void print_binary(uint8_t byte)
{
    int i = CHAR_BIT * sizeof(byte);
    while (i--) {
        putchar('0' + ((byte >> i) & 1));
    }
}

int main(void)
{
    uint8_t program[5] = { 0xA9, 0xC0, 0xAA, 0xE8, 0x00 };

    struct cpu* cpu = cpu_init();
    bool finished = cpu_interpret(cpu, program);

    printf("Register A: 0x%02X\n", cpu->register_a);
    printf("Register X: 0x%02X\n", cpu->register_x);
    printf("Processor status: 0b");
    print_binary(cpu->processor_status);
    printf("\nProgram counter: %d\n", cpu->program_counter);

    if (finished) {
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}
