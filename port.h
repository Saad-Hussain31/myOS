#ifndef __PORT_H
#define __PORT_H
#include "types.h"


/* Class 1:purely virtual Port base class which knows its port num. 
Constructor is also protected bcz I dont want it to be
instantiated. */ 
class Port 
{
protected: 
	uint16_t portnumber;
	Port(uint16_t portnumber);
	~Port();
};


// Class 2: Used by multiplexers to read & write 8-bits integers. 
class Port8Bit : public Port
{
public:
	Port8Bit(uint16_t portnumber);
	~Port8Bit();
	virtual void Write(uint8_t data);
	virtual uint8_t Read();
};

//also 8bits but slower so it needs it's own write()
class Port8BitSlow : public Port8Bit
{
public:
	Port8BitSlow(uint16_t portnumber);
	~Port8BitSlow();
	virtual void Write(uint8_t data);
	//I will inherit read() so not overriding it
};


// Class 3: Used by multiplexers to read & write 16-bits integers.
class Port16Bit : public Port
{
public:
	Port16Bit(uint16_t portnumber);
	~Port16Bit();
	virtual void Write(uint16_t data);
	virtual uint16_t Read();
};

// Class 4: Used by multiplexers to read & write 32-bits integers.

class Port32Bit : public Port
{
public:
	Port32Bit(uint32_t portnumber);
	~Port32Bit();
	virtual void Write(uint32_t data);
	virtual uint32_t Read();
};

#endif
