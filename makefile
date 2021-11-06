GPPPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore #except -m32 all of them are to tell that there is no OS outside my prog
ASPARAMS = --32 
LDPARAMS = -melf_i386

objects = loader.o kernel.o

%.o: %.cpp
	g++ $(GPPPARAMS) -o $@ -c $<  # call g++ wd params, opt shoudl be target file($@) and we wanna compile (-c) the ipt file ($<). 
	
%.o: %.s
	as $(ASPARAMS) -o $@ $<
	
mykernel.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)
	
install: mykernel.bin
	sudo cp $< /boot/mykernel.bin #copying mykernel.bin to the given path.
