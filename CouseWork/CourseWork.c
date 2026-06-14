#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <math.h>
#include <stdbool.h>

/* 
 * Тестовая функция, не используется
 */
void printArguments(int argc, char **argv)
{
	for (int i=0; i<argc; i++)
	{
		printf("Arg # %d = %s\n", i, argv[i]);
	}
}

void printHelp()
{
	printf("Использование: CouseWork [-i -a -tr -ti | -help]\n");
	printf("При указании -i печатаются итерации\n");
	printf("При указании -a печатаются абсциссы точек пересечения функций.\n");
	printf("При указании -tr производится тест функции root.\n");
	printf("При указании -ti производится тест функции integral.\n");
}
	
extern char *optarg;
extern int optind, opterr, optopt;

/* Первая функция
 * 
 * f1 = 0.6*x+3
 */
float f1(float x)
{
	return 0.6*x+3;
	
}

/*
 * Вторая функция
 * 
 * f2 = (x-2)^3 - 1
 */
float f2(float x)
{
	return (x-2)*(x-2)*(x-2) - 1;
}

/*
 * Третья функция
 * 
 * f3 = 3/x;
 */
float f3(float x)
{
	return 3/x;
}

/*
 * Тестовая функция для интеграла
 * f(x)=1;
 */
float integralTestFunc(float x)
{
	return 1;
}

/*
 * Тестовая функция для нахождения корня уравнения
 * f(x)=2x;
 */
float abstissTestFunc(float x)
{
	return 2*x;
}

/*
 * Пустая функция, всегда возвращает нуль
 */
float nullFunc(float x)
{
	return 0;
}


int rootError = 0;
size_t iterations = 0;

//Переменные для определения опций командной строки
bool optionI = false; //Печатать итерации


/* 
 * 
 * Функция rootAb вычисляет с точностью eps1 корень x уравнения f(x)=0
 * f - указатель на функцию
 * a и b - это левая и правая граница интервала
 * 
 * Если интервал не подходит, то глобальная переменная rootError становится 
 * равной единице, а сама функция возвращает 0
 * 
 * Если корень найден, то глобальная переменная rootError = 0
 *
 * Считаем, что b всегда больше a, и f() определена на интервале a,b
 */
float root(float f(float), float g(float), float a, float b,float eps1)
//float rootAb(float f(float), float a, float b, float eps1)
{
	
	rootError = 0;

	
	float prevF = 0;
	float res3 = 0;
	int i = 0;
	
	while (1)
	{
		i++;
		
		float res1 = f(a)-g(a);
		float res2 = f(b)-g(b);

		if (res1==0)
			return a;
		if (res2==0)
			return b;
		
		if (optionI)	
			printf("Итерация № %d, a=%f, f(a)=%f, b=%f, f(b)=%f\n", i, a, res1, b, res2);
			
		if (( (res1>0)&&(res2<0))||((res1<0)&&(res2>0))) //Меняется знак
		{
			float c = (b-a)/2; //Делим интервал на двое
			res3 = f(a+c)-g(a+c);
			
			if (optionI)	
			printf("\t  c=%f, a+c=%f, f(a+c)=%f\n", c, a+c, res3);
			
			if (fabs(fabs(res3)-fabs(prevF)) < eps1)
			{
				return a+c;
			}
			
			if (((res1>0)&&(res3<0))||((res1<0)&&(res3>0)))
			{
				b = b-c;
				if (optionI)	
				printf("\t    b=%f, c=%f\n", b, c);
				prevF = res3;
			}
			else
			{
				a = a+c;
				if (optionI)	
				printf("\t    a=%f, c=%f\n", a, b);
				prevF = res3;
			}

			
		}
		else 
		{
			rootError = 1;
			return 0;
		}	
		
		iterations++;
	}

	return 0;
}




/* 
 * 
 * Функция root вычисляет с точностью eps1 корень x уравнения f(x)=g(x)
 * f и g - это указатели на функции 
 * a и b - это левая и правая граница интервала
 * 
 * Если интервал не подходит, то глобальная переменная rootError становится 
 * равной единице, а сама функция возвращает 0
 * 
 * Если корень найден, то глобальная переменная rootError = 0
 *
 */
/* float root(float f(float), float g(float), float a, float b,float eps1)
{
	 
	return rootAb(f_all(f,g,;
} */



/* 
 * 
 * Функция integral вычисляет определенный интеграл
 * на интервале a,b с точностью eps2
 *
 * Решаю методом прямоугольников
 */
float integral(float f(float), float a, float b, float eps2)
{
	float sum = 0;
	float prevSum = 0;
	float tempA, tempB;
	size_t i=0;
	while(1)
	{
		i++;
		
		float section = fabs(b-a)/i;
		tempA = a;
		tempB = a;
		
		sum = 0;
		
		while(1)
		{
			float func = f(tempA);
			tempB += section;
			
			if (tempB>b) break;
			
			sum = sum + fabs(func) * fabs(tempB-tempA);
			
			tempA = tempB;
			
		}
		
		if (fabs(fabs(sum)-fabs(prevSum))<eps2) break;
		
		prevSum = sum;
		
	}
	return sum;
}

