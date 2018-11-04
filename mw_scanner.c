#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
#include "header.h"

#ifndef __KERNEL__
#define __KERNEL__
#endif

// scan processes for name specified by user
void scan_proc(const char* keyword)
{

}

// scan memory for name specified by user
void scan_mem(const char* keyword)
{

}

// scan sys call and interrupt descriptor tables
void scan_tables()
{

}

static int mw_scanner_open(struct inode *inode, struct file *file)
{
	printk("Device opened.\n");
	return 0;
}

static int mw_scanner_release(struct inode *inode, struct file *file)
{
	printk("Device released.\n");
	return 0;
}

static long mw_scanner_ioctl(struct file *filp, unsigned int cmd, unsigned long args)
{
	switch(cmd)
	{
	case READ_PROC:
		scan_proc((char*)args);
		printk(KERN_INFO "Scanning processes for keyword \"%s\"\n", (char*)args);
		break;
	case READ_MEM:
		scan_mem((char*)args);
		printk(KERN_INFO "Scanning memory for keyword \"%s\"\n", (char*)args);
		break;
	case READ_TBL:
		scan_tables((char*)args);
		printk(KERN_INFO "Scanning system call table and interrupt descriptor table for keyword \"%s\"\n", (char*)args);
		break;
	}
	return 0;
}

static struct class *my_class;

static struct file_operations fops = {
	.open = mw_scanner_open,
	.release = mw_scanner_release,
	.unlocked_ioctl = mw_scanner_ioctl
};


// initialization of module
int __init init_module(void)
{
	printk("Module init.\n");

	major_num = register_chrdev(0, DEVICE_NAME, &fops);
	printk("major_num: %d", major_num);

	my_class = class_create(THIS_MODULE, DEVICE_NAME);
	device_create(my_class, NULL, MKDEV(major_num, 0), NULL, DEVICE_NAME);
	printk("Device initialized in kernel.\n");

  	return 0;
}

// exit of module
void __exit exit_module(void)
{
  	printk("Module exit.\n");

	device_destroy(my_class, MKDEV(major_num, 0));
	class_unregister(my_class);
	class_destroy(my_class);
	unregister_chrdev(major_num, DEVICE_NAME);
	printk("Device has been released.\n\n");
	
	return;
}

module_init(init_module);
module_exit(exit_module);

//MODULE_AUTHOR("Josh Lisco, Sydney Lee, John Woodman");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("A kernel module to list process by their names");