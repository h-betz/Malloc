
#define malloc(x) mymalloc(x, __FILE__, __LINE__)
#define free(x) myfree(x, __FILE__, __LINE__)

int main(int argc, char **argv) {
    
    printf("Size before p: %d\n", sbrk(0));
    char *p = (char *)malloc(10);
    printf("Size after p: %d\n", sbrk(0));
    char *q = (char *)malloc(50);
    printf("Size after q: %d\n", sbrk(0));
    free(p);
    char *r = (char *)malloc(10);
    printf("Size after r: %d\n", sbrk(0));
    free(r);   
    printf("Size delete r: %d\n", sbrk(0));
     
    free(q);
    /*char *x = (char *)malloc(20);
    printf("Size after x: %d\n", sbrk(0));
    free(x);
    printf("Size delete x: %d\n", sbrk(0));     
    char *y = (char *)malloc(15);
    printf("Size after y: %d\n", sbrk(0));          
    free(p);
    printf("Size delete p: %d\n", sbrk(0));
    free(y);*/
    //free(x);
    //printf("Size: %d\n", sbrk(0));   
    
    
    
    //printf("Test 2\n");
    
    //char *x = (char *)malloc(10);
    //free(x + 100);
    //free(x);
    
    return 0;
}

