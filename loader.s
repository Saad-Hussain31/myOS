.set MAGIC, 0x1badb002 #the bootloader sees this magic number and recognizes that ur program is kernel.
.set FLAGS, (1<<0 | 1<<1) #these 3 are compiler vars and wont be the part of .o file. we need to explicitly include them which we do in next multiboot section below.
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot 
	.long MAGIC 
	.long FLAGS 
	.long CHECKSUM
	

.section .text
.extern kernalMain #this tells the assembler that theres something called kernalMain outside of this file. Linker will take care of it. 
.global loader #program entry point

loader:
	mov $kernel_stack, %esp #settng the stack pointer to some stack (from where we wanna start it).
	
	
	push %eax 
	push %ebx
	call kernelMain
	

	
.section .bss
.space 2*1024*1024;  #providing some extra space bcz stack pointer will overwrite stuff in RAM.


kernel_stack: #this is the pointer where stack pointer is set 
