/**
 * Example client program that uses thread pool.
 */

#include <stdio.h>
#include <unistd.h>
#include "threadpool.h"

#define worknum 10
struct data
{
    int a;
    int b;
};

void add(void *param)
{
    struct data *temp;
    temp = (struct data*)param;

    printf("I add two values %d and %d result = %d\n",temp->a, temp->b, temp->a + temp->b);
}


int main(void)
{
    // create some work to do
    struct data work[worknum];
    for(int i=0;i<worknum;++i){
    work[i].a = i;
    work[i].b = 10-i;}

    // initialize the thread pool
    pool_init();

    sleep(1);
    // submit the work to the queue
    for(int i=0;i<worknum;++i)
    if(pool_submit(&add,&work[i])==1){printf("Queue is full!\n");return 0;}

    // may be helpful 
    sleep(5);

    pool_shutdown();

    return 0;
}
