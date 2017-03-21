#include <kernel/terminal.h>
#include <stdint.h>
#include <string.h>

static const int VGA_WIDTH = 80;
static const int VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xb8000;

struct terminal {
    size_t row;
    size_t column;
    uint8_t color;
    uint16_t* buffer;
};

static struct terminal terminal;

void terminal_initialize(void) {
    terminal.row = 0;
    terminal.column = 0;
    terminal.color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    terminal.buffer = VGA_MEMORY;
    for (size_t row = 0; row < VGA_HEIGHT; row++) {
        for (size_t column = 0; column < VGA_WIDTH; column++) {
            terminal.buffer[row * VGA_WIDTH + column] =
                vga_entry(' ', terminal.color);
        }
    }
}

void terminal_putentryat(unsigned char c, uint8_t color, size_t row,
        size_t column) {
    terminal.buffer[row * VGA_WIDTH + column] = vga_entry(c, color);
}

void terminal_putchar(char c) {
    terminal_putentryat((unsigned char)c, terminal.color, terminal.row,
            terminal.column);
    if (++terminal.column == VGA_WIDTH) {
        terminal.column = 0;
        if (++terminal.row == VGA_HEIGHT) {
            terminal.row = 0;
        }
    }
}

void terminal_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        terminal_putchar(data[i]);
    }
}

void terminal_writestring(const char* data) {
    terminal_write(data, strlen(data));
}

