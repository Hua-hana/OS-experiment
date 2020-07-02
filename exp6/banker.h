#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 4

void banker_init(int *ava,int maxi[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES]);
void display();
int greater_v(int *a,int *b);
void add_v(int *a,int *b);
void sub_v(int *a,int *b);
int judge_safe(int ne[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES],int al[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES]);
int request_resources(int customer_num, int request[]);
void release_resources(int customer_num, int release[]);