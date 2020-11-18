obj-m := kernal_module.o 

#native compiler
KERNELDIR = /lib/modules/$(shell uname -r)/build/

PWD := $(shell pwd)

default :
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean  :
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm -rf /lib/modules/$(shell uname -r)/extra/

install :
	$(MAKE) -C $(KERNELDIR) M=$(PWD) install
	depmod -a

