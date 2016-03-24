
#define malloc(x) mymalloc(x, __FILE__, __LINE__)
#define free(x) myfree(x, __FILE__, __LINE__)

int main(int argc, char **argv) {
    
    double *b = (double *)malloc(sizeof(double)*100);
    int *c = (int *)malloc(sizeof(int));
    char *a = (char *)malloc(20);
    free(c);
    int *d = (int *)malloc(sizeof(int));
    free(b);
    free(d);
    free(a);
    
    return 0;
}

