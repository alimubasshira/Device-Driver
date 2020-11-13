#include<linux/init.h>
#include<linux/module.h>
#include<linux/stat.h>
#include<linux/kernel.h>
//#include"header.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("mubbu");

static int add_fun(int a,int b);

static void average_fun(int a,int b)
{
   printk("average = %d\n", add_fun(a,b)/2);
}


static int init_fun(void)
{

   printk(KERN_ALERT"inside average  init module \n");
   average_fun(10,20);
   return 0;
}

static void  exit_fun(void)
{

 printk(KERN_ALERT"exit from  average module\n");

}


module_init(init_fun);
module_exit(exit_fun);


