#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"vm_manager.h"
char memory[FRAME_NUM][PAGE_SIZE];
int page_table[PAGE_NUM];//-1 represents invalid
int TLB[TLB_SIZE][2];
int mp;
int tp;
FILE *fp;
FILE *out;
int request_num,tlb_miss,page_miss;
int tlb_lru[TLB_SIZE];
int mem_lru[FRAME_NUM];

void init(const char *filename){
    fp=fopen(filename,"rb");
    out=fopen("out.txt","w");
    for(int i=0;i<PAGE_NUM;++i)page_table[i]=-1;
    for(int i=0;i<FRAME_NUM;++i){
        mem_lru[i]=0;
        for(int j=0;j<PAGE_SIZE;++j)memory[i][j]=0;}
    for(int i=0;i<TLB_SIZE;++i){tlb_lru[i]=0;TLB[i][0]=TLB[i][1]=-1;}
    request_num=tlb_miss=page_miss=0;
    tp=mp=0;
}

int tlb_request(int page){
    for(int i=0;i<tp;++i)
        if(page==TLB[i][0]){tlb_lru[i]--;return TLB[i][1];}
        
    return -1;
}

int read_file(int page){
    if(mp==FRAME_NUM){
        int frame=memorry_replace(page);
        fseek(fp,page*PAGE_SIZE,SEEK_SET);
        fread(memory[frame],1,PAGE_SIZE,fp);
        return frame;
        }
    fseek(fp,page*PAGE_SIZE,SEEK_SET);
    fread(memory[mp],1,PAGE_SIZE,fp);
    mp++;
    return mp-1;
}

void tlb_replace(int page,int frame){
    int max=-65536;
    int min=1;
    int loc=0;
    for(int i=0;i<TLB_SIZE;++i){
        if(tlb_lru[i]>max){max=tlb_lru[i];loc=i;}
        if(tlb_lru[i]<min)min=tlb_lru[i];
    }
    TLB[loc][0]=page;
    TLB[loc][1]=frame;
    tlb_lru[loc]=min-1;
}

int memorry_replace(int page){
    int max=-65536;
    int min=1;
    int loc=0;
    for(int i=0;i<FRAME_NUM;++i){
        if(mem_lru[i]>max){max=mem_lru[i];loc=i;}
        if(mem_lru[i]<min)min=mem_lru[i];
    }
    mem_lru[loc]=min-1;
    //update page_table
    for(int i=0;i<PAGE_NUM;++i)if(page_table[i]==loc)page_table[i]=-1;
    page_table[page]=loc;
    return loc;
}



void request(int logic_add){
    int page=logic_add>>8;
    int offset=logic_add%PAGE_SIZE;
    int frame=tlb_request(page);
    //tlb_miss
    if(frame==-1){
        tlb_miss++;
        if(page_table[page]==-1){page_miss++;page_table[page]=read_file(page);}
        frame=page_table[page];
        if(tp==TLB_SIZE){tlb_replace(page,frame);}
        else {TLB[tp][0]=page;TLB[tp][1]=frame;tp++;}
    }
    mem_lru[frame]--;
    int num=(int)memory[frame][offset];
    request_num++;
    fprintf(out,"Virtual address: %d Physical address: %d Value: %d\n",logic_add,(frame<<8)+offset,num);
}

void end(){
    fclose(fp);
    fclose(out);
    printf("Page-fault rate=%f%% TLB hit rate=%f%%\n",100*(float)page_miss/request_num,100*(float)(request_num-tlb_miss)/request_num);

}


