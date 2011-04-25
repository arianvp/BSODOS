#ifndef _VGA_H_
#define _VGA_H_
#define VGA_COLOR_BLACK 0
#define VGA_COLOR_BLUE 1
#define VGA_COLOR_GREEN 2
#define VGA_COLOR_CYAN 3
#define VGA_COLOR_RED 4
#define VGA_COLOR_MAGENTA 5
#define VGA_COLOR_BROWN 6
#define VGA_COLOR_LIGHTGREY 7
#define VGA_COLOR_DARKGREY 8
#define VGA_COLOR_LIGHTBLUE 9
#define VGA_COLOR_LIGHTGREEN 10
#define VGA_COLOR_LIGHTCYAN 11
#define VGA_COLOR_LIGHTRED 12
#define VGA_COLOR_LIGHTMAGENTA 13
#define VGA_COLOR_LIGHTBROWN 14
#define VGA_COLOR_WHITE 15

struct vga_entry_struct
{
	char value;
	unsigned fgcolor : 4;
	unsigned bgcolor : 4;
}__attribute__((packed));

typedef struct vga_entry_struct  vga_entry_t;

void vga_put_entry(vga_entry_t _entry);
void vga_putc(char _c);
void vga_eputc(char _c, char _fgcolor, char _bgcolor);
void vga_clear(void);
void vga_puts(char *_str);
void vga_eputs(char *_str, char _fgcolor, char _bgcolor);
#endif
