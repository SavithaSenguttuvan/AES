obj-m += LED_Char_Module.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules
	$(CC) LED_Char_Module_Test.c -o test
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean	
	rm test



	

 