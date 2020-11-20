/*
 * This program implements basic functionality of char driver.
*/

#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/cdev.h>
#include<linux/fs.h>
#include<linux/uaccess.h>
#define NAME mycDevice

//function prototypes
static int NAME_open(struct inode *inode, struct file *file);
static int NAME_release(struct inode *inode, struct file *file);
static ssize_t NAME_write(struct file *file,const char __user *ubuff, size_t count, loff_t *offp);
static ssize_t NAME_read(struct file *file, char  __user *ubuff, size_t count, loff_t *offp);

//structure that defines operation
struct file_operations fops=
{
	.owner   = THIS_MODULE,
	.open    = NAME_open,
	.read    = NAME_read,
	.write   = NAME_write,
	.release = NAME_release,

};

//Structure for character driver
static struct cdev *my_cdev;

//initialization module
static int __init init_fun (void)
{
	int status,count = 1;
	int major,minor;
 
 	//mkdev(int major, int minor);   create a device number
 	dev_t mm;
        mm    = MKDEV(2,0);
	major = MAJOR(mm);
	minor = MINOR(mm);
        	
	printk("Major number:%d\nMinor number:%d",major,minor);

 	//register_chardev_region(dev_t first, int no_of_device, char* name_of_file);
 	status = register_chrdev_region(mm, count, "device02");
 	if(status == 0)
 	{
	 	printk("successfull register\n");
 	}
 	else
 	{
	 	printk("not register\n");
	 	return -1;
 	}

	//initializing char device with file operations
	//cdev_init(my_cdev,&fops);
	my_cdev = cdev_alloc();

        my_cdev -> ops = &fops;
        
	//notify kernel about the new device
	status = cdev_add(my_cdev, mm,1);
	if(status < 0)
	{
		printk("char device not been created\n");
		unregister_chrdev_region(mm, 1);
		return -1;
	}
 	return 0;

}

//clean up module/ exit module
static void __exit exit_fun ( void )
{
 	dev_t mm ;
	mm = MKDEV(2,0);
  	unregister_chrdev_region(mm, 1);
	cdev_del(my_cdev);
  	printk ("mydevice driver unloaded ...\n");
}

//open system call
static int NAME_open(struct inode *inode, struct file *file)
{
       printk("IN kernel space.......in open call\n");
       return 0;       
}

//release system call
static int NAME_release(struct inode *inode, struct file *file)
{
       printk("IN kernel space.......in release call\n");
       return 0;       
}

//write system call
static ssize_t NAME_write(struct file *file,const  char __user *ubuff, size_t count, loff_t *offp)
{
	int stat;
	char kbuff[10];
	ssize_t ret;
        printk("IN kernel space.......in write call\n");
	//copies data fron user buffer to kernel buffer
        stat = copy_from_user(kbuff,ubuff,count);
        if(stat == 0)
	{
        	printk("sucessfully written in kernal\n");
		printk("message from user : %s\n",kbuff);
		ret = count;
		return ret;
	}
	else if(stat > 0)
	{
        	printk("some content didn't written\n");
		ret = count;
		return count;
	}
	else
	{
        	printk("Fail to write\n");
		ret = -EFAULT;
		return ret;
	}
    
}

//read system call
static ssize_t NAME_read(struct file *file,char __user *ubuff, size_t count, loff_t *offp)
{
	ssize_t ret;
	char kbuff[]= "hey....I am kerenel";
	int stat;
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
	}

}

//module function
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mubasshira");
module_init(init_fun);
module_exit(exit_fun);
