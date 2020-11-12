#include<linux/init.h>
#include<linux/module.h>
#include<linux/stat.h>
#include<linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mubasshira");

//declared variable as static to limit its scope within the module
static int var[3] = {0,0,0};
static int arr_argc = 0;

module_param_array(var, int, &arr_argc, S_IRUGO);


static int init_param_array(void)
{
 printk("In init function\n"); 

// for(int i=0; i < (sizeof(var)/sizeof(int)); i++)
// {
   printk("parameter[%d] = %d\n",0,var[0]);
// }
   printk("no of argrument = %d\n",arr_argc);
  
   return 0;

}

static void exit_param_array(void)
{
 printk("good bye from exit function\n");

}

module_init(init_param_array);
module_exit(exit_param_array);

/*
 * module_param_array(name, type, num, perm);
 * The first param is the parameter's (in this case the array's) name
 * The second param is the data type of the elements of the array
 * The third argument is a pointer to the variable that will store the number 
 * of elements of the array initialized by the user at module loading time
 * The fourth argument is the permission bits
 */
