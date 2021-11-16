
#include "gdt.h"

//initializing constructor
GlobalDescriptorTable::GlobalDescriptorTable()
: nullSegmentSelector(0,0,0),
unusedSegmentSelector(0,0,0),
codeSegmentSelector(0,64*1024*1024, 0x9A), //start at 0, takes 64MBs for segment size
dataSegmentSelector(0,64*1024*1024, 0x92) //all this creates the table

//telling processor to use the table
{
    uint32_t i[2]; //we have 8 bytes or 32 bits
    i[0] = (uint32_t)this; //these 1st 4 bytes is the addr of table itself
    i[1] = sizeof(GlobalDescriptorTable) << 16; //these 4 bytes are hi-bytes of seg integer

    //execute 1 line of assembler for telling processor
    asm volatile("lgdt (%0)": :"p" (((uint8_t *) i)+2)); //loading gdt 

}
GlobalDescriptorTable::~GlobalDescriptorTable() //it should unload the gdt, but empty for now
{
}

//we need offsets datasegment selector and code segment selector
uint16_t GlobalDescriptorTable::DataSegmentSelector()
{
    return (uint8_t*)&dataSegmentSelector - (uint8_t*)this;
}

uint16_t GlobalDescriptorTable::CodeSegmentSelector()
{
    return (uint8_t*)&codeSegmentSelector - (uint8_t*)this;
}

//need to set the entries a/c to parameters we get from above 2 functions
GlobalDescriptorTable::SegmentDescriptor::SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t flags)
{
    //casting to array of bytes and setting bytes explicitly
    uint8_t* target = (uint8_t*)this;

    //case 1: if limit is 16 bits, set 6th byte
    if(limit <= 65536)
    {
	target[6] = 0x40;
    }
    //otherwise, if last 12 bts are not 1 then we decrease the lim by 1(giving us extra space)
    else 
    {
    	if((limit & 0xFFF) != 0xFFF)
	    limit = (limit >> 12)-1;
	else
	    limit = limit >> 12;

	target[6] = 0xC0;

    }

    target[0] = limit & 0xFF; //last byte(from RHS) is gonna be LSB of limit
    target[1] = (limit >> 8) & 0xFF;
    target[6] |= (limit >> 16) & 0xF; //setting lower 4 bits using |

    target[2]=  base & 0xFF;
    target[3]= (base >> 8) & 0xFF;
    target[4]= (base >> 16) & 0xFF;
    target[7]= (base >> 24) & 0xFF;

    target[5] = flags; //setting access rights
}

//given just a starting pointer, we wanna have location of each byte. easy. 
uint32_t GlobalDescriptorTable::SegmentDescriptor::Base()
{
    uint8_t* target = (uint8_t*)this;
    uint32_t result = target[7]; //take 7th byte and shift it to left
    result = (result << 8) + target[4]; 
    result = (result << 8) + target[3];
    result = (result << 8) + target[2];
    return result;
}

uint32_t GlobalDescriptorTable::SegmentDescriptor::Limit()
{
    uint8_t* target = (uint8_t*)this;
    uint32_t result = target[6] & 0xF; //first taking low 4 bits of shared byte
    result = (result << 8) + target[1];
    result = (result << 8) + target[0];

    if((target[6] & 0xC0) == 0xC0) //handling for case 1
	    result = (result << 12) | 0xFFF;
    return result;
}


