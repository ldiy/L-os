#include "keyboard_map.h"
extern unsigned char keyboard_map[128];
extern unsigned char keyboard_map_shift[128];
unsigned char status;
unsigned int ok;
unsigned int shift;
char line_buffer[80];
int current_line_buffer_pos;
int h;

// clear the line buffer
void clear_line_buffer(void)
{
    unsigned int i = 0;
    while (i < 80) {
        line_buffer[i++] = ' ';
        current_line_buffer_pos=0;
    }
}

//clear a buffer
void clear(char*str)
{
    unsigned int i = 0;
    while (i < 80) {
        str[i++] = '\0';       
    }
}

//get the first word of a line
char * get_program(char * line){
    unsigned int i =0;
    char *command;
    while(line[i] != ' '){
        command[i]=line[i];
        i++;
    }
    command[i]='\0';
    return(command);
}

// get lengt of a *str
int get_lenght(char * str){
    int i =0;
    while(str[i] != '\0'){
        i++;
    }
    return(i);
}



//check if command is in the line
int check_command(char* line, char* command){
    int length = get_lenght(command);
    int i = 0 ;
    int ok = 1;
    char *comm_space;
    while (i < length){
      if(line[i] != command[i]){
        ok = 0;
      } 
      i++;
    }
    if(ok == 1){
      return(1);
    }
    else{
      return(0);
    }
  }
  
  //remove the command from the line (get the options)
char * rem_program(char * line, char * programm){
    int line_length=get_lenght(line);
    int programm_lenght=get_lenght(programm);
    int i = programm_lenght + 1;
    int y=0;
    char * options;
    while(line[i] != '\0'){
        options[y++]=line[i++];
    }
    options[y]='\0';
    return(options);
    clear(options);
}

//char to int
/*int toInt(char c){
    if(c=='0')
        return(0);
    if(c=='1')
        return(1);
    if(c=='2')
        return(2);
    if(c=='3')
        return(3);
    if(c=='4')
        return(4);
    if(c=='5')
        return(5);
    if(c=='6')
        return(6);
    if(c=='7')
        return(7);
    if(c=='8')
        return(8);
    if(c=='9')
        return(9);
    return(10);
}*/

//char to hex
int toHex(char c){
	if(c == '0'){
		return 0x0;
	}if(c == '1'){
		return 0x1;
	}if(c == '2'){
		return 0x2;
	}if(c == '3'){
		return 0x3;
	}if(c == '4'){
		return 0x4;
	}if(c == '5'){
		return 0x5;
	}if(c == '6'){
		return 0x6;
	}if(c == '7'){
		return 0x7;
	}if(c == '8'){
		return 0x8;
	}if(c == '9'){
		return 0x9;
	}if(c == 'a' || c == 'A'){
		return 0xa;
	}if(c == 'b' || c == 'B'){
		return 0xb;
	}if(c == 'c' || c == 'C'){
		return 0xc;
	}if(c == 'd' || c == 'D'){
		return 0xd;
	}if(c == 'e' || c == 'E'){
		return 0xe;
	}if(c == 'f' || c == 'F'){
		return 0xf;
	}
	return -1;
}



int a=0;
int b=0;

