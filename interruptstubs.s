.set IRQ_BASE, 0X20 
.section .text


.extern _ZN16InterruptManager15handleInterruptEhj #this comes from making obj file.
.global _ZN16InterruptManager22IgnoreInterruptRequestEv


.macro HandleException num
.global _ZN16InterruptManager16HandleInterruptRequest\num\()Ev #this creates the implementation of forwarded declared funcs in interrupts.h
_ZN16InterruptManager16HandleInterruptRequest\num\()Ev:
    movb $\num, (interruptnumber)
    jmp int_bottom
.endm


.macro HandleInterruptRequest num
.global _ZN16InterruptManager26HandleInterruptRequest\num\()Ev #this creates the implementation of forwarded declared funcs in interrupts.h
_ZN16InterruptManager26HandleInterruptRequest\num\()Ev:    
    movb $\num + IRQ_BASE, (interruptnumber) #adding content of compiler variable to the num
    jmp int_bottom
.endm



HandleInterruptRequest 0x00 
HandleInterruptRequest 0x01

int_bottom: # given esp, itll jump in handleIntr func 

# store old vals of regs   
    pusha
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs

# push vals in stack and jump into intrhandler func. (old vals are stored)
    push %esp 
    push (interruptnumber)
    call _ZN16InterruptManager15handleInterruptEhj #calling method
# addl $5,%esp we have to pop old esp & intr# but in next statement we are getting return val from func, so no need to do this
    movl %eax, %esp

# restoring back in reverse order coz stack.
    popl %gs
    popl %fs
    popl %es
    popl %ds
    popa

_ZN16InterruptManager22IgnoreInterruptRequestEv:

#telling processor that interrupt handling is finished
    iret

.data 
    interruptnumber: .byte 0 #interrupt# for timer is initialized to 0






