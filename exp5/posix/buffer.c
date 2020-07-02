#include "buffer.h"
#include <semaphore.h>
#include<pthread.h>
#include<stdio.h>
/* the buffer */
//actual size=BUFFER_SIZE
buffer_item buffer[BUFFER_SIZE];
int head=0,tail=0;
sem_t full,empty;
pthread_mutex_t mutex;
int insert_item(buffer_item item) {
/* insert item into buffer
return 0 if successful, otherwise
return -1 indicating an error condition */

sem_wait(&empty);
pthread_mutex_lock(&mutex);
buffer[head]=item;
head=(head+1)%BUFFER_SIZE;
sem_post(&full);
printf("insert %d. Now the buffer is:",item);
for(int i=tail;i!=head;i=(i+1)%BUFFER_SIZE)printf("%d ",buffer[i]);
printf("\n");
pthread_mutex_unlock(&mutex);

return 0;

}
int remove_item(buffer_item *item) {
/* remove an object from buffer
placing it in item
return 0 if successful, otherwise
return -1 indicating an error condition */
sem_wait(&full);
pthread_mutex_lock(&mutex);
*item=buffer[tail];
tail=(tail+1)%BUFFER_SIZE;
sem_post(&empty);
printf("remove %d. Now the buffer is:",*item);
for(int i=tail;i!=head;i=(i+1)%BUFFER_SIZE)printf("%d ",buffer[i]);
printf("\n");
pthread_mutex_unlock(&mutex);

return 0;

}

void buffer_init(){
    sem_init(&full,0,0);
    sem_init(&empty,0,BUFFER_SIZE-1);
    pthread_mutex_init(&mutex,NULL);
}