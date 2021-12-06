.set IRQ_BASE, 0X20 
.section .text


.extern _ZN16InterruptManager15handleInterruptEhj #this comes from making obj file.



.macro HandleException num
.global _ZN16InterruptManager16handleInterruptRequest\num\()Ev #this creates the implementation of forwarded declared funcs in interrupts.h
    movb $\num, (interruptnumber)
    jmp int_bottom
.endm


.macro HandleInterruptRequest num
.global _ZN16InterruptManager26handleInterruptRequest\num\()Ev #this creates the implementation of forwarded declared funcs in interrupts.h
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

#telling processor that interrupt handling is finished
    iret

.data 
    interruptnumber: .byte 0 #interrupt# for timer is initialized to 0






