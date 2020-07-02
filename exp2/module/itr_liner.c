/**
 * Kernel module that communicates with /proc file system.
 *
 * This provides the base logic for Project 2 - displaying task information
 */

#include <linux/init.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include<linux/sched/signal.h>//change
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/vmalloc.h>
#include <linux/uaccess.h>//change

#define BUFFER_SIZE 128
#define PROC_NAME "pid"

/* the current pid */
static long l_pid;
struct task_struct *task;

/* This function is called when the module is loaded. */
static int proc_init(void)
{
        printk(KERN_INFO "/proc/%s created\n", PROC_NAME);
	for_each_process(task){
	printk(KERN_INFO "command=%s pid=%d state=%ld\n", task->comm,task->pid,task->state);
	
	}
	return 0;
}

/* This function is called when the module is removed. */
static void proc_exit(void) 
{

        printk( KERN_INFO "/proc/%s removed\n", PROC_NAME);
}



/* Macros for registering module entry and exit points. */
module_init( proc_init );
module_exit( proc_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Module");
MODULE_AUTHOR("SGG");

