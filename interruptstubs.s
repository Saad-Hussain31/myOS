.section .text


.extern _ZN16InterruptManager15handleInterruptEhj #this comes from making obj file.


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






