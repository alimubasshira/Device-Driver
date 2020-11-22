#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DD");
/*
 * This that are needed for char device
 * 1. device number;  device number is used by Linux to identify the device
 * 2. cdev structure; kernel representation of char device
 *    2.1 file_operations ; operations that can be done on your device
 *        /usr/src/<Your version Linux kernel>/include/linux/fs.h
 */

static dev_t devnum;      // device number
static struct cdev _cdev; // represents  char device 

static int sample_open(struct inode *inodep,struct file *filep)
{
	printk("In Open function\n");
	return 0;
}
static int sample_close(struct inode *inodep, struct file *filep)
{
	printk("In Close function\n");
	return 0;
}
static ssize_t sample_read(struct file *filep, char __user *ubuff, size_t cnt, loff_t * offset)
{
	ssize_t i;
	i=cnt;
	printk("In read function\n");

/*	printk("No of byte user want: %d\n",(int)cnt);		
		
	for(i=0; i<cnt; i++)
	{
	   ret=copy_to_user(ubuff+i, cbuff.buf+cbuff.tail, 1);
	   if(ret)
	   {
	   	printk("error copy_to_user \n");
		return -1;
	   }
           cbuff.tail=(cbuff.tail+1)&(SIZE-1);
	}

        printk("no of byte successfully read data from kernel: %d\n",i);
*/
	return cnt;
}
static ssize_t sample_write(struct file *filep, const char __user * ubuff, size_t cnt, loff_t *offset)
{
	ssize_t i;
	i=cnt;
	printk("In Write function\n");
/*
	for(i=0; i<cnt; i++)
	{
	   ret=copy_from_user(cbuff.buf+cbuff.head, ubuff+i, 1);
	   if(ret)
           {
                printk("error copy_to_user \n");
                return -1;
           }
	   cbuff.head=(cbuff.head+1)&(SIZE-1);		
	}
       
        printk("data write by user:");
	for(j=cbuff.tail; j < cbuff.head; j++)
	{
		printk("%c",cbuff.buf[j]);
	}  
*/	
	return cnt;       

}
struct file_operations fops={
	.open    = sample_open,
	.release = sample_close,
	.read    = sample_read,
	.write   = sample_write,
}; //Designated initialisation of a structure;

static int __init sample_init(void)
{
	int ret,major,minor; 
	printk("In init function\n");

	ret = alloc_chrdev_region(&devnum,0,1,"dev04");// request the kernel
	if(ret)
	{  //non zero means not successfull
		printk("Kernel did't grant us device number\n");
		return ret;
	}

	major = MAJOR(devnum);
        minor = MINOR(devnum);
	printk("device no:%d %d\n",major,minor);

	//Control : we got device number
	cdev_init(&_cdev,&fops); // Binds your cdev with file operations
	
	ret = cdev_add(&_cdev,devnum,1); //Device is "Live" Now
	if(ret)
	{
		printk("Unable to add cdev to kernel\n");
		unregister_chrdev_region(devnum,1);
		return ret;
	}
	printk("Done Init\n");
	return 0;
}
static void __exit sample_exit(void)
{
	printk("In exit function\n");
	cdev_del(&_cdev);
	unregister_chrdev_region(devnum,1);
	printk("done exit\n");
}
module_init(sample_init);
module_exit(sample_exit);
