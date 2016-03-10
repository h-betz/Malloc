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

//Merges adjacent blocks of free memory together
void merge(struct memBlock *block, void *index) {
        
    struct memBlock *next;                              //memBlock pointer used to check next memory block
    
    index = index + block->size;                        //get index of next memory block by incrementing current index by size of current memory block
    next = (struct memBlock *)index;                    //assign next to the next memory block
    
    //Check to see if next memory block can be merged with the current one
    if (index != lastPtr && next->free == 1) {
        block->size += next->size;
        return;
    }
        
    return;
}


//Frees the memory given by the void pointer ptr, prints an error otherwise
void myfree(void *ptr, char *file, int line) {
    
    //First check to see if we allocated any memory with our malloc
    if (!started) {
        printf("Error! No memory has been allocated. In file: %s on line: %d\n", file, line);
    }
    
    //Next do a check to see if the pointer passed was actually a NULL value
    if (ptr == NULL) {
        printf("Error. No memory was ever allocated\n");
        return;
    }
    
    struct memBlock *mem;                                   //a memory block that will represent the pointer that was passed and the one we are looking for in memory
    void *index;                                            //keeps track of where we are in the heap
    struct memBlock *currentInd;                            //the memory block of our current position in memory
    struct memBlock *prevInd = NULL;                        //the previous memory block that we looked at 
    
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
            
            //if previous memory block is not null and is free, merge it with current block
            if (prevInd != NULL && prevInd->free == 1) {
                merge(prevInd, prev_index);
            }
            
            return;
            
        } 
        
        prevInd = currentInd;                   //store current memory block as the previous memory block
        prev_index = index;                     //store current index as previous index
        index = index + currentInd->size;       //increment index by current memory block size
        
    }
    
    //Otherwise, we were given a bad pointer
    printf("Error! Invalid pointer address. In file: %s on line %d\n", file, line);
    
    return;
    
}

//our memory allocator function
void * mymalloc(int bytes, char *file, int line) {
    
    //Check to see if our malloc-er has been initialized
    if (!started) {
        start();                                        //initialize everything needed to malloc
    }
    
    int old_size = bytes;                               //variable used to store user passed size value
    
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
                memLoc = index;                         //set memloc to point to this index address
                printf("Successfully malloced memory of size %d\n", old_size);
                break;
            }
        } 
        
        index = index + currentInd->size;
        
    }
    
    //Ask OS for more memory if needed
    if (!memLoc) {
        sbrk(bytes);                                    //ask the OS for bytes more memory
        memLoc = lastPtr;                               //set memloc to the last place index
        lastPtr = lastPtr + bytes;                      //increment the last place index to account for the change in added memory
        currentInd = memLoc;                            //set the current memory block to point to the memloc (index of old last place)
        currentInd->free = 0;                           //mark the memory block as not free
        currentInd->size = bytes;                       //set the size of memory block to the number of bytes
        printf("Successfully malloced memory of size %d\n", old_size);
        
    }
    
    memLoc = memLoc + sizeof(struct memBlock);          //move the pointer past the memory block
   
    return memLoc;
    
}