int main(int argc, char **argv)
{

//Страница справки: https://www.opennet.ru/man.shtml?topic=getopt_long_only&category=3&russian=0
	
/*
 * Подсказка
 * 
* struct option {
* const char *name;
* int has_arg;
* int *flag;
* int val;
* };
*/




/*
 Значения различных полей:

name
	является именем длинной опции.
has_arg
	может быть: no_argument (или 0), если опция не имеет аргумента; required_argument (или 1), если опция требует указания аргумента; optional_argument (или 2), если опция может иметь необязательный аргумент.
flag
	задает способ возвращения результатов для длинной опции. 
	Если flag равен NULL, то getopt_long() возвращает val. 
	Hапример, вызывающая программа может назначить val эквивалентом символа короткой опции. 
	В противном случае getopt_long() возвращает 0, а flag указывает на переменную, 
	устанавливаемое значение которой равно val, если опция найдена; 
	и оставляемую без изменений, если опция не найдена.
val
	является возвращаемым значением или загружается в переменную, на которую указывает flag.
*/

	 static struct option long_options[] = {
            {"tr", 0, 0, 0},
            {"ti", 0, 0, 1},
            {"help", 0, 0, 2},
            {"i", 0, 0, 3},
            {"a", 0, 0, 4},
            {0, 0, 0, 0}
        };

	int c;

    
    //Переменные для определения опций командной строки
    bool optionA = false; //Печатать абсциссы функций
    bool optionTR = false; //тестирование вычисления корня уравнения
    bool optionTI = false; //тестирование вычисления интеграла
   
   
   
	while (1) {
      
        int option_index = 0;
       

        c = getopt_long_only (argc, argv, "",
                 long_options, &option_index);
        if (c == -1)
            break;

        switch (c) {
        case 0:
			optionTR = true;
			
            //printf ("параметр 0 %s", long_options[option_index].name);
            //if (optarg)
            //    printf (" с аргументом %s", optarg);
            //printf ("\n");
            
            break;

		case 1:
			optionTI = true;
			
			//printf ("параметр 1 %s", long_options[option_index].name);
           
            //if (optarg)
            //    printf (" с аргументом %s", optarg);
            //printf ("\n");
            break;
		case 2: //Если запрашивают справку, то сразу её выводим
		    //printf ("параметр 2 %s", long_options[option_index].name);
            //if (optarg)
            //    printf (" с аргументом %s", optarg);
            //printf ("\n");
            printHelp();
            return 1;
            break;
		case 3:
			optionI = true;
			//printf ("параметр %s \n", long_options[option_index].name);
            break;
            
        case 4:
			optionA = true;
			//printf ("параметр %s \n", long_options[option_index].name);
            break;
            
        default: //Если неподдерживаемая опция, то сразу выводим справку и ничего не делаем.
            //printf ("?? getopt возвратило код символа 0%o ??\n", c);
            printf ("Указана неподдерживаемая опция\n");
            printHelp();
            return 1;
        }
    }

	float r12 = root(f1, f2, 0, 5, 0.00001);
	float r13 = root(f1, f3, 0, 5, 0.00001);
	float r23 = root(f2, f3, 0, 5, 0.00001);
	
	
	if (optionA) {
		printf ("Корень функции f1-f2 на интервале [0,5] равен %f\n", r12);
		printf ("Корень функции f1-f3 на интервале [0,5] равен %f\n", r13);
		printf ("Корень функции f2-f3 на интервале [0,5] равен %f\n", r23);
	}
	
	float I1 = integral(f1, r13, r12, 0.00001);
	float I2 = integral(f2, r23, r12, 0.00001);
	float I3 = integral(f3, r13, r23, 0.00001);
	
	printf("Интеграл под функцией 1 равен %f\n", I1);
	printf("Интеграл под функцией 2 равен %f\n", I2);
	printf("Интеграл под функцией 3 равен %f\n", I3);
	
	printf("Итоговый ответ курсовой работы: Размер области между графиками функций f1, f2, f3 равен %f\n", I1-I2-I3);
	
	//printf("Integral f1=%f\n", integral(f1, 1,5,0.00001));
	//printf("rootAb f1=%f, rootError: %d\n", rootAb(f1, -16,22,0.001), rootError);
	//printf("rootAb f2=%f, rootError: %d\n", rootAb(f2, -20,40,0.001), rootError);
	
	
    
    if (optionTI)
    {
		printf("Тестовая функция f(x)=1 для вычисления интеграла на интервале [0,10]=%f\n", integral(integralTestFunc, 0,10,0.00001));
	}
	
	if (optionTR)
    {
		printf("Тестовая функция f(x)=2x для вычисления корня функции на интервале [-10,10]=%f\n", root(abstissTestFunc, nullFunc, -10,10,0.00001));
	}
		       
}
