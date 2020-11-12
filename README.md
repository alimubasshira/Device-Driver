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
      * lsmod
      * rmmod
      * dmesg -c
      * user -r
      
      
  