//runs the programm
void program(char program[80]){
    char * comand = get_program(program); //get the first word of the line
    char  *options = rem_program(program,comand);  //get the rest of the line
    int check=1;

    //echo command
    if(check_command(program,"echo \0")){
        kprint(options);//print the rest of the line after the echo command
        check=0; 
    }



    //check for harddisk
  /*  if(check_command(program,"read \0")){
             read_disk(0,0,1);
             
             
        check=0; 
    }
    if(check_command(program,"write \0")){
        // listFiles(0,0,10);
        write_disk(0,0,options);
         //preparedisk(0,0);
        check=0; 
    }*/
    //shutdown command
    if(check_command(program,"shutdown \0")){
        clearscreen();//clear the screen
        reset_screen_poss(); //reset current position to 0,0
        reset_cursor_poss(); //reset cursor location to 0,0
        color=0x04;//set the screen color to 0x04
        kprint("please, press the power button to shutdown your computer");
        __asm__ __volatile__("hlt"); //halt the cpu
        check=0;
    }

    //cls command (clear screen)
    if(check_command(program,"cls \0")){
        clearscreen(); //clear the screen
        set_curpos(0,0); //set current possition to 0,0
        cursor_col=0;  //set cursor to 0,0
        cursor_row=0;
        check=0;
    }

    //help command
    if(check_command(program,"help \0")){
        kprintln("|-----------------HELP-----------------|");
        kprintln("|echo    |                             |");
        kprintln("|cls     |  clear the screen           |");
        kprintln("|color   |  set the color of the screen|");
        kprintln("|shutdown|  shutdown the computer      |");
        kprintln("|version |  show version information   |");
        kprintln("|help    |  show this help message     |");      
          kprint("|--------------------------------------|");
        check=0;
    }

    //version command (show version information)
    if(check_command(program,"version \0")){
        kprintln("|--------------VERSION--------------|");
        kprintln("|               L-os                |");
        kprintln("|            version: 0.0.9         |");
        kprintln("|             made by:              |");
        kprintln("|              L-diy                |");
        kprintln("|          Lorenz Clijnen           |");
          kprint("|-----------------------------------|");
        check=0;
    }

    //color command(set the screen color)
    if(check_command(program,"color \0")){
        if(check_command(options,"0x\0")){//if options starts with 0x set the screen color
            a=toHex(options[2]);
            b=toHex(options[3]);
            color = (a * 16)+b;
            setcolor(color);
        }
        else if(check_command(options,"help\0")){ //if options starts with help show help information
            kprintln("  example: color 0x07");
            kprintln("           color 0x85");
            kprintln("|--DIGIT--|-----COLOR----||--DIGIT--|-----COLOR-----|");
            kprintln("|    0    |     black    ||    5    |     magenta   |");
            kprintln("|    1    |     blue     ||    6    |     brown     |");
            kprintln("|    2    |     green    ||    6    |   light grey  |");
            kprintln("|    3    |     cyan     ||    7    |    dark grey  |");
            kprintln("|    4    |     red      ||    8    |   light blue  |");
              kprint("|------------------------||-------------------------|");

        }
        else{
            kprint("this is not a color. type color help for more information");
        }
        check=0;
    }


    //if it was not a command
    if(check)
        kprint("command not found");
    
}

//set the keycode's to a line
void terminal(char keycode){
    
    ok=1;
   /* if(keycode== 0x1C){ //enter
        if(line_buffer[0]==' ' || line_buffer[0]=='\0')
        ok=0;
       
        if(ok){
        cursor_row++;
        cursor_col=0;
        new_line();
        program(line_buffer);
        cursor_row++;
        cursor_col=0;
        new_line();
        clear_line_buffer();
        kprint(">>") ;  
        cursor_col=cursor_col+2;
        }   
        ok=0;
    }*/
    if(keycode==0x0E){//backspace
        if(current_line_buffer_pos != 0){ //check if there is something in the buffer
        cursor_col= cursor_col-1;
        current_pos= current_pos -2;
        videomem[current_pos++]=' ';
        videomem[current_pos++]= color;
        current_pos= current_pos-2;
        
        current_line_buffer_pos=current_line_buffer_pos-1;
        set_cursor(cursor_row,cursor_col);
        }
        ok=0;
        return;
    }
    if(keycode==0x36){//richt shift
        shift=1;
        return;
    }
    if(keycode==0xAA){//left shift
        shift=1;
        return;
    }
    if(cursor_col == 80){
        cursor_row++;
        cursor_col=1;
    }
    else{
        if(ok)
        cursor_col++;
    }
    set_cursor(cursor_row,cursor_col);
    if(ok){
   
   
        char key = keyboard_map[(unsigned char) keycode];//convert keycode to asci char with keyboard map
        if(shift){
            key=keyboard_map_shift[(unsigned char) keycode];
            shift=0;
        }
        kprintc(key);
        line_buffer[current_line_buffer_pos++]= key;
    
    }
}