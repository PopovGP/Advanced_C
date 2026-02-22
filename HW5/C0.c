/* С0
 * Вычеркивание
 * Сколько различных трехзначных чисел можно получить из заданного натурального N, 
 * вычеркивая цифры из его десятичной записи?
 * Examples
 * Input
 * 1111111111111111111111111
 * Output
 * 1
 */



#include <stdio.h>
#include <stdbool.h>

int arr[1024] = {0};
int nums[1024] = {0};

int main()
{

	char ch;
	int cnt=0;
	while(1)

	{
		ch=getchar();
		if (ch == '\n') break;
		//printf("%c\n", ch);
		
		arr[cnt]=ch-48;

		
		cnt++;
	}
	
	//printf("digits: %d\n", cnt);
	
	int res = 0;
	for (int i=0; i<cnt; i++)
	{
		for (int j=i; j<cnt; j++)
		{
			for (int k=j; k<cnt; k++)
			{
				if (i!=j&&i!=k&&j!=k)
				{
					int num = arr[i]*100 + arr[j]*10 + arr[k];
					if (num<100)
					{
						continue;
					}
					
					bool notFound = true;
					for (int m=0; m<res; m++)
					{
						if (num == nums[m]) 
						{
							notFound = false;
						}
					}
					
					if (notFound)
					{
						nums[res] = num;
						res++;
					}
					//printf("%u%u%u == %u\n", arr[i],arr[j],arr[k], num);
				}
			}
		}
	}
	printf("%u\n", res);
					
	
}
