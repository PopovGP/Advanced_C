/*
 * Сколько раз встречается максимум
На стандартном потоке ввода задаётся натуральное число N (N > 0), после которого следует последовательность 
из N целых чисел.На стандартный поток вывода напечатайте, сколько раз в этой последовательности встречается
 максимум. Указание: использовать массивы запрещается.
 */



#include <stdio.h>

int main(int argc, char *argv[])
{
    unsigned int N;
    int number, max, numberOfOccurences;
    scanf("%ud", &N);
   
    for (int i=0; i<N; i++)
    {
         scanf("%d", &number);
         if (i==0)
         {
            max = number;
            numberOfOccurences = 0;
         }
             
         if (number>max)
         {
            max = number;
            numberOfOccurences = 1;
         }
         else if (number==max)
         {
            numberOfOccurences ++; 
         }
  
    }
    printf("%u", numberOfOccurences);
        
    return 0;
}
