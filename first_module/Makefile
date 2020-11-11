obj-m := hello.o

KERNELDIR = /lib/modules/$(shell uname -r)/built

PWD := $(shell pwd)

default :
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
