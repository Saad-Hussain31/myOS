#include "interrupts.h"



void printf(char* str);
    
InterruptManager::GateDescriptor InterruptManager::interruptDescriptorTable[256];

void  InterruptManager::SetInterruptDecriptorTableEntry(uint8_t interruptNumber, uint16_t codeSegmentSelectorOffset, 
void (*handler) (), uint8_t DescriptorPrivilegeLevel, uint8_t DescriptorType)
{
    //entries
    const uint8_t IDT_DESC_PRESENT = 0x80; 
    interruptDescriptorTable[interruptNumber].handlerAddressLowBits = ((uint32_t) handler) & 0xFFFF;
    interruptDescriptorTable[interruptNumber].handlerAddressLowBits = (((uint32_t) handler) >> 16) & 0xFFFF;
    interruptDescriptorTable[interruptNumber].gdt_codeSegmentSelector = codeSegmentSelectorOffset;
    interruptDescriptorTable[interruptNumber].access = IDT_DESC_PRESENT | DescriptorType | (DescriptorPrivilegeLevel&3) << 5; //need only last 3 bits using &3
    interruptDescriptorTable[interruptNumber].reserved = 0;
}


InterruptManager::InterruptManager(GlobalDescriptorTable* gdt) 
: picMasterCommand(0x20), picMasterData(0x21), picSlaveCommand(0xA0), picSlaveData(0xA1)
{
    // if we get an interrupt and we dont have handler for it then it should go through IgnoreInterrupt method. OS crashes!
    uint16_t CodeSegment = gdt->CodeSegmentSelector();
    const uint8_t IDT_INTERRUPT_GATE = 0xE;

    //setting up entries in a loop
    for (uint16_t i = 0; i < 256; i++)
        SetInterruptDecriptorTableEntry(i, CodeSegment, &IgnoreInterruptRequest, 0, IDT_INTERRUPT_GATE);//ith entry, codeseg from gdt, adres of intrignr func, kernel space, type

    SetInterruptDecriptorTableEntry(0x20, CodeSegment, &HandleInterruptRequest0x01, 0, IDT_INTERRUPT_GATE);
    SetInterruptDecriptorTableEntry(0x21, CodeSegment, &HandleInterruptRequest0x01, 0, IDT_INTERRUPT_GATE);

    picMasterCommand.Write(0x11);
    picSlaveCommand.Write(0x11);
    picMasterData.Write(0x20);
    picSlaveData.Write(0x28);

    picMasterData.Write(0x04);
    picSlaveData.Write(0x02);

    picMasterData.Write(0x01);
    picSlaveData.Write(0x01);

    picMasterData.Write(0x00);
    picSlaveData.Write(0x00);

    //letting processor use th table
    InterruptDescriptorTablePointer idt;
    idt.size = 256 * sizeof(GateDescriptor) - 1;
    idt.base = (uint32_t)interruptDescriptorTable;
    asm volatile("lidt %0" : : "m" (idt));


}
InterruptManager::~InterruptManager()
{

}

void InterruptManager::Activate()
{
    asm ("sti");
}

uint32_t InterruptManager::handleInterrupt(uint8_t interruptNumber, uint32_t esp)
{
    printf("INTERRUPT");
    return esp;
}