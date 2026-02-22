#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10000

int main() {
    clock_t start = clock();
    for (int i = 1; i <= N; i++) rand();
    clock_t finish = clock();
    printf("%ld\n", finish - start);
    printf("%ld\n", CLOCKS_PER_SEC);
}
