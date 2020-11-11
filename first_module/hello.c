#include<linux/init.h>
#include<linux/module.h>

//module_licence("GPL");

static int init_hello (void)
{
 printk("welcome to world\n");
 return 0;

}

static void exit_hello(void)
{
 printk("good bye world\n");

}

module_init(init_hello);
module_exit(exit_hello);
