#include "stdint.h"
void preparedisk(int disk, int addr){
	write_port(0x1F1,0x00);
	write_port(0x1F2,0x01);
	write_port(0x1F3,(unsigned char)addr);
	write_port(0x1F4,(unsigned char)(addr >> 8));
	write_port(0x1F5,(unsigned char)(addr >> 16));
	write_port(0x1F6,0xE0 | (disk << 4) | ((addr >> 24) & 0x0F));
	write_port(0x1F7,0x20);
	while (!(read_port(0x1F7) & 0x08)) {}
}

void read_disk(int disk, int addr, int len){
	for(int s = 0; s < len; s++){
		preparedisk(disk,addr+s);
		unsigned char sect[512];
		for(int i = 0; i < 255; i++){
			uint16_t tmpword = (uint16_t)read_port(0x1F0);
			//sect[i] = ((unsigned char)(tmpword));
			//sect[i+1] = ((unsigned char)(tmpword >> 8));
			kprintc((uint16_t)(tmpword));
			kprintc((uint16_t)(tmpword >> 8));
		}
		//kprint(sect);
	}

	//
/*	write_port(0x1F6,0xE0 | (disk << 4) | ((addr >> 24) & 0x0F));
	write_port(0x1F1,0x00);
	write_port(0x1F2,0x01);
	write_port(0x1F3,(unsigned char)addr);
	write_port(0x1F4,(unsigned char)(addr >> 8));
	write_port(0x1F5,(unsigned char)(addr >> 16));
	
	write_port(0x1F7,0x20);
	while (!(read_port(0x1F7) & 0x08)) {}
	
	unsigned char*tmpword;
	for (int idx = 0; idx < 256; idx++)	
	{	
		tmpword[idx]=read_port(0x1F0);
		tmpword[idx++]=read_port(0x1F0);
	}
	kprint(tmpword);*/
}
void write_disk(int disk, int addr,char*data){
	write_port(0x1F6,0xE0 | (disk << 4) | ((addr >> 24) & 0x0F));
	write_port(0x1F1,0x00);
	write_port(0x1F2,0x01);
	write_port(0x1F3,(unsigned char)addr);
	write_port(0x1F4,(unsigned char)(addr >> 8));
	write_port(0x1F5,(unsigned char)(addr >> 16));
	
	write_port(0x1F7,0x30);
	while (!(read_port(0x1F7) & 0x08)) {}
	
	unsigned char tmpword;
	for (int idx = 0; idx < 256; idx++)	
	{	
	write_port(0x1F0,data[idx]);
	//write_port(0x1F0,data[idx]);
	}
	write_port(0x1F7,0xE7);
	
	
}

