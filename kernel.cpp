#include "gdt.h"
#include "types.h"
#include "interrupts.h"
void printf(char* str)
{
	unsigned short* VideoMemory = (uint16_t*)0xb8000;

	static uint16_t x=0, y = 0; //cursor

	for(int i = 0; str[i] != '\0'; ++i)
	{
		switch(str[i])
		{
			case '\n': //line feed
				y++;
				x = 0;
				break;
			default:
				VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
				x++;
				break;
		}
		

		if(x >= 80) //if x is behind right corner of screen
		{
			y++; //jump to next line
			x = 0; //reset x
		}
		if (y >= 25)
		{
			for (y = 0; y <25; y++)
				for(x= 0; x < 80; x++)
					VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';//reset screem to empty spave character
			x = 0;
			y = 0;
		}
	}
}


extern "C" void kernelMain(void*  multiboot_structure, uint32_t /*multiboot_magic*/)
{
	printf("Hello World, this is my Operating system\n");
	printf("Hello World, this is my Operating system\n");
	printf("Hello World, this is my Operating system\n");
	GlobalDescriptorTable gdt;
	InterruptManager interrupts(&gdt);
	interrupts.Activate();
	while(1); //inf loop to prevent kernel from stopping
}
