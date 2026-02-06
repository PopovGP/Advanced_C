/* 

Распаковать порядок
Необходимо реализовать программу, которой на входе передаётся вещественное число в типе float, 
она возвращает порядок который хранится в поле EXP в виде десятичного целого числа. 
Функция должна строго соответствовать прототипу


*/

#include <stdio.h>
#include <stdint.h>

union floatbit {
    float value;
    struct {
        uint32_t mant:23;
        uint32_t exp:8;
        uint32_t sign:1;
    } bit;
} f;
        

int extractExp(float num)
{
    f.value = num;
    return f.bit.exp;
}


int main(int argc, char *argv[])
{
   float N;
   
  
  
      scanf("%f", &N);
      
      printf("%d", extractExp(N));
 
   
    
    return 0;
}
