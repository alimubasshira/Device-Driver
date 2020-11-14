obj-m := add.o 

#native compiler
KERNELDIR = /lib/modules/$(shell uname -r)/build/
#KERNELDIR = /usr/src/linux-headers-5.4.0-48-generic/

PWD := $(shell pwd)

default :
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean  : 
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

install :
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
	depmod -a


