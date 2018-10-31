#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h> // task_struct definition
#include <asm/unistd.h>
#include <linux/list.h>
#include <linux/init_task.h>

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

//MODULE_AUTHOR("Josh Lisco, Sydney Lee, John Woodman");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("A kernel module to list process by their names");