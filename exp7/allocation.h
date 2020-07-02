#define SIZE 100

void split(int loc,int size,char *n);
void merge(int loc);
int request_memory(int s,char *n,const char*mode);
void release_memory(char *n);
void compact();
void stat();
void init(int m);