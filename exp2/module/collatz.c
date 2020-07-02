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
#include<linux/moduleparam.h>

#define BUFFER_SIZE 128
#define PROC_NAME "pid"

static int start = 25;
module_param(start, int, 0);

struct collatz{
int num;
struct list_head list;
};
static LIST_HEAD(num_head);


/* This function is called when the module is loaded. */
static int proc_init(void)
{
        printk(KERN_INFO "/proc/%s created\n", PROC_NAME);
	struct collatz *ptr;
	int n=start;
	ptr=kmalloc(sizeof(*ptr),GFP_KERNEL);
	ptr->num=n;
	INIT_LIST_HEAD(&ptr->list);
	list_add_tail(&ptr->list,&num_head);
	while(n!=1){
	if(n%2==0)n/=2;
	else n=3*n+1;
	ptr=kmalloc(sizeof(*ptr),GFP_KERNEL);
	ptr->num=n;
	INIT_LIST_HEAD(&ptr->list);
	list_add_tail(&ptr->list,&num_head);
	}
	ptr=kmalloc(sizeof(*ptr),GFP_KERNEL);
	ptr->num=n;
	INIT_LIST_HEAD(&ptr->list);
	list_add_tail(&ptr->list,&num_head);

	list_for_each_entry(ptr,&num_head,list){
	printk(KERN_INFO "%d ", ptr->num);}
	return 0;
}

/* This function is called when the module is removed. */
static void proc_exit(void) 
{
	struct collatz *ptr,*next;
	list_for_each_entry_safe(ptr,next,&num_head,list){
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

