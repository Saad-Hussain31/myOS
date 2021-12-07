#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H
#include "types.h"
#include "port.h"
#include "gdt.h"


class InterruptManager
{
    protected:
    struct GateDescriptor
    {
        uint16_t handlerAddressLowBits;
        uint16_t gdt_codeSegmentSelector;
        uint8_t reserved;
        uint8_t access;
        uint16_t handlerAddressHighBits;
    }__attribute__((packed));

    static GateDescriptor interruptDescriptorTable[256];

    struct InterruptDescriptorTablePointer //table created, tell processor to use it
    {
        uint32_t base;
        uint32_t size;
    }__attribute__((packed));

    static void SetInterruptDecriptorTableEntry(
        uint8_t interruptNumber,
        uint16_t codeSegmentSelectorOffset,
        void (*handler) (), //pointer to handler
        uint8_t DescriptorPrivilegeLevel, //for access rights
        uint8_t DescriptorType //for flags
    );

    //we have to tell PIC to send us interrupt
    Port8BitSlow picMasterCommand;
    Port8BitSlow picMasterData;
    Port8BitSlow picSlaveCommand; 
    Port8BitSlow picSlaveData;



    public: 
    InterruptManager(GlobalDescriptorTable* gdt);
    ~InterruptManager();

    void Activate();

    static uint32_t handleInterrupt(uint8_t interruptNumber, uint32_t esp);
    static void IgnoreInterruptRequest();
    static void HandleInterruptRequest0x00(); //intr for timer
    static void HandleInterruptRequest0x01(); //inr for keyboard
    

};


#endif