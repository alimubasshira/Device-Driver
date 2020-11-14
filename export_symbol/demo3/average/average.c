#include<linux/init.h>
#include<linux/module.h>
#include<linux/stat.h>
#include<linux/kernel.h>
//#include"header.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("mubbu");

static int add_fun(int a,int b);
int a[2]={0,0},arr_argc;
module_param_array(a, int, &arr_argc, S_IRUGO);

static void average_fun(int a,int b)
{
   printk("average = %d\n", add_fun(a,b)/2);
}


static int init_fun(void)
{

   printk(KERN_ALERT"inside average  init module \n");
   average_fun(a[0],a[1]);
   return 0;
}

static void  exit_fun(void)
{

 printk(KERN_ALERT"exit from  average module\n");

}


module_init(init_fun);
module_exit(exit_fun);


