
#define malloc(x) mymalloc(x, __FILE__, __LINE__)
#define free(x) myfree(x, __FILE__, __LINE__)

int main(int argc, char **argv) {
    
    
    char *x = (char *)malloc(sizeof(int));
    free(x);
    char *y = (char *)malloc(sizeof(int)*4);
    free(y + 10);
    free(y);
    
    
    return 0;
}

