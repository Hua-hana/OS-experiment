#include<pthread.h>
#include<stdio.h>
#include <unistd.h> 
#include<string.h>
#include<sys/types.h>
#include<stdbool.h>
#include<sys/stat.h>
#include<fcntl.h>
int fd;
int array[9][9];
int result[11];
struct para{
int col,row;
};
void *runner(struct para*a);

int main(int argc,char * argv[]){
pthread_t tid[11];
pthread_attr_t attr;

if(argc!=2){fprintf(stderr,"enter a filename!");return -1;}
fd=open(argv[1],O_RDONLY);
if(fd==-1){fprintf(stderr,"Open File Failed");return -1;}

for(int i=0;i<11;++i)result[i]=0;
dup2(fd,STDIN_FILENO);
char tmp;
for(int i=0;i<9;++i)
	for(int j=0;j<9;++j){//read(fd,&array[i][j],1);read(fd,&tmp,1);}
		scanf("%d",&array[i][j]);}
/*
for(int i=0;i<9;++i){
	printf("\n");
	for(int j=0;j<9;++j)printf("%d ",array[i][j]);}
*/
struct para* parameter[11];
pthread_attr_init(&attr);
for(int i=0;i<9;++i){
parameter[i]=(struct para*)malloc(sizeof(struct para));
parameter[i]->col=i%3;
parameter[i]->row=i/3;
pthread_create(&tid[i],&attr,runner,parameter[i]);
}
parameter[9]=(struct para*)malloc(sizeof(struct para));
parameter[10]=(struct para*)malloc(sizeof(struct para));
parameter[10]->col=-1;
parameter[10]->row=0;
pthread_create(&tid[9],&attr,runner,parameter[10]);
parameter[9]->col=0;
parameter[9]->row=-1;
pthread_create(&tid[10],&attr,runner,parameter[9]);

for(int i=0;i<11;++i)pthread_join(tid[i],NULL);

for(int i=0;i<11;++i)if(result[i]==0){printf("Not a sudoku\n");return 0;}
printf("Is a sudoku\n");
return 0;

}

void *runner(struct para*a){
	//printf("create  %d %d\n",a->row,a->col);
	int re=0;
	int b[10]={0};
	if(a->col==-1){
		for(int i=0;i<9;++i){
			for(int j=0;j<9;++j)b[array[j][i]]=1;
			for(int j=1;j<=9;++j)			  {if(b[j]==0)pthread_exit(0);b[j]=0;}
			}
		result[10]=1;
		pthread_exit(0);}
	
	else if(a->row==-1){
		for(int i=0;i<9;++i){
			for(int j=0;j<9;++j)b[array[i][j]]=1;
			for(int j=1;j<=9;++j){if(b[j]==0)pthread_exit(0);b[j]=0;}
			}	
		result[9]=1;
		pthread_exit(0);}
	else {	int row=a->row*3;int col=a->col*3;
		for(int i=0;i<3;++i)
			for(int j=0;j<3;++j)b[array[i+row][j+col]]=1;	
		for(int j=1;j<=9;++j)if(b[j]==0)pthread_exit(0);
		//printf("%d\n",a->row*3+a->col);
		result[a->row*3+a->col]=1;
		pthread_exit(0);}

}

