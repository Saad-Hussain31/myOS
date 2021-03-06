#include "types.h"
#include "port.h"

/*Implementing Class 1.
Constructor: initializing object with provided portnumber.*/

Port::Port(uint16_t portnumber)
{
    this->portnumber = portnumber;
}

Port::~Port()
{
}

//Implementation of Class 1 ends here.

//Implementing Class 2.

Port8Bit::Port8Bit(uint16_t portnumber)
: Port(portnumber)
{
}

Port8Bit::~Port8Bit()
{
}

void Port8Bit::Write(uint8_t data)
{
    /*volatile means the variable can be modified from outside. 
      It also stops the compiler from optimizing the code. */
    __asm__ volatile("outb %0, %1" : : "a" (data), "Nd" (portnumber));
}

uint8_t Port8Bit::Read()
{
    uint8_t result;
    __asm__ volatile("inb %1, %0" : "=a" (result) : "Nd" (portnumber));
    return result;
}

//Implementation of Class 2 ends here.

//Implementing Class 2.5.

Port8BitSlow::Port8BitSlow(uint16_t portnumber)
: Port8Bit(portnumber)
{
}

Port8BitSlow::~Port8BitSlow()
{
}

void Port8BitSlow::Write(uint8_t data)
{
    __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:" : : "a" (data), "Nd" (portnumber));
}

//Implementation of Class 2.5 ends here.

//Implementing Class 3.

Port16Bit::Port16Bit(uint16_t portnumber)
: Port(portnumber)
{
}

Port16Bit::~Port16Bit()
{
}

void Port16Bit::Write(uint16_t data)
{
    __asm__ volatile("outw %0, %1" : : "a" (data), "Nd" (portnumber));
}

uint16_t Port16Bit::Read()
{
    uint16_t result;
    __asm__ volatile("inw %1, %0" : "=a" (result) : "Nd" (portnumber));
    return result;
}

//Implementation of Class 3 ends here.

//Implementing Class 4.

Port32Bit::Port32Bit(uint32_t portnumber)
: Port(portnumber)
{
}

Port32Bit::~Port32Bit()
{
}

void Port32Bit::Write(uint32_t data)
{
    __asm__ volatile("outl %0, %1" : : "a" (data), "Nd" (portnumber));
}

uint32_t Port32Bit::Read()
{
    uint16_t result;
    __asm__ volatile("inl %1, %0" : "=a" (result) : "Nd" (portnumber));
    return result;
}
//Implementation of Class 4 ends here.
