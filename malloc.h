#ifndef MALLOC_H
#define MALLOC_H

#include <stdlib.h>
#include <unistd.h>

struct memBlock {
    
    int free;
    int size;
    
};

//Declaration of the function that will initialize our malloc implementation
void start();

//Declaration of our merge function that will merge adjacent memory blocks together if they are both free
void merge(struct memBlock *block, void *index);

//Declaration of our free function
void myfree(void *ptr, char *file, int line);

//Declaration of our created malloc function
void * mymalloc(int bytes, char *file, int line);

#endif
