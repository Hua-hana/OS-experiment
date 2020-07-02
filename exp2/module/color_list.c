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
struct color{
int red,blue,green;
struct list_head list;
};
static LIST_HEAD(color_list);
/* This function is called when the module is loaded. */
static int proc_init(void)
{
        printk(KERN_INFO "/proc/%s created\n", PROC_NAME);
	struct color *violet;
	int i=4;
	while(i>0){
	violet = kmalloc(sizeof(*violet), GFP_KERNEL);
	violet->red = i;
	violet->blue = i;
	violet->green = i;
	INIT_LIST_HEAD(&violet->list);	
	list_add_tail(&violet->list, &color_list);
	i--;
}
	list_for_each_entry(violet,&color_list,list){
	printk(KERN_INFO "red=%d blue=%d green=%d\n", violet->red,violet->blue,violet->green);
	}
	return 0;
}

/* This function is called when the module is removed. */
static void proc_exit(void) 
{	struct color *ptr,*next;
	list_for_each_entry_safe(ptr,next,&color_list,list){
	list_del(&ptr->list);
	kfree(ptr);
	}
        printk( KERN_INFO "/proc/%s removed\n", PROC_NAME);
}



/* Macros for registering module entry and exit points. */
module_init( proc_init );
module_exit( proc_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Module");
MODULE_AUTHOR("SGG");

