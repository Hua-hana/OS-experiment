#include"allocation.h"
#include<stdlib.h>
#include<stdio.h>
#include <string.h>
#define BUF 20
int main(int argc,char* argv[]){
    int mem;
    if(argc!=2)return 1;
    mem=atoi(argv[1]);
    //printf("%d\n",mem);
    init(mem);
    char com[BUF];
    char *s;
    char*tmp;
    char *name;
    char*n;
    char*mode;
    while(1){
        printf("allocator>");
        fgets(com,BUF,stdin);
        
        tmp=strdup(com);
        //printf("%s\n",tmp);

        if(strcmp(tmp,"C\n")==0){
            compact();
        }
        else if(strcmp(tmp,"STAT\n")==0){
            
            stat();
        }
        else{
        s=strsep(&tmp," ");
        
        if(strcmp(s,"RQ")==0){
            name=strsep(&tmp," ");
            n=malloc(strlen(name)+1);
            strcpy(n,name);
            n[strlen(name)]='\0';
            mem=atoi(strsep(&tmp," "));
            mode=strsep(&tmp," ");
            //printf("%s %d %s\n",n,mem,mode);
            request_memory(mem,n,mode);
        }
        else if(strcmp(s,"RL")==0){
            name=strsep(&tmp," ");
            name[strlen(name)-1]='\0';
            //printf("%s\n",name);
            
            release_memory(name);
        }
       
        else {break;}
        free(tmp);
        }
    }

    return 0;
}