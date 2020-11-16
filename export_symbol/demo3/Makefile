##ifneq($(KERNELRELEASE),)
	obj-y := average/ add/

#native compiler
##else
	KERNELDIR = /lib/modules/$(shell uname -r)/build/

	PWD := $(shell pwd)

default :
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean  :
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

#endif

install :
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
	depmod -a

