#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"vm_manager.h"
#define BIN_NAME "BACKING_STORE.bin"

int main(int argc,char*argv[]){
    FILE *f;
    if(argc!=2)return 1;
    f=fopen(argv[1],"r");
    init(BIN_NAME);
    char tmp[10];
    int add;
    while(fgets(tmp,10,f)!=NULL){
        //printf("%d\n",tmp);
        add=atoi(tmp);
        request(add);
    }
    end();
}