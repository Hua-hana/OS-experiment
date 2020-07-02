
#include<stdio.h>
#include <unistd.h> 
#include"banker.h"


int available[NUMBER_OF_RESOURCES];
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

int work[NUMBER_OF_RESOURCES];
int finish[NUMBER_OF_CUSTOMERS];

void banker_init(int *ava,int maxi[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES]){
    for(int i=0;i<NUMBER_OF_RESOURCES;++i)available[i]=ava[i];
    for(int i=0;i<NUMBER_OF_CUSTOMERS;++i)
        for(int j=0;j<NUMBER_OF_RESOURCES;++j){
            maximum[i][j]=maxi[i][j];
            allocation[i][j]=0;
            need[i][j]=maximum[i][j];
        }

}

void display(){

    printf("available :\n");
    for(int i=0;i<NUMBER_OF_RESOURCES;++i)printf("%d ",available[i]);
    printf("\nmaximum :\n");
    for(int i=0;i<NUMBER_OF_CUSTOMERS;++i){
        if(i!=0)printf("\n");
        for(int j=0;j<NUMBER_OF_RESOURCES;++j){printf("%d ",maximum[i][j]);}}
    printf("\nallocation :\n");
    for(int i=0;i<NUMBER_OF_CUSTOMERS;++i){
        if(i!=0)printf("\n");
        for(int j=0;j<NUMBER_OF_RESOURCES;++j){printf("%d ",allocation[i][j]);}}
    printf("\nneed :\n");
    for(int i=0;i<NUMBER_OF_CUSTOMERS;++i){
        if(i!=0)printf("\n");
        for(int j=0;j<NUMBER_OF_RESOURCES;++j){printf("%d ",need[i][j]);}}
    printf("\n");
}

int greater_v(int *a,int *b){
    for(int i=0;i<NUMBER_OF_RESOURCES;++i)if(a[i]<b[i])return 0;
    return 1;
}
void add_v(int *a,int *b){for(int i=0;i<NUMBER_OF_RESOURCES;++i)a[i]=a[i]+b[i];}
void sub_v(int *a,int *b){for(int i=0;i<NUMBER_OF_RESOURCES;++i)a[i]=a[i]-b[i];}

int judge_safe(int ne[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES],int al[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES]){
    for(int i=0;i<NUMBER_OF_CUSTOMERS;++i){
        if(finish[i]==0){
            if(greater_v(work,ne[i])==1){
            add_v(work,al[i]);
            finish[i]=1;
            if(judge_safe(ne,al)==1)return 1;
            else {
                finish[i]=0;
                sub_v(work,al[i]);
            }
            }
        }
    }
    for(int i=0;i<NUMBER_OF_RESOURCES;++i)if(finish[i]==0)return 0;
    return 1;
}


int request_resources(int customer_num, int request[]){
    int tmpneed[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
    int a[NUMBER_OF_RESOURCES];
    int al[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
    //printf("here1\n");
    for(int i=0;i<NUMBER_OF_CUSTOMERS;++i){
        for(int j=0;j<NUMBER_OF_RESOURCES;++j){
            tmpneed[i][j]=need[i][j];
            al[i][j]=allocation[i][j];
        }}
    for(int i=0;i<NUMBER_OF_RESOURCES;++i){
        a[i]=available[i]-request[i];
        if(a[i]<0||request[i]>need[customer_num][i])return -1;
        tmpneed[customer_num][i]-=request[i];
        al[customer_num][i]+=request[i];
        }

    //safe judge
    for(int i=0;i<NUMBER_OF_RESOURCES;++i)work[i]=a[i];
    for(int i=0;i<NUMBER_OF_CUSTOMERS;++i)finish[i]=0;
    int r=judge_safe(tmpneed,al);

    if(r==0)return -1;

    for(int i=0;i<NUMBER_OF_RESOURCES;++i){
        need[customer_num][i]=tmpneed[customer_num][i];
        available[i]=a[i];
        allocation[customer_num][i]=al[customer_num][i];}
    return 0;

}

void release_resources(int customer_num, int release[]){
    for(int i=0;i<NUMBER_OF_RESOURCES;++i){
        available[i]+=release[i];
        need[customer_num][i]+=release[i];
        allocation[customer_num][i]-=release[i];}
}