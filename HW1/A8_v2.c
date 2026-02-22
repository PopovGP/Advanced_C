/* 

Весы
В стартер боксе Geek Brains есть электронные чашечные весы (вместимость каждой чашки 1 тонна) и гири 
массами 1г, 3г, 9г, 27г, и т.д. по одной штуке каждой массы. 
Менеджер из рекламного отдела взял такие весы и не знает, можно ли взвесить что-нибудь тяжелое и если можно, 
сколько гирь придется положить на весы (на любую чашку). Надо помочь ему. 
Формат входных данных: единственное натуральное число – масса взвешиваемого товара в граммах 
(не больше 1 000 000 000). 
Формат выходных данных: единственное целое число – общее количество гирь или 
число –1 если данный товар взвесить невозможно.



*/
#define WEIGHTS_SIZE 19

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h> //C23

uint32_t iterations = 0;

bool mustExit = false; //C23

//int8_t counter = -1;

int32_t sum = 0;

int8_t coeffs[WEIGHTS_SIZE]={0};

int8_t arr[3]={-1,0,1};

int8_t result = -1;

uint32_t N;

uint32_t weights[WEIGHTS_SIZE]={
1,
3,
9,
27,
81,
243,
729,
2187,
6561,
19683,
59049,
177147,
531441,
1594323,
4782969,
14348907,
43046721,
129140163,
387420489
};


void printData();

//Результат должен быть равен нулю
int32_t calc()
{
    int32_t mysum = 0;
    for (int i=0;i<WEIGHTS_SIZE;i++)
    {
        mysum = mysum + weights[i]*coeffs[i];
    }
    return mysum-N;
}

void perebor(uint8_t counter)
{
    if (mustExit) return;
    iterations++;
    
  //  if (iterations>100) { mustExit = true; return;};
    if (iterations%100000000==0) printf("iterations=%u  counter=%u\n", iterations, counter); 
    
    //counter++;
    if (counter==WEIGHTS_SIZE)
    {
        
        
       // sum = calc();
       // if (sum==0)
       // {
      //      mustExit = true;
      //      printData();
            
            
            
       //     return;
       // }
       
        
        return;
    }
    
    for (uint8_t i=0;i<3;i++)
    {
        coeffs[counter] = arr[i];
     
        perebor(counter+1);  
    }      
    
    
}
        
   
void printData()
{
    result = 0;
    for (int i=0;i<WEIGHTS_SIZE;i++)
    {
        printf("i=%d weight=%d, coeff=%d\n", i, weights[i], coeffs[i]);
        if (coeffs[i]!=0) result++;
    }
    
}


int main(int argc, char *argv[])
{
   
   
      
   
  
    scanf("%u", &N);
    
    perebor(0);

    
    
    
   
    printf("%d\n", result);
    printf("iterations=%u\n", iterations);
   
 
   
    
    return 0;
}
