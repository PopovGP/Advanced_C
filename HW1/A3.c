/* Извлечение бит
На вход программе подается беззнаковое 32-битное целое число N и натуральное число K (1 ≤ K ≤ 31). 
Требуется взять K младших битов числа N и вывести полученное таким образом число.
*/

#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    uint32_t N;
    uint32_t c;
  
    scanf("%u %u", &N, (int *)&c);
    
   // printf("N=%u dec and %x hex, C=%u\n", N, N, c);
   // printf("%u\n", (32-c));
   // printf("N>>c=%x\n", (N>>c));
   // printf("0xFFFFFFFF<<(32-c)=%x\n", 0xFFFFFFFF<<(32-c));
   // printf("N&0xFFFFFFFF<<(32-c)=%x\n", (N<<(32-c))&(0xFFFFFFFF<<(32-c)));
    printf("%u", (N<<(32-c))>>(32-c));
   
    
    return 0;
}
