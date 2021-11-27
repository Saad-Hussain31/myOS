GPPPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore #except -m32 all of them are to tell that there is no OS outside my prog
ASPARAMS = --32 
LDPARAMS = -melf_i386

objects = loader.o gdt.o port.o interrupts.o interruptsstubs.o kernel.o

%.o: %.cpp
	g++ $(GPPPARAMS) -o $@ -c $<  # call g++ wd params, opt shoudl be target file($@) and we wanna compile (-c) the ipt file ($<). 
	
%.o: %.s
	as $(ASPARAMS) -o $@ $<
	
mykernel.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)
	
install: mykernel.bin
	sudo cp $< /boot/mykernel.bin #copying mykernel.bin to the given path.

mykernel.iso: mykernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/
	echo  'set timeout=0' >> iso/boot/grub/grub.cfg
	echo  'set default=0' >> iso/boot/grub/grub.cfg
	echo  '' >> iso/boot/grub/grub.cfg
	echo  'menuentry "My OS" {' >> iso/boot/grub/grub.cfg
	echo  '   multiboot /boot/mykernel.bin' >> iso/boot/grub/grub.cfg
	echo  '   boot' >> iso/boot/grub/grub.cfg
	echo  '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso #mkrescue to create a disk image. 
	rm -rf iso #after creating disk image we dont need iso directory so we delete it.

run: mykernel.iso
	(killall VirtualBox && sleep 1) || true   #sleep 1 bcz killall is slow so before killing it, new Vm might start so we wait for few seconds
	VirtualBox --startvm 'my OS'  & # & is for making it a background process

.PHONY: clean
clean:
	rm -f $(objects) mykernel.bin mykernel.iso
	