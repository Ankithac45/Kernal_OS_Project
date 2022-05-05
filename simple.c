/*
commands
make: the compiled kernel module simple.ko is created
sudo insmod simple.ko:	to load kernel module
lsmod: list of kernel modules
demsg: to check the contents of kernel log buffer
sudo rmmod simple: to remove the loaded kernel module
sudo demsg -c: to clear the buffer
*/

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

/* This function is called when the module is loaded. */

struct task_struct *task;
struct task_struct *task_next;		// to iterate through task->children
struct list_head *list;			// to iterate through the list in each task->children struct

int simple_init(void)	
{
	printk(KERN_INFO "Loading Module\n");
	
	for_each_process(task)
	{
		printk(KERN_INFO "pid: %d, process: %s, state: %ld\n", task->pid, task->comm, task->state);
		list_for_each(list, &task->children)
		{
			task_next = list_entry(list, struct task_struct, sibling);
			printk(KERN_INFO "CHILD OF %s[%d] ,pid: %d, process: %s, state: %ld\n",task->comm, task->pid, task_next->pid, task_next->comm, task_next->state);
		}
	
	printk("------------------------------------------\n");
	}
  	
	return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void)
{
	printk(KERN_INFO "Removing Module\n");
}


/* Macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");