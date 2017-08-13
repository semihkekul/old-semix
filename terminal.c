#include <stddef.h>
#include <stdint.h>
#include "../include/system.h"
void terminal_move_cursor();
void execute_command();
/* Hardware text mode color constants. */
enum vgaColor
{
	VGACOLORBLACK = 0,
	VGACOLORBLUE = 1,
	VGACOLOR_GREEN = 2,
	VGACOLORCYAN = 3,
	VGACOLOR_RED = 4,
	VGACOLOR_MAGENTA = 5,
	VGACOLORBROWN = 6,
	VGACOLOR_LIGHT_GREY = 7,
	VGACOLOR_DARK_GREY = 8,
	VGACOLOR_LIGHTBLUE = 9,
	VGACOLOR_LIGHT_GREEN = 10,
	VGACOLOR_LIGHTCYAN = 11,
	VGACOLOR_LIGHT_RED = 12,
	VGACOLOR_LIGHT_MAGENTA = 13,
	VGACOLOR_LIGHTBROWN = 14,
	VGACOLORWHITE = 15,
};

static inline uint8_t vgaEntryColor(enum vgaColor fg, enum vgaColor bg)
{
	return fg | bg << 4;
}

static inline uint16_t vgaEntry(unsigned char uc, uint8_t color)
{
	return (uint16_t)uc | (uint16_t)color << 8;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *terminal_buffer;

void terminal_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vgaEntryColor(VGACOLOR_LIGHT_GREY, VGACOLORBLACK);
	terminal_buffer = (uint16_t *)0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++)
	{
		for (size_t x = 0; x < VGA_WIDTH; x++)
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vgaEntry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vgaEntry(c, color);
}

void term_scroll_screen_up()
{
	for (size_t idx = VGA_WIDTH; idx < VGA_WIDTH * VGA_HEIGHT; ++idx)
	{
		terminal_buffer[idx - VGA_WIDTH] = terminal_buffer[idx];
	}
	size_t lastRow = VGA_WIDTH * (VGA_HEIGHT - 1);
	for (size_t idx = 0; idx < VGA_WIDTH; ++idx)
	{
		terminal_buffer[idx + lastRow] = ' ';
	}
}

bool command_mode = false;
bool command_complete = true;
void putc(char c)
{
	switch (c)
	{
	case '\r':
		terminal_column = 0;
		break;
	case '\n':
		terminal_column = 0;
		terminal_row++;
		if(command_complete && command_mode)
			execute_command();
		break;
	case '\t':
		terminal_column = (terminal_column + 8) / 8 * 8;
		if (terminal_column >= VGA_WIDTH)
		{
			terminal_column -= VGA_WIDTH;
			terminal_row++;
		}
		break;
	case '\f':
		/*
        termEraseScreen();
        terminal_column = terminal_row = 0;
		*/
		break;
	case '\a':
		//termBeep();
		break;


	case '\b':
		if (terminal_column > 1)
			terminal_column--;

			terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);

		//if (terminal_column > 0)
		//terminal_column--;

	case 0:
	 break;

	default:
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH)
		{
			terminal_column = 0;
			++terminal_row;
		}
		break;
	}

	if (terminal_row == VGA_HEIGHT)
	{
		term_scroll_screen_up();
		terminal_row--;
	}
	terminal_move_cursor();
}

void terminal_write(const char *data, size_t size)
{
	for (size_t i = 0; i < size; i++)
		putc(data[i]);
}


void puts(const char *data)
{
	terminal_write(data, strlen(data));
}

void terminal_move_cursor()
{
	unsigned temp;

	/* The equation for finding the index in a linear
    *  chunk of memory can be represented by:
    *  Index = [(y * width) + x] */
	temp = terminal_row * VGA_WIDTH + terminal_column;
	outb(0x3D4, 14);
	outb(0x3D5, temp >> 8);
	outb(0x3D4, 15);
	outb(0x3D5, temp);
}

void terminal_command_mode(bool mode)
{
	command_mode = mode;
}


void execute_command()
{
	
     
	const size_t index = terminal_row * VGA_WIDTH + terminal_column;
    
	command_complete = false;
	
	//if(strcmp(command,"help") == 0 )
	{
		//puts("halt : shut down the computer");
	//	puts("help : prints help");
	}
	//else 
	{
		puts(" command not found!\n");
	}
	puts("$ ");
	command_complete = true;
}