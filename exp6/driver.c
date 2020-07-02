#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"banker.h"
#define SIZE 10
int main(int argc, char *argv[])
{
    FILE *in;
    char *temp;
    char cus[SIZE];

    int resource[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
    int a[NUMBER_OF_RESOURCES];

    if(argc!=NUMBER_OF_RESOURCES+1)return -1;
    for(int i=1;i<=NUMBER_OF_RESOURCES;++i)a[i-1]=atoi(argv[i]);
    in = fopen("in1.txt","r");
    int j=0;
    while (fgets(cus,SIZE,in) != NULL) {

        temp = strdup(cus);
        for(int i=0;i<NUMBER_OF_RESOURCES;++i)resource[j][i]=atoi(strsep(&temp,","));
        //printf("get\n");
        // add the task to the scheduler's list of tasks
        
        j++;
        free(temp);
    }
    fclose(in);
    //for(int i=0;i<NUMBER_OF_CUSTOMERS;++i)for(int j=0;j<NUMBER_OF_RESOURCES;++j)printf("%d ",resource[i][j]);
    banker_init(a,resource);

   // printf("\n");
    char com[2*SIZE];
    char *comname;
    int cus_num;
    while(1){
        printf(">> ");
        fgets(com,2*SIZE,stdin);
        temp=strdup(com);
        comname=strsep(&temp," ");
        //printf("com=%s comname=%s\n",com,comname);
        if(comname[0]=='e'||comname[0]=='E')break;
        else if(comname[0]=='*')display();
        else {
            cus_num=atoi(strsep(&temp," "));
            for(int i=0;i<NUMBER_OF_RESOURCES;++i)a[i]=atoi(strsep(&temp," "));
            if(comname[1]=='Q'){if(request_resources(cus_num,a)==-1)printf("request failed\n");else printf("request successed\n");}
            else if(comname[1]=='L')release_resources(cus_num,a);
        }
    free(temp);
    }
}

    