
#define malloc(x) mymalloc(x, __FILE__, __LINE__)
#define free(x) myfree(x, __FILE__, __LINE__)

int main(int argc, char **argv) {
    
    
    char *a = malloc(10);
    *a = "name";
    int *b = malloc(sizeof(int)*10);
    *b = 20;
    double *c = malloc(sizeof(double)*2);
    *c = 45.23;
    free(c);
    free(b);
    free(a);
    
    return 0;
}

