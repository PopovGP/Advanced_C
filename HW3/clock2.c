#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10000

int main() {
    clock_t start = clock();
    for (int i = 1; i <= N; i++) rand();
   // clock_t finish = clock();
    while(1)
    {
			clock_t finish = clock();
			double ms = (double)(finish - start)/CLOCKS_PER_SEC*1000;
		    printf("finish - start %ld\n", finish - start);
		    printf("float finish - start %lf\n", ms);
			printf("%ld\n", CLOCKS_PER_SEC);
			if (ms>100) break;
	}
	return 0;

}
