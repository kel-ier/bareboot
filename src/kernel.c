#include<stdbool.h>
#include<stddef.h>
#include<stdint.h>
#if defined(__linux__)
#error "Wrong compiler utilised"
#endif

//Hardware text constants for vga colours
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

//Function to define color bytes for a character
static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg){
	return fg | (bg<<4);
}
//Function to define a character byte
static inline uint16_t vga_entry(unsigned char ch, uint8_t color){
	return (uint16_t) ch | ((uint16_t) color << 8);
}

size_t strlen(const char* str){
	size_t len = 0;
	while(str[len])
		len++;
	return len;
}


//Set size of screen
#define VGA_WIDTH   80
#define VGA_HEIGHT  25
#define VGA_MEMORY  0xB8000 

size_t terminal_row;
size_t terminal_col;
uint8_t terminal_color;
uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;

//Initilise terminal to fixed colors, set cursor to start
void terminal_init(void){
	terminal_row = 0;
	terminal_col = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BLACK);
	for(size_t i = 0;i<VGA_HEIGHT;i++)
		for(size_t j = 0;j<VGA_WIDTH;j++){
			size_t idx = (i*VGA_WIDTH) + j;
			terminal_buffer[idx] = vga_entry(' ',terminal_color);
		}
}

//Following functions are used to display characters
void terminal_putentryat(char ch, uint8_t color, size_t x, size_t y){
	const size_t idx = y*VGA_WIDTH + x;
	terminal_buffer[idx] = vga_entry(ch,color);
}

void terminal_putchar(char ch){
	if(ch == '\n'){							//Implement new line
		terminal_col = 0;
		if(++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
		return;
	}
	terminal_putentryat(ch, terminal_color,terminal_col, terminal_row);
	if(++terminal_col == VGA_WIDTH){
		terminal_col = 0;
		if(++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}

void terminal_write(const char* data){
	size_t size = strlen(data);
	for(size_t i =0;i<size;i++)
		terminal_putchar(data[i]);
}

void kernel_main(void){
	terminal_init();
	terminal_write("Hello from os:\nImplemented by Arjun");
}