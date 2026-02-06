/* 
Поиск последовательности бит
На вход программе подается беззнаковое 32-битное целое число N и натуральное число K (1 ≤ K ≤ 31). 
Требуется взять K подряд идущих битов числа N так, чтобы полученное число было максимальным. 
Программа должна вывести полученное число.


*/

#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    uint32_t N;
    uint32_t c;
    uint32_t max = 0;
  
    scanf("%u %u", &N, &c);
    
    int sizeInBits = sizeof(N)*8; //Размер в битах
    
    uint32_t mask = 0xFFFFFFFF>>(sizeInBits - c);
    
  
    
    for (int32_t i=c; i<=sizeInBits; i++)
    { 
        
        if ((N&mask)>max) max = (N&mask);
        N = N >> 1;
       
    }
        
  
    printf("%u", max);
   
    
    return 0;
}
