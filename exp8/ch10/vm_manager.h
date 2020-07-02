#define FRAME_NUM 128
#define PAGE_NUM 256
#define TLB_SIZE 32
#define PAGE_SIZE 256

void init(const char *filename);
int tlb_request(int page);
int read_file(int page);
void tlb_replace(int page,int frame);
int memorry_replace(int page);
void request(int logic_add);
void end();