#include <stdio.h>

// LinkedList Node Struct
struct block_info {
    size_t size;
    int free;
    struct block_info *next;
};

typedef struct block_info block_info;

void* walloc(size_t);
void* find_free_block(struct block_info**, size_t);
void* allocate_space(size_t);
void* realloc(void*, size_t);
void* calloc(size_t, size_t);
void free(void*);
struct block_info* get_blk_info_address(void*);
