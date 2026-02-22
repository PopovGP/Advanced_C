/* С2

Польская запись
Необходимо вычислить выражение написанное в обратной польской записи.
 На вход подается строка состоящая из целых, неотрицательных чисел и арифметических символов. 
 В ответ единственное целое число - результат. 
 Более подробно об Обратной польскаязапись числа можно также почитать тут

Examples


 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h> // Для errno
#include <limits.h> // Для LONG_MAX, LONG_MIN
#include <stdlib.h>

int stack[1024]={0}; //Сделаем стек на массиве
size_t curPos = -1;   //-1 = стек пустой
 

/* https://metanit.com/c/tutorial/10.6.php
 * Возвращает:
 * 0 - ошибка, строка не распознана
 * 1 - распознано число, в resNumber заполняется это число
 * 2 - распознан знак операции, в sign заполняется символ этой операции
 */

int extractData(char *str, long *result, char *sign)
{
	
    char *endptr;

    int status = 0;
   
 
    errno = 0; // Сбрасываем errno перед вызовом
    *result = strtol(str, &endptr, 10);
 
    // Проверяем возможные ошибки
    if (errno == ERANGE) {
        status = 0; //puts("Произошло переполнение! Значение слишком велико");
        if (*result == LONG_MAX) {
            status = 0; //puts("Переполнение вверх (MAX)");
        } else if (*result == LONG_MIN) {
            status = 0; //puts("Переполнение вниз (MIN)");
        }
    }
    // Проверяем, были ли преобразованы какие-либо цифры
    else if (endptr == str) {
        //puts("Не найдено ни одной цифры для преобразования");
        *sign = str[0];
        status = 2;
    }
    // Проверяем, дошли ли мы до конца строки ('\0')
    else if (*endptr != '\0') {
        //printf("Преобразование успешно, но остановилось на символе: '%c'\n", *endptr);
       // printf("Остаток строки: '%s'\n", endptr);
       status = 0;
    }
    else {
       // puts("Преобразование прошло успешно и полностью.");
       status = 1;
    }
 
    //printf("Результат: %ld\n", *result);
    return status;
}

void push (int num)
{
	curPos ++;
	
	stack[curPos] = num;
	//printf("push: %d curPos: %d\n", stack[curPos], curPos);
}

int pop()
{
	//printf("pop: %d curPos: %d\n", stack[curPos], curPos);

	return stack[curPos--];
}

int main()
{
	
	
	int a,b;
	char ch[1024];
	long number;
	char sign;
	bool breakCondition = false;
	while(scanf("%s",&ch))
	{
		//printf("%s\n", ch);
		size_t len = strlen(ch);
		
		
		
		if (ch[len-1]=='.') 
		{
			ch[len-1]='\0';
			breakCondition = true;
		}
		
		sign = '\0';
		int res = extractData(ch, &number, &sign);
		if (res == 1) // Это число
		{
			push(number);
		}
		else if (res==2) //это знак
		{
			switch(sign)
			{
				case '+': 
				//	printf("%c\n", sign);
			
					push(pop()+pop());
					break;
					
				case '-': 
					a = pop();
					b= pop();
					push(b-a);
					break;
					
				case '*': 
					push(pop()*pop());
					break;
				case '/': 
					
					a = pop();
					b = pop();
					push(b/a);
					break;
					
				default: 
					printf("Ошибка, нераспознанный знак операции %c!\n", sign);
				
			}
		}
		//printf("sign=%c\n", sign);
		
		if (breakCondition) break;
		
		
	}
	
	printf("%d", pop());
	
}
