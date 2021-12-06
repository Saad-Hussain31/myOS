#include "interrupts.h"



void printf(char* str);
    
InterruptManager::GateDescriptor InterruptManager::interruptDescriptorTable[256];

void  InterruptManager::SetInterruptDecriptorTableEntry(
        uint8_t interruptNumber,
        uint16_t codeSegmentSelectorOffset,
        void (*handler) (),
        uint8_t DescriptorPrivilegeLevel,
        uint8_t DescriptorType)
{
    
}


InterruptManager::InterruptManager(GlobalDescriptorTable* gdt)
{
    #if we get an interrupt and we dont have handler for it then it should go through IgnoreInterrupt method. OS crashes!

}
InterruptManager::~InterruptManager;
{

}

uint32_t InterruptManager::handleInterrupt(uint8_t interruptNumber, uint32_t esp)
{
    printf(" INTERRUPT");
    return esp;
}