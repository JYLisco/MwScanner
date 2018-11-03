#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h> // task_struct definition
#include <asm/unistd.h>
#include <linux/list.h>
#include <linux/init_task.h>

#include "header.h"

#ifndef __KERNEL__
#define __KERNEL__
#endif


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

static struct file_operations fops = {
	.open = mw_scanner_open,
	.release = mw_scanner_release,
	.unlocked_ioctl = mw_scanner_ioctl
};


// initialization of module
int __init init_module(void)
{
  printk("Module init.\n");
  // function call
  return 0;
}

// exit of module
void __exit exit_module(void)
{
  printk("Module exit.\n");
  return;
}

module_init(init_module);
module_exit(exit_module);

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


//MODULE_AUTHOR("Josh Lisco, Sydney Lee, John Woodman");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("A kernel module to list process by their names");