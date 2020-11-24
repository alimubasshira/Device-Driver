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
static ssize_t add_read(struct file *filep, char __user *ubuff, size_t cnt, loff_t * offset)
{
	ssize_t i;
	i=cnt;
	printk("In read function\n");

	printk("No of byte user want: %d\n",(int)cnt);		
	
	ret=copy_to_user(ubuff,add);
	if(ret)
	{
	    printk("error copy_to_user \n");
	    return -1;
	}

        printk("no of byte successfully read data from kernel: %d\n",i);
	return cnt;
}
static ssize_t add_write(struct file *filep, const char __user * ubuff, size_t cnt, loff_t *offset)
{
	ssize_t i;
	i=cnt;
	printk("In Write function\n");
          
        
        printk("data write by user:");
	return cnt;       

}
struct file_operations fops1={
	.open    = sample_open,
	.release = sample_close,
	.read    = add_read,
	.write   = add_write,
}; 

struct file_operations fops2={
        .open    = sample_open,
        .release = sample_close,
        .read    = sub_read,
        .write   = sub_write,
};

struct file_operations fops3={
        .open    = sample_open,
        .release = sample_close,
        .read    = mul_read,
        .write   = mul_write,
};

struct file_operations fops4={
        .open    = sample_open,
        .release = sample_close,
        .read    = div_read,
        .write   = div_write,
};

static int __init sample_init(void)
{
	int ret,major,minor; 
	printk("In init function\n");

	ret = alloc_chrdev_region(&devnum,0,4,"dev04");// request the kernel
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
