#include <stdlib.h> /* required for rand() */
#include "buffer.h"
#include<pthread.h>
#include <unistd.h>
#include<stdio.h>
void *producer(void *param);
void *consumer(void *param);
int main(int argc, char *argv[]){
int st,cn,pn;
st=atoi(argv[1]);
pn=atoi(argv[2]);
cn=atoi(argv[3]);

buffer_init();

pthread_t *pro,*con;
pro=malloc(sizeof(pthread_t)*pn);
con=malloc(sizeof(pthread_t)*cn);
for(int i=0;i<pn;++i){pthread_create(&pro[i],NULL,producer,NULL);}
for(int i=0;i<cn;++i){pthread_create(&con[i],NULL,consumer,NULL);}

sleep(st);
printf("end %d %d %d \n",st,pn,cn);
return 0;

}



void *producer(void *param) {
buffer_item item;
while(1){
/* sleep for a random period of time */
int st=rand()%1000000;
usleep(st);
/* generate a random number */
item = rand();
if (insert_item(item))
printf("error insert");
}
}
void *consumer(void *param) {
buffer_item item;
while (1) {
/* sleep for a random period of time */
int st=rand()%1000000;
usleep(st);
if (remove_item(&item))
printf("error remove");
}
}