#include<pthread.h>
#include<stdio.h>
#include <unistd.h> 
#include<string.h>
#include<sys/types.h>
#include<stdbool.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <time.h>
#define MAX_SORT 1000
#define INT_MAX 100000
void *sort_mt(int *p);
void *merge(int *p);
int *a1,*a2;


int rand_a(){
	srand((unsigned)time(NULL)); 
	int range=rand()%MAX_SORT;
	a1=malloc(sizeof(int)*range);

	for(int i=0;i<range;++i)a1[i]=rand()%INT_MAX;
	FILE* tmpf=fopen("no_sort.txt","w");
	if(tmpf==NULL){printf("open file failed");return -1;}
	//printf("%d\n",range);
	for(int i=0;i<range;++i)fprintf(tmpf,"%d\n",a1[i]);
	fclose(tmpf);
	return range;
}

int main(int argc,char* argv){

pthread_t tid[3];
pthread_attr_t attr;

if(argc!=1){fprintf(stderr,"???");return -1;}
int len=rand_a();
a2=malloc(sizeof(int)*len);
int *index1=malloc(sizeof(int)*2),*index2=malloc(sizeof(int)*2);
index1[0]=0;index1[1]=len/2-1;
index2[0]=len/2;index2[1]=len-1;

pthread_attr_init(&attr);
pthread_create(&tid[0],&attr,sort_mt,index1);
pthread_create(&tid[1],&attr,sort_mt,index2);
pthread_join(tid[0],NULL);
pthread_join(tid[1],NULL);

pthread_create(&tid[2],&attr,merge,index2);
pthread_join(tid[2],NULL);

//printf("here\n");
FILE*f=fopen("sorted.txt","w");
for(int i=0;i<len;++i)fprintf(f,"%d\n",a2[i]);

fclose(f);
free(a2);free(a1);
return 0;}
void *sort_mt(int *p){
	int low=p[0],high=p[1];
	
	for(int lh=low;lh<high-1;++lh)
		for(int rh=lh+1;rh<high;++rh)
			if(a1[rh]<a1[lh])
			{int tmp=a1[lh];a1[lh]=a1[rh];a1[rh]=tmp;}
	}	

void *merge(int *p){
	int mid=p[0]-1,high=p[1];
	int i=0,j=mid+1;
	int k=0;
	while(i<=mid&&j<=high){
		if(a1[i]<a1[j])a2[k++]=a1[i++];
		else a2[k++]=a1[j++];
	}
	while(i<=mid)a2[k++]=a1[i++];
	while(j<=high)a2[k++]=a1[j++];
}



