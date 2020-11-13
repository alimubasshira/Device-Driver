#include<linux/init.h>
#include<linux/module.h>
#include<linux/stat.h>
#include<linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("mubbu");

//static int add_fun(int a,int b)
static int add_fun(int a,int b)
{
   return a+b;
}

EXPORT_SYMBOL_GPL(add_fun);

static int __init init_fun(void)
{

   printk(KERN_ALERT"inside add init fun \n");
   printk("addition = %d\n",add_fun(2,3));
   return 0;
}

static void __exit  exit_fun(void)
{

 printk(KERN_ALERT"exit from add module\n");

}


module_init(init_fun);
module_exit(exit_fun);



