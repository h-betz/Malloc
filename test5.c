
#define malloc(x) mymalloc(x, __FILE__, __LINE__)
#define free(x) myfree(x, __FILE__, __LINE__)

int main(int argc, char **argv) {
    
    char *x = (char *)malloc(500);
    free(x);
    free(x);
    x = (char *)malloc(500);
    free(x);
    return 0;
}

