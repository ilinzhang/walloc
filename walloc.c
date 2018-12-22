// Walloc is my implementation on malloc, just for fun
#include <stdio.h>
#include <unistd.h>
#include "walloc.h"

// GLOBAL LIST HEAD
block_info* list_head = NULL;

#define node_size sizeof(struct block);

/*
* @requires - (size_t) number of bytes to allocate
* @modifies - changes size of process heap
* @effects - returns a pointer to location of newly allocated memory or NULL if there was an issue
*/
// TODO: Make this thread-safe
void *walloc(size_t size) {
    block_info* this_block = NULL;
    block_info* last = list_head;

    if (size <= 0) {
        return NULL;
    }

    if (!list_head) {
        this_block = allocate_space(size);    
        if (!this_block) {
            return NULL;
        }
        list_head = this_block;
    } else {
        this_block = find_free_block(&last, size);
        // No free block was found, allocate more space
        if (!this_block) {
            this_block = allocate_space(size);
            if (!this_block) {
                return NULL;
            }
        }
    }

    this_block->free = 0;
    return (this_block+1);
}

/*
* Find free block - if available
* If no free block is available, returns NULL
*/
void *find_free_block(struct block_info** last, size_t size){
    
    block_info* current = list_head;
    
    while (current != NULL && !(current->free && current->size >= size)) {
        *last = current;
        current = current->next;
    }

    return current;
}

/*
* Called to allocate more heap space for the process
*/
void *allocate_space(size_t size){

    // Get the current head of the heap
    void* proc_head = sbrk(0);
    void* res = sbrk(size + sizeof(struct block_info));
    // Error handling here
    if (res == (void*) -1) {
        return NULL;
    }


    return NULL;
}

/*
* Reallocates a given pointer to a new size (if it's possible)
*/
void *realloc(void* ptr, size_t size){

    return NULL;
}

/*
* Allocates a space in memory that is initialized to 0
*/
void *calloc(size_t num_elems, size_t size){

    return NULL;
}

/*
* Frees the block at the specified location
*/
void free(void* ptr) {
    if (!ptr) {
        return;
    }

    struct block_info* blk = get_blk_info_address(ptr);
    // NO DOUBLE FREES ALLOWED, DUDES 
    if(blk->free == 0) {
        return;
    }
    
    blk->free = 1;
}

struct block_info* get_blk_info_address(void* ptr) {
    return (struct block_info *)ptr - 1;
}