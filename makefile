all: mymalloc.o test0 test1 test2 test3 test4 test5 test6

mymalloc.o: mymalloc.c mymalloc.h
	gcc -c mymalloc.c

test0: test0.c
	gcc -w -o test0 test0.c mymalloc.o
test1: test1.c
	gcc -w -o test1 test1.c mymalloc.o
test2: test2.c
	gcc -w -o test2 test2.c mymalloc.o
test3: test3.c
	gcc -w -o test3 test3.c mymalloc.o
test4: test4.c
	gcc -w -o test4 test4.c mymalloc.o
test5: test5.c
	gcc -w -o test5 test5.c mymalloc.o
test6: test6.c
	gcc -w -o test6 test6.c mymalloc.o
    
clean:
	rm ./test0
	rm ./test1
	rm ./test2
	rm ./test3
	rm ./test4
	rm ./test5
	rm ./test6
	rm mymalloc.o
