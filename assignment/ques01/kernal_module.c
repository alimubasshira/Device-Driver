/*
 * A charachter driver with open and close functionality
*/

#include<linux/init.h>
#include<linux/module.h>
#include<linux/types.h>
#include<linux/cdev.h>
#include<linux/fs.h>

#define NAME mycDevice

//function prototypes
int NAME_open(struct inode *inode, struct file *file);
int NAME_release(struct inode *inode, struct file *file);

//structure that defines operation
struct file_operations fops=
{
	.owner   = THIS_MODULE,
	.open    = NAME_open,
	.release = NAME_release,

};

//Structure for character driver
struct cdev *my_cdev;

//initialization module
static int __init init_fun (void)
{
	int status,no_of_device = 1;
	int major,minor;
 
 	//mkdev(int major, int minor);   create a device number
 	dev_t mm;
        mm    = MKDEV(3,0);
	major = MAJOR(mm);
	minor = MINOR(mm);
        	
	printk("Register device with\nMajor number:%d\nMinor number:%d",major,minor);

 	//register_chardev_region(dev_t first, int no_of_device, char* name_of_file);
 	status = register_chrdev_region(mm, no_of_device, "mydevice");
 	if(status == 0)
 	{
	 	printk("successfull register\n");
 	}
 	else
 	{
	 	printk("not register\n");
	 	return -1;
 	}

	//allocate memory to char device structure
	my_cdev = cdev_alloc();

	//initializing char device with file operations
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
	mm = MKDEV(3,0);

  	unregister_chrdev_region(mm, 1);
	cdev_del(my_cdev);
  	printk ("mydevice driver unloaded ...\n");
}

//open system call
int NAME_open(struct inode *inode, struct file *file)
{
       printk("IN kernel space.......in open call\n");
       return 0;       
}

//release system call
int NAME_release(struct inode *inode, struct file *file)
{
       printk("IN kernel space.......in release call\n");
       return 0;       
}



//module function calls

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mubasshira");
module_init(init_fun);
module_exit(exit_fun);
