
void keyboard_handler_main(void)
{
  
    char scancode;
    
    write_port(0x20, 0x20); //write EOI (end of interupt)
    status = read_port(0x64); //read status of keyboard on port 0x64
    //current_line_buffer_pos=0;
    
    //check if buffer is not empty
    if (status & 0x01){
        
        scancode = read_port(0x60); //read keycode of keboard on port 0x60
        
        if(scancode < 0)
        return;
        
        
        terminal(scancode);
        return;
    }
}