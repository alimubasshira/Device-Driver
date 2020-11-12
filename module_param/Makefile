obj-m := arrayparam.o 
#-std = c99
#obj-m := demo.o

#native compiler
KERNELDIR = /lib/modules/5.4.0-48-generic/build/
#KERNELDIR = /usr/src/linux-headers-5.4.0-48-generic/

PWD := $(shell pwd)

default :
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean  : 
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

#       $(make) rm -rf  hello.mod.c hello.o hello.mod modules.order module.symvers hello.ko built-in.a hello.mod.o 


