
#include "gdt.h"
#include "types.h"
void printf(char* str)
{
	unsigned short* VideoMemory = (uint16_t*)0xb8000;
	for(int i = 0; str[i] != '\0'; ++i)
		VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i];

}


extern "C" void kernelMain(void*  multiboot_structure, uint32_t /*multiboot_magic*/)
{
	printf("Hello World, this is my Operating system");
	GlobalDescriptorTable gdt;
	while(1); //inf loop to prevent kernel from stopping
}
