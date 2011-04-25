#include "vga.h"
#include "common.h"
#define VGA_CMD_PORT 0x3D4
#define VGA_DATA_PORT 0x3D5
#define VGA_CURSOR_HIGH 14
#define VGA_CURSOR_LOW 15
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEM_LOCATION 0xB8000;
#define HIGH_BYTE(x) (x >> 8)
#define LOW_BYTE(x) (x)
static void move_cursor(void);
static void scroll(void);


vga_entry_t *vidmem = (vga_entry_t *)VGA_MEM_LOCATION;
u8int cursor_x;
u8int cursor_y;

static void move_cursor(void)
{
	u16int cursor_pos = cursor_y * VGA_WIDTH + cursor_x;
	outb(VGA_CMD_PORT,	VGA_CURSOR_HIGH);
	outb(VGA_DATA_PORT,	HIGH_BYTE(cursor_pos));
	outb(VGA_CMD_PORT,	VGA_CURSOR_LOW);
	outb(VGA_DATA_PORT,	LOW_BYTE(cursor_pos));
}

static void scroll(void)
{
	vga_entry_t blank;
	blank.bgcolor	= VGA_COLOR_BLUE;
	blank.fgcolor	= VGA_COLOR_WHITE;
	blank.value		= ' ';
	if (cursor_y >= VGA_HEIGHT)
	{
		int i;
		for (i = 0*VGA_WIDTH; i < (VGA_HEIGHT - 1)*VGA_WIDTH; ++i)
			vidmem[i] = vidmem[i + VGA_WIDTH];
		for (i = (VGA_HEIGHT - 1)*VGA_WIDTH; i < VGA_HEIGHT*VGA_WIDTH; ++i)
			vidmem[i] = blank;
		cursor_y = VGA_HEIGHT - 1;
	}
}

void vga_put_entry(vga_entry_t _entry)
{
	switch (_entry.value)
	{
		case 0x08:
			if (cursor_x)
				cursor_x--;
			break;
		case 0x09:
			cursor_x = (cursor_x+8) & ~(8-1);
			break;
		case '\r':
			cursor_x = 0;
			break;
		case '\n':
			cursor_x = 0;
			cursor_y++;
			break;
		default:
			if (_entry.value >= ' ')
			{
				vidmem[cursor_y * VGA_WIDTH + cursor_x] = _entry;
				cursor_x++;
			}
			break;
	}
	if (cursor_x >= VGA_WIDTH)
	{
		cursor_x = 0;
		cursor_y ++;
	}
	scroll();
	move_cursor();
}

void vga_clear(void)
{
	vga_entry_t blank;
	blank.bgcolor	= VGA_COLOR_BLUE;
	blank.fgcolor	= VGA_COLOR_WHITE;
	blank.value		= ' ';
	int i;
	for (i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
		vidmem[i] = blank;
	cursor_x = 0;
	cursor_y = 0;
	move_cursor();
}

void vga_putc(char _c)
{
	vga_entry_t entry;
	entry.bgcolor	= VGA_COLOR_BLUE;
	entry.fgcolor	= VGA_COLOR_WHITE;
	entry.value		= _c;
	vga_put_entry(entry);
}

void vga_eputc(char _c, char _fgcolor, char _bgcolor)
{
    vga_entry_t entry;
    entry.bgcolor = _bgcolor;
    entry.fgcolor = _fgcolor;
    entry.value = _c;
    vga_put_entry(entry);
}



void vga_puts(char *_str)
{
	int i = -1;
	do vga_putc(_str[i++]);
	while(_str[i]);
}

void vga_eputs(char *_str, char _fgcolor, char _bgcolor)
{
	int i = -1;
	do vga_eputc(_str[i++], _fgcolor, _bgcolor);
	while(_str[i]);
}
