#include<linux/init.h>
#include<linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mubasshira");

//declared variable as static to limit its scope within the module
static char* var1 = "mubbu";
static int   var2 = 10;


module_param(var1, charp, S_IRUGO);
module_param(var2, int, S_IRUGO);

static int init_param(void)
{
 printk("In init function\n"); 
 printk("parameter1 = %s\nparameter2 = %d",var1,var2);
 return 0;

}

static void exit_param(void)
{
 printk("good bye from exit function\n");

}

module_init(init_param);
module_exit(exit_param);
