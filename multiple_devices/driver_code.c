#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/circ_buf.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/sched.h>
#include <linux/wait.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("DD");
#define SIZE 32
#define MAJORN 2
#define NMINORS 3

static dev_t devnum;      // device number
struct mydevice
{
	struct cdev _cdev;
	struct circ_buf cbuf; 
	wait_queue_head_t _wq;
}_devs[NMINORS];

static int sample_open(struct inode *inodep,struct file *filep)
{
	struct mydevice *_devp = container_of(inodep->i_cdev,struct mydevice,_cdev);
	filep->private_data = _devp;
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
	int i,ret;
	int mini;
	struct mydevice *_devp = filep->private_data; 

	wait_event_interruptible(_devp->_wq,CIRC_CNT(_devp->cbuf.head,_devp->cbuf.tail,SIZE)>0); // CIRC_CNT ==0 means no Data;
	
	mini = min(cnt,(size_t)CIRC_CNT(_devp->cbuf.head,_devp->cbuf.tail,SIZE));
	
	printk("Size from USERspace for REad:%d\n",(int)cnt);
	for(i=0;i<mini;i++)
	{
		ret = copy_to_user(ubuff+i,_devp->cbuf.buf+_devp->cbuf.tail,1);
		if(ret)
		{
			printk("Errot copying to user\n");
			return -EFAULT;
		}
	 	printk("copied %c to user\n",_devp->cbuf.buf[_devp->cbuf.tail]);
		_devp->cbuf.tail =(_devp->cbuf.tail+1)&(SIZE-1);
	}
	return i;
}
static ssize_t sample_write(struct file *filep, const char __user * ubuff, size_t cnt, loff_t *offset)
{
	int ret,i;
	//Assignment min of space avavible in circ buffer and cnt
        struct mydevice *_devp =filep->private_data;
	printk("Size Sent from UserSpace %d\n",(int)cnt);
	for(i=0;i<cnt;i++)
	{
		ret = copy_from_user(_devp->cbuf.buf+_devp->cbuf.head,ubuff+i,1);
		if(ret)
		{
			printk("Error copying\n");
			return -EFAULT;
		}
		printk("Copied form USER %c\t",_devp->cbuf.buf[_devp->cbuf.head]);
		_devp->cbuf.head = (_devp->cbuf.head +1)&(SIZE-1);
	}
        wake_up(&_devp->_wq);
	return i;
}

struct file_operations fops=
{
	.open    = sample_open,
	.release = sample_close,
	.read    = sample_read,
	.write   = sample_write,
}; //Designatedinitialisation of a structure;

static int __init sample_init(void)
{
	int i,j,ret;
        dev_t tmpdev;
	devnum =MKDEV(MAJORN,0); // is used for constructing a device number
	
	ret = register_chrdev_region(devnum,NMINORS,"my_dev");// request the kernel
	if(ret)
	{  //non zero means not successfull
		printk("Kernel did't grant us device number\n");
		goto reg_out;
	}
	//Control : we got device number
	for(i=0;i<NMINORS;i++)
	{
		cdev_init(&_devs[i]._cdev,&fops); // Binds your cdev withfile operations
		_devs[i].cbuf.buf = kmalloc(SIZE,GFP_KERNEL) ;//allocates memory
		if(!_devs[i].cbuf.buf)
		{
			printk("Memory is not allocated\n");
			goto cbuf_out;
		}
		init_waitqueue_head(&_devs[i]._wq);// init our waitqueue
	} // end offirst for loop

	for(j=0;j<NMINORS;j++)
	{
		tmpdev = MKDEV(MAJOR(devnum),MINOR(devnum)+j);
		ret = cdev_add(&_devs[j]._cdev,tmpdev,1); //Device is "Live" Now
		if(ret)
		{
			printk("Unable to add cdev to kernel\n");
			goto cdev_out;
		}
	}
	printk("Done Init\n");
	return 0;

	cdev_out:
	for(--j;j>=0;j--)
		cdev_del(&_devs[j]._cdev);
	
	cbuf_out:
	for(--i;i>=0;i--)
		kfree(_devs[i].cbuf.buf);
	
	reg_out:
		unregister_chrdev_region(devnum,NMINORS);
	return -1;
}

static void __exit sample_exit(void)
{
	int i;
	for(i=0;i<NMINORS;i++)
	{
		cdev_del(&_devs[i]._cdev);
		kfree(_devs[i].cbuf.buf);
	}
	unregister_chrdev_region(devnum,NMINORS);
	printk("Good bye\n");
}

module_init(sample_init);
module_exit(sample_exit);
