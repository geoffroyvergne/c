obj-m += lkm_simple_example.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
test:
	sudo dmesg -C
	sudo insmod lkm_simple_example.ko
	sudo rmmod lkm_simple_example.ko
	dmesg