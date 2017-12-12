void read_disk(unsigned char adrr, int drive, int mode){
    write_port(0x1F1,0x00); //send null byte to port 0x1f1
    write_port(0x1F2,0x01); //send sector count to port 0x1ft
    write_port(0x1F3,(unsigned char)addr); //send the low 8 bits of the block adress
    write_port(0x1F4,(unsigned char)adrr>>8); //send the next 8 bits of the block adress to port 0x1F4
    write_port(0x1F5,(unsigned char)addrr>>16); //send next 8 bits
    write_port(0x1F6,0xE0|(drive<<4)|((adr>>24)&0X0f));//send drive indicater, magic bits and highest 4 bits of block adress
    if(mode){//read
        write_port(0x1F7,0x20);

    }
    else{
        write_port(0x1F7,0x30);
    }
    
}
