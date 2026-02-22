/* С1

Префикс и суффикс
На стандартном потоке ввода задаются две символьные строки, разделённые символом перевода строки. 
Каждая из строк не превышает по длине 10000 символов. В строках не встречаются пробельные символы. 
На стандартный поток вывода напечатайте два числа, разделённых пробелом: первое число — длина 
наибольшего префикса первой строки, являющегося суффиксом второй; второе число — наоборот, 
длина наибольшего суффикса первой строки, являющегося префиксом второй. Сравнение символов 
проводите с учётом регистра (т.е. символы 'a' и 'A' различны).



 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAXLEN 10000


int main()
{

	char str1[MAXLEN+1]={0};
	char str2[MAXLEN+1]={0};
	
	scanf("%s",str1);
	scanf("%s",str2);
	
	size_t str1len = strlen(str1);
	size_t str2len = strlen(str2);
	
	size_t i=0;
	size_t j=0;
	int res1=0;
	int res2=0;
	
	int oldres1=0;
	int oldres2=0;

	
	bool pass1 = true;
	bool pass2 = true;
	
	//bool oldpass1 = true;
	//bool oldpass2 = true;
	while(1)
	{
		if (i>=str1len||i>=str2len) break;
		
		j = 0;
		
		//oldres1 = res1;
		//oldres2 = res2;
		
		pass1 = true;
		pass2 = true;
		
		res1=0;
		res2=0;
		
		//printf("**********************\n");
		while(1)
		{
			if (j>i) break;
			//printf("======\n");
			//printf("i=%d j=%d %c %c\n", i, j, str1[j], str2[str2len-(i-j)-1]);
			//printf("i=%d j=%d %c %c\n", i, j, str2[j], str1[str1len-(i-j)-1]);
			
			if(str1[j]==str2[str2len-(i-j)-1]&&pass1) res1++;
			else pass1 = false;
			
			if(str2[j]==str1[str1len-(i-j)-1]&&pass2) res2++;
			else pass2 = false;
			
			//printf("	res1=%d\n", res1);
			//printf("	res2=%d\n", res2);
			
			
			
			j++;
		}
		
		//if (!res1&&!res2) break;
		
		if (res1>oldres1&&pass1) oldres1 = res1;
		if (res2>oldres2&&pass2) oldres2 = res2;
		
		i++;
		
	
	} 
	
	printf("%d %d", oldres1, oldres2);
}
