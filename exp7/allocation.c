#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"allocation.h"

int memory[SIZE][2];
int block_num;
char *name[SIZE];


void init(int m){
    for(int i=0;i<SIZE;++i)
    name[i]=NULL;
    memory[0][0]=0;
    memory[0][1]=m-1;
    block_num=1;
}



void split(int loc,int size,char *n){
    if(memory[loc][1]-memory[loc][0]+1==size){name[loc]=n;return ;}
    for(int i=block_num-1;i>=loc;--i){
        memory[i+1][0]=memory[i][0];
        memory[i+1][1]=memory[i][1];
        name[i+1]=name[i];
    }
    memory[loc][1]=memory[loc][0]+size-1;
    memory[loc+1][0]=memory[loc][1]+1;
    name[loc]=n;
    block_num++;
}

void merge(int loc){
    if(loc>0&&loc+1<block_num&&name[loc-1]==NULL&&name[loc+1]==NULL){
        memory[loc-1][1]=memory[loc+1][1];
        for(int i=loc;i<block_num-2;++i){
            memory[i][0]=memory[i+2][0];
            memory[i][1]=memory[i+2][1];
            name[i]=name[i+2];
        }
        name[block_num-2]=NULL;
        name[block_num-1]=NULL;
        block_num-=2;
    }
    else if((loc==0||name[loc-1]!=NULL)&&loc+1<block_num&&name[loc+1]==NULL){
        memory[loc][1]=memory[loc+1][1];
        for(int i=loc+1;i<block_num-1;++i){
            memory[i][0]=memory[i+1][0];
            memory[i][1]=memory[i+1][1];
            name[i]=name[i+1];
        }
        name[block_num-1]=NULL;
        block_num--;
    }
    else if((loc+1==block_num||name[loc+1]!=NULL)&&loc>0&&name[loc-1]==NULL){
        memory[loc-1][1]=memory[loc][1];
        for(int i=loc;i<block_num-1;++i){
            memory[i][0]=memory[i+1][0];
            memory[i][1]=memory[i+1][1];
            name[i]=name[i+1];
        }
        name[block_num-1]=NULL;
        block_num--;
    }
}



int request_memory(int s,char *n,const char*mode){
    int i=0;
    if(mode[0]=='F'){
        while(name[i]!=NULL||memory[i][1]-memory[i][0]+1<s)++i;
        if(i==block_num)return -1;
        split(i,s,n);
    }
    else if(mode[0]=='B'){
        int min=memory[block_num-1][1]-memory[0][0]+1+1;
        int loc=-1;
        for(;i<block_num;++i){
            if(name[i]==NULL&&memory[i][1]-memory[i][0]+1>=s){
                if(memory[i][1]-memory[i][0]+1<min){loc=i;min=memory[i][1]-memory[i][0]+1;}
            }
        }
        if(loc==-1)return -1;
        split(loc,s,n);
    }
    else if(mode[0]=='W'){
        int max=0;
        int loc=-1;
        for(;i<block_num;++i){
            if(name[i]==NULL&&memory[i][1]-memory[i][0]+1>=s){
                if(memory[i][1]-memory[i][0]+1>max){loc=i;max=memory[i][1]-memory[i][0]+1;}
            }
        }
        if(loc==-1)return -1;
        split(loc,s,n);
    }
    return 0;
}

void release_memory(char *n){
    
    int loc=0;
    for(int i=0;i<block_num;++i){
        //printf("release %s %d\n",n,i);
        if(name[i]!=NULL&&strcmp(name[i],n)==0)
        {loc=i;break;}}
    free(name[loc]);
    name[loc]=NULL;
    
    merge(loc);
    
}

void compact(){
    int offset=0;
    int p_num=0;
    int size=memory[block_num-1][1];
    for(int i=0;i<block_num;++i){
        if(name[i]==NULL){offset+=memory[i][1]-memory[i][0]+1;continue;}
        p_num++;
        memory[i][0]-=offset;
        memory[i][1]-=offset;   
    }
    offset=0;
    
    for(int i=0;i<block_num;++i){
        if(name[i]==NULL){offset++;continue;}  
        if(offset==0)continue;
        memory[i-offset][0]=memory[i][0];
        memory[i-offset][1]=memory[i][1];
        name[i-offset]=name[i];
        name[i]=NULL;
    }

    memory[p_num][0]=memory[p_num-1][1]+1;
    memory[p_num][1]=size;
    name[p_num]=NULL;
    block_num=p_num+1;
}

void stat(){
    for(int i=0;i<block_num;++i){
        if(name[i]==NULL)printf("Addresses [%d:%d] Unused\n",memory[i][0],memory[i][1]);
        else printf("Addresses [%d:%d] Process %s\n",memory[i][0],memory[i][1],name[i]);
    }
}

