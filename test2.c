
#define malloc(x) mymalloc(x, __FILE__, __LINE__)
#define free(x) myfree(x, __FILE__, __LINE__)

int main(int argc, char **argv) {
    
    
    char *x =(char*) malloc(0);
    free(x);
    int a = 19;
    int *y = (int *) malloc(20);
    int b = 20;
    double c = 46.4;
    double *z = (double *) malloc(sizeof(double)*3);
    int d = 200;
    free(z); 
    free(y);    
    
    return 0;
}

