#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/fs.h>
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
	printk("Sample Open function\n");
	return 0;
}
static int sample_close(struct inode *inodep, struct file *filep)
{
	printk("sample Close function\n");
	return 0;
}
static ssize_t sample_read(struct file *filep, char __user *ubuff, size_t cnt, loff_t * offset)
{
	/*char kbuff[] = "hello user";
	int stat;
	ssize_t ret;

	printk("in read\n");

        stat = copy_to_user(ubuff, kbuff,count);
        if(stat == 0)
        {
                printk("sucessfully send messager from kernel \n");
                ret = count;
                return ret;
        }
        else if(stat > 0)
        {
                printk("some content left to send\n");
                ret = count-stat;
                return ret;
        }
        else
        {
                printk("Fail to send message\n");
                ret = -EFAULT;
                return ret;
        }*/
	printk("in read\n");
	return 0;
}
static ssize_t sample_write(struct file *filep, const char __user * ubuff, size_t cnt, loff_t *offset)
{
	printk("Sample Write\n");
	return 0;
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
//	devnum =MKDEV(42,0); // is used for constructing a device number
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
	cdev_del(&_cdev);
	unregister_chrdev_region(devnum,1);
	printk("Good bye\n");
}
module_init(sample_init);
module_exit(sample_exit);
