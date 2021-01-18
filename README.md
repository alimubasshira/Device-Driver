# Device-Driver
Day-1 : 
Classification of Embedded system programming
 * hardwaired 
   * bare-metal programming
     ex- blinking led
 * two tiered architecture
   * user application + embedded OS/kernel
     ex- automatic washing machine
 * Three tiered architecture
   *   user space
      OS/kernel space
      ex- gamming device

Toolchain for kernel/Device driver built process
  * Compiler
    * Native compiler - gcc
    * Cross compiler  - keil
    * cross - native compiler
    
  * Debugger
    * gcc -g hello.ko -----> kgdb hello
    * debugger -target-in-line  (hardware debugger)
      debug code with harware in target and gdb in host
      
           HOST        TARGET
           gdb         jtag 
           
      * JTAG- joint test action group
      * SWD - single wire debugger
    * linux trace toolkit
      it understand the flow sequence & events
      
      
Day-2 :
what is toolchain?
* It is a combination of tool as-
  * Binary utility
     * as (assembler)
     * ld (linker)
     * objcopy/objdump (deassembler)
  * gcc (compiler)
  * header
  * libraries for c development
  * debugger

what is ABI?

 * An ABI is a set of rules that determines calling convention, and rules for laying out structures,
 * It gives info about how to store function with its args and parameter in file so, seraching for that function is easy 
 * It tells how to locate what it needs inside the library file.
 * ABI is platfrom dependent but not language independent
 * https://stackoverflow.com/questions/2171177/what-isabi-an-application-binary-interface-

 * you Actually don't need an ABI at all if-
   * Your program doesn't have functions
   * Your program is a single executable that is running alone (i.e. an embedded system) 
     where it's literally the only thing running and it doesn't need to talk to anything else.

Board support development
 * Bootloader
   * It is peice of code which prepare hardware for kernel ready
   * It is done in minimum 2 stages
     * 1 stage : small code that boot the main bootloader 
              ex- BIOS
     * 2 stage : it perform hardware initialization(ethernet,timers, clocks, etc),provide info about location of filesystem of kernel to be loaded, pass necessary arguments to                   kernel and transfer control to kernel. '
              ex- GRUB, UBOOT,
 * kernel
 
 * perpheral derivers
 
 * Rootfile system
   It is format which specifies how files of system to be stored
    * linux   - EXT2/3/4        (extended file system)
    * windows - FATxx           (file allocator table)
    * apple   - HFS, HFS+, APFS (Hierarchical File System) 

Day-3:
* kernel - it is a core component of operating system which manages resources, Nature of a kernel is reactive it wait until work request come
  * types of kernel
    * monolithic kernel
    * micro kernel

* module programming : (code)
  * it is very difficult to provide every functionality to kernel at the time of boot so it provide adding functionality dynamically
  * every thing in linux is a module 
  * there are two types of module
    * static module  (can't be remove )
    * dynamic module (can be added and remove at any time)
  * process of creating and inserting module
    * module initialization
      @ hello.c --> module_init()
    * module removing
      @ hello.c --> module_exit()
    * compilation and loading
      @ makefile 
    * utilites to veiw/manage/remove module
      * insmod
      * lsmod  lsmod works by reading the /proc/modules virtual file. 
               Information on currently loaded modules can also be found in the sysfs virtual filesystem under /sys/module.
      * rmmod
      * dmesg -c
      * user -r
  
Day-4 : (code)
  * The message goes to one of the system log files, such as /var/log/messages (the name of the actual file varies between Linux distributions).
  * command line argument to module
    * module parameter       --> module_param(name , type, permission)
    * module array parameter --> module_array_param(name of varable, & no of element passed, type, permision )
  * As there is no shared object(libc ,.so)kind of think in kernel we have symbol table
  * kernel symbol table - is resolve each symbols in our program by using symbol table
    * inserting multiple module --> modprobe is used
    * modprobe  --> module.dep file 
    * depmod -a --> update module.dep (extra ---> .ko)
    * EXPORT_SYMBOL_GPL(fun_name / var_name)
    
Day-5 :
Device Driver
  * https://embetronicx.com/tutorials/linux/device-drivers/device-file-creation-for-character-drivers/
  * http://www.makelinux.net/ldd3/?u=chp-1.shtml 

*  reentrant—it must be capable of running in more than one context at the same time.

* We can create the device file manually by using mknod.
    mknod -m <permissions> <name> <device type> <major> <minor>
* We can allocate the major and minor numbers in two ways.
    * Statically allocating
        int register_chrdev_region(dev_t first, unsigned int count, char *name);
        return 0 on success
    * Dynamically Allocating  
        int alloc_chrdev_region(dev_t *dev, unsigned int firstminor, unsigned int count, char *name);
        dev is an output-only parameter that will, on successful completion, hold the first number in your allocated range.
    
*  dev_t is a 32-bit quantity with 12 bits set aside for the major number and 20 for the minor number.    

* Dallocation of major and minor numbers 
    void unregister_chrdev_region(dev_t first, unsigned int count);

* We can create a divce file in two ways.
    * Manually
        mknod -m <permissions> <name> <device type> <major> <minor>
        If you don’t want to give permission, You can also use chmod to set the permissions for a device file after creation.
    * Automatically
        * Include the header file linux/device.h and linux/kdev_t.h
        * Create the struct Class
            This will create the struct class for our device driver. It will create a structure under/sys/class/.
                struct class * class_create (struct module *owner, const char *name);
            the pointer created here is to be destroyed when finished by making a call to class_destroy.
                void class_destroy (struct class * cls);
        * Create Device with the class which is created by the above step
             This function can be used by char device classes. A struct device will be created in sysfs, registered to the specified class.
                struct device *device_create (struct *class, struct device *parent, dev_t dev, const char *fmt, ...);
             you can destroy the device using device_destroy().
                void device_destroy (struct class * class, dev_t devt);
*  There are two ways of allocating and initializing one of these structures.
    * Runtime Allocation
          struct cdev *my_cdev = cdev_alloc( );
          my_cdev->ops = &my_fops;
    * Own allocation
          void cdev_init(struct cdev *cdev, struct file_operations *fops);
  
* the final step is to tell the kernel about it with a call to: 
    int cdev_add(struct cdev *dev, dev_t num, unsigned int count);
  
* To remove a char device from the system, call:
    void cdev_del(struct cdev *dev);  

* kmalloc function is used to allocate the memory in kernel space. This is like a malloc() function in userspace. The function is fast (unless it blocks) and doesn’t clear the memory it obtains. The allocated region still holds its previous content. The allocated region is also contiguous in physical memory.
 
* This is like a free() function in the userspace. This is used to free the previously allocated memory.
    void kfree(const void *objp)
    
* copy_from_user()
    This function is used to Copy a block of data from user space (Copy data from user space to kernel space).
    unsigned long copy_from_user(void *to, const void __user *from, unsigned long  n);  

* copy_to_user()
    This function is used to Copy a block of data into userspace (Copy data from kernel space to user space).
    unsigned long copy_to_user(const void __user *to, const void *from, unsigned long  n);
  
  
  
  
  
  
  
  
  
  
  
