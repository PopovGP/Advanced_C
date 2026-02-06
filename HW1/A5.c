/* 
Подсчет битов
На вход программе подается беззнаковое 32-битное целое число N. 
Требуется найти количество единичных битов в двоичном представлении данного числа.



*/

#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    uint32_t N;
    uint32_t c=0;
  
    scanf("%u", &N);
    
    uint32_t num = 1;
    
    for (int i=0;i<32;i++)
    {
       
        if (  (num<<i) & N) 
            c++;
        
    
    }
    

    printf("%u", c);
   
    
    return 0;
}
