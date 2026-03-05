/* D0
Отсортировать слова
Дана строка, состоящая из английских букв и пробелов. В конце строки символ точка. 
Все слова разделены одним пробелом. 
Необходимо составить из слов односвязный список и упорядочить по алфавиту. 
Список необходимо удалить в конце программы. 
Для сравнение строк можно использовать strcmp. 
Необходимо использовать данную структуры организации списка.

struct list {
char word[20];
struct list *next;
}
Необходимо реализовать односвязный список и обслуживающие его функции.

add_to_list
swap_elements
print_list
delete_list

Examples
Input
efg abcd zzz.
Output
abcd efg zzz
Input
fffff kkkkkk a.
Output
a fffff kkkkkk

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct list {
char word[20];
struct list *next;
} ;

struct list* add_to_list(struct list *l, char w[20])
{
	struct list *tmp = l;
	if(tmp)
	
			while(tmp->next)
			{
				tmp=tmp->next;
			}
	
	
	
	
		
	struct list *p = (struct list *) malloc(sizeof(struct list));
	p->next=NULL;
	strcpy(p->word, w);
	
	
	if(l)
	{
		tmp->next = p;
		return l;
	}
	return p;


}
	

void swap_elements(struct list *l1, struct list *l2)
{
	//struct list *temp = l1->next;
	//l1->next = l2->next;
	
	//l2->next = temp;
	
	char tmp[20];
	strcpy(tmp, l1->word);
	
	strcpy(l1->word, l2->word);
	strcpy(l2->word , tmp);
	
	
}

void print_list(struct list *l)
{
	//list *temp;
	//temp = l;
	while(l)
	{
		printf("%s ", l->word);
		l=l->next;
	}
}

void delete_list(struct list *l)
{
	
	while(l)
	{
		struct list *temp;
		temp = l->next;
		free(l);
		l=temp;
	}
}
	

    	
int main()
{
	struct list * myL=NULL;
	
	char arr[20];
	while(true)
	{
		scanf("%s", &arr);
		//printf("%s\n", arr);
		int len = strlen(arr);
		if (len>0) 
		{
			if(arr[len-1]=='.')
			{
				arr[len-1]=0;
				myL = add_to_list(myL, arr);
				//myCmp(myL);
				break;
			}
			myL = add_to_list(myL, arr);
			//myCmp(myL);
				
		}
	}
	
	struct list *l1;
	struct list *l2;
	
	l1 = myL;
	l2 = myL;
	
	while(l1)
	{
		l2 = myL;
		while(l2)
		{
			int result1 = strcmp(l1->word, l2->word);
			if (result1<0)
			{
				  //printf("s1 is greater than s2.\n");
				  swap_elements(l1, l2);
			}
			
			l2=l2->next;
		}
		
		l1=l1->next;
	}
	
	print_list(myL);
	
	delete_list(myL);

}

