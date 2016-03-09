#ifndef MALLOC_H
#define MALLOC_H

#include <stdlib.h>
#include <unistd.h>

struct memBlock {
    
    int free;
    int size;
    
};

void start();

//Declaration of our free function
void myfree(void *ptr, char *file, int line);

//Declaration of our created malloc function
void * mymalloc(int bytes, char *file, int line);

#endif
