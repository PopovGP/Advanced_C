/* 

Упаковать массив
В программе реализована структура данных:
struct pack_array {
uint32_t array; // поле для хранения упакованного массива из 0 и 1
uint32_t count0 : 8; // счетчик нулей в array
uint32_t count1 : 8; // счетчик единиц в array
}
Необходимо реализовать программу, которая упаковывает переданный ей массив из 32-ух элементов 0 и 1 в указанную структуру данных.
Функция должна строго соответствовать прототипу:

void array2struct(int [], struct pack_array *)


*/

#include <stdio.h>
#include <stdint.h>

struct pack_array {
uint32_t array; // поле для хранения упакованного массива из 0 и 1
uint32_t count0 : 8; // счетчик нулей в array
uint32_t count1 : 8; // счетчик единиц в array
};

#define MAX_ELEMENTS 32

void array2struct(int my_array[], struct pack_array * pa)
{
    uint32_t count0 = 0;
    uint32_t count1 = 0;

    
    for (int i=0; i<MAX_ELEMENTS; i++)
    {
        pa->array = pa->array | my_array[i] << (MAX_ELEMENTS-1-i);
     //   printf("i=%u my_array[i]=%u\n", i, my_array[i]);
        if (my_array[i]) count1++; else count0++;
        
    }
    pa->count0 = count0;
    pa->count1 = count1;
    
    
    
}

int main(int argc, char *argv[])
{
   int N;
   int arr[MAX_ELEMENTS];
   struct pack_array mypa;
   mypa.array = 0;

  
    
    for (int i=0;i<MAX_ELEMENTS;i++)
    {
        scanf("%u", &N);
        arr[i]=N;

    }

   
   array2struct(arr, &mypa);
   
   printf("%u %u %u", mypa.array, mypa.count0, mypa.count1);
   
   
    
    return 0;
}
