#include "io.h"

#define SERIAL_COM1_BASE 0x3F8

#define SERIAL_DATA_PORT(base) (base)
#define SERIAL_FIFO_COMMAND_PORT(base) (base+2)
#define SERIAL_LINE_COMMAND_PORT(base) (base+3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base+4)
#define SERIAL_LINE_STATUS_PORT(base) (base+5)

#define SERIAL_LINE_ENABLE_DLAB 0x80

int sum_of_three(int a,int b,int c)
{
	int i=0;
	
	char *fb = (char *)0xB8000;
	char arr[22]  = "Welcome to Deep OS!!";
	int j=0;
	for(i=1000;j<20;i+=2)
	{
		outb(0x3D4, 14);
    	outb(0x3D5,((i >> 8) & 0x00FF));
    	outb(0x3D4, 15);
    	outb(0x3D5,i & 0x00FF);
		fb[i] = arr[j++] ;
		fb[i+1] = 0x0F;
	}
	return a+b+c;
}

void serial_configure_baud(unsigned short com,unsigned short divisor)
{
	outb(SERIAL_LINE_COMMAND_PORT(com),SERIAL_LINE_ENABLE_DLAB);
	outb(SERIAL_DATA_PORT(com),divisor&0x00FF);
	outb(SERIAL_DATA_PORT(com+1),(divisor>>8)&0x00FF);
}

void serial_configure_line(unsigned short com)
{
	outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

void serial_configure_buffer(unsigned short com)
{
    outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
}

void serial_configure_modem(unsigned short com)
{
    outb(SERIAL_MODEM_COMMAND_PORT(com), 0x3B);
}

unsigned char read_serial(unsigned short com)
{
	while((inb(SERIAL_LINE_STATUS_PORT(com))&1)==0);

	return inb(SERIAL_DATA_PORT(com));
}

void write_serial(unsigned short com)
{
	while((inb(SERIAL_LINE_STATUS_PORT(com))&0x20)==0);

	outb(SERIAL_DATA_PORT(com),'A');
}