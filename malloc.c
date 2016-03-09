#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "malloc.h"

void * memPtr;                                          //will keep track of where our memory starts
void * lastPtr;                                         //will keep track of where our memory ends
int started = 0;                                        //keeps track of whether or not our heap has been created

//starts the malloc process
void start() {
    
    lastPtr = sbrk(0);                                  //gives us the last address for memory for our program
    memPtr = lastPtr;                                   //set our starting point to our end point since we haven't allocated memory yet
    started = 1;
    
}

void merge(struct memBlock *block, void *index) {
        
    struct memBlock *next;                              //memBlock pointer used to check next memory block
    struct memBlock *prev;                                    
    
    index = index + block->size;                        //get index of next memory block by incrementing current index by size of current memory block
    next = (struct memBlock *)index;                      //assign next to the next memory block
    
    //Check to see if next memory block can be merged with the current one
    if (index != lastPtr && next->free == 1) {
        block->size += next->size;
        printf("Merged data size: %d\n", block->size);
        return;
    }
    //Check to see if previous memory block can be merged with the current one
    /*if (prev_index == memPtr && prev->free == 1) {
        block->size += prev->size;
        printf("Merged memory size: %d\n", block->size);
        return;
    }*/
    
    
    
    return;
}



void myfree(void *ptr, char *file, int line) {
    
    //First do a check to see if the pointer passed was actually a NULL value
    if (ptr == NULL) {
        printf("Error. No memory was ever allocated\n");
        return;
    }
    
    struct memBlock *mem;
    void *index;
    struct memBlock *currentInd;
    struct memBlock *prevInd = NULL;
    
    void *prev_index;
    
    mem = ptr - sizeof(struct memBlock);                    //holds the pointer that we passed as memBlock
    index = memPtr;
    
    while (index != lastPtr) {                              //loop through our memory until we reach the end
            
        currentInd = (struct memBlock *)index;
        
        //Check if current memory block is the same as the one we passed
        if (currentInd == mem) {                       
        
            //Check to see if current memory block has already been freed, if so print error and return
            if (currentInd->free != 0) {
                printf("Error! Invalid free, memory is already freed. In file: %s on line: %d\n", file, line);
                return;
            }
            
            //Otherwise, mark the memory block as free and merge with neighboring blocks if possible
            printf("Freeing memory of size %d\n", mem->size);
            mem->free = 1;
            ptr = NULL;
            merge(currentInd, index);
            if (prevInd != NULL) {
                merge(prevInd, prev_index);
            }
            
            return;
            
        } 
        
        prevInd = currentInd;
        prev_index = index;
        index = index + currentInd->size;
        
    }
    
    printf("Error! Invalid pointer address. In file: %s on line %d\n", file, line);
    
    return;
    
}

//our memory allocator function
void * mymalloc(int bytes, char *file, int line) {
    
    if (!started) {
        start();
    }
    
    void * index;                                       //where we are currently at in memory     
    struct memBlock *currentInd;                        //similar to index, but casted as a memBlock
    void *memLoc;                                       //the memory location which we will return
    
    bytes = bytes + sizeof(struct memBlock);            //the total memory we need has to include the size of our memBlock struct
    memLoc = 0;                                         //memLoc will go to 0 until we find a location in our memory
    index = memPtr;                                     //we set our current index to the start of our memory heap
    
    while (index != lastPtr) {                          //loop through our memory until we reach the end
        
        currentInd = (struct memBlock *)index;
        if (currentInd->free) {                         //found a point that's open for memory
            if (currentInd->size >= bytes) {            //the space has enough room for our bytes
                currentInd->free = 0;                   //set memory block as unavailable 
                memLoc = index;
                printf("Allocated memory\n");
                break;
            }
        } 
        
        index = index + currentInd->size;
        
    }
    
    //Ask OS for more memory if needed
    if (!memLoc) {
        printf("Need more memory\n");
        sbrk(bytes);
        memLoc = lastPtr;
        lastPtr = lastPtr + bytes;
        currentInd = memLoc;
        currentInd->free = 0;
        currentInd->size = bytes;
        
    }
    
    memLoc = memLoc + sizeof(struct memBlock);
   
    return memLoc;
    
}


