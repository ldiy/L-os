//define var's
#define screensize 2*25*80
extern char read_port(unsigned short port);
extern void write_port(unsigned short port, unsigned char data);
extern void load_idt(unsigned long *idt_ptr);
char *videomem = (char*)0xb8000;
unsigned int current_pos=0;
unsigned int current_cursor_pos=0;
unsigned int cursor_col=0;
unsigned int cursor_row=0;
unsigned char color=0x07;
//clear screen
void clearscreen(void){
	for(int i=0; i<screensize; i=i){
		videomem[i++] = ' ';
		videomem[i++] = color;
	}
	
}
//set cursor location (row, col)
void set_cursor(int row, int col)
{
   unsigned short position=(row*80) + col;

   // cursor LOW port to vga INDEX register
   write_port(0x3D4, 0x0F);
   write_port(0x3D5, (unsigned char)(position&0xFF));
   // cursor HIGH port to vga INDEX register
   write_port(0x3D4, 0x0E);
   write_port(0x3D5, (unsigned char )((position>>8)&0xFF));
   //set_cursor(row,col);
   cursor_col=col;
   cursor_row=row;
}

//scroll screen function
void scroll_screen(void){
	int i=0;
	int x=160;
	int z=0;
	int y=158;
	if(current_pos>3840){
		while(z<=25){
			while(i<=y){
				videomem[i]=videomem[x];
				i++;
				x++;
			}
			i=i+1;
			x=x+1;
			y=y+160;
			z++;
		}
		current_pos=3682;
		cursor_row--;
		set_cursor(cursor_row,cursor_col);
	}		
	
}
//print function string
void kprint(const char *str)
{
	unsigned int i = 0;
	while (str[i] != '\0') {
		videomem[current_pos++] = str[i++];
		videomem[current_pos++] = color;
		scroll_screen();
	}
}


//print function char
void kprintc(const char str)
{
		videomem[current_pos++] = str;
		videomem[current_pos++] = color;
		scroll_screen();
}



//set current possition (row,col)
void set_curpos(int row, int col){
	current_pos=(row*80+col)*2;
	scroll_screen();
}

//reset cursor location (0,0)
void reset_cursor_poss(void){
	set_cursor(0,0);
	cursor_col=0;
	cursor_row=0;
}
//reset possition
void reset_screen_poss(void){
	current_pos=0;
}


//set current_pos to a new line
void new_line(void){
	current_pos = current_pos + (160 - current_pos % (160));
	scroll_screen();
}

//print a string and set current_pos and cursor location to a new line
void kprintln(const char *str){
	kprint(str);
	new_line();
	cursor_row++;
	cursor_col=0;
}

//set the for- and background color of the screen
void setcolor(char colorc){
	for(int i=1; i<screensize; i=i+2){
		videomem[i] = colorc;
	}
}