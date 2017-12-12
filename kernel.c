
extern void load_idt(unsigned long *idt_ptr);
extern void keyboard_handler(void);

#include "screen.c" //load file for screen functions
#include "idt.c" //load Interrupt descriptor table (idt.c)
#include "irq.c" //load interupt request file (irq.c)
//#include "fat.c"
#include "terminal.c" //load terminal file
#include "keyboard.c" //load keyboard file

void kmain(void)
{

	clearscreen(); //clear the screen
	reset_screen_poss(); //reset current position to 0,0
	reset_cursor_poss(); //reset cursor location to 0,0
	kprint("Welcome"); //print welcome message on the screen
	set_cursor(1,2); //set cursor to line 1
	set_curpos(1,0);//set current possition to line 1
	kprint(">>");
	idt_init(); //initialize interupt descrpiter table
	kb_init(); //initialize keyboard
	while(1);
	
}
