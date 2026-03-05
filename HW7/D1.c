/* D1
Вид сверху
В программе описана структура для хранения двоичного дерева:
typedef struct tree {
datatype key;
struct tree *left, *right;
} tree;
Необходимо реализовать функцию, которая печатает вид дерева сверху.
Функция должна строго соответствовать прототипу:

void btUpView(tree *root)
Examples
Input
10 5 15 3 7 13 18 1 6 14 0
Output
1 3 5 10 15 18
 
*/

#include <stdio.h>
#include <stdlib.h>

#define datatype int


typedef struct tree {
datatype key;
struct tree *left, *right;
} tree;



void printTree(tree *root)
{

	static int depth = 0;
	
	//Это тестовый обход для отладки
	printf("Key: %d, depth: %d \n", root->key, depth);
	if (root->left) 
	{
		
		printf("Going left, depth: %d \n", depth);
		depth ++;
		printTree(root->left);
		depth --;
		//printf("%d ", root->key);
	}
	
	if (root->right) 
	{
		printf("Going right, depth: %d \n", depth);
		depth ++;
		printTree(root->right);
		depth --;
		//printf("%d ", root->key);
	}
	
	
	
}

//static int direction = 1;

void btUpView(tree *root)
{
	static int direction = 1;
	static int depth = 0;
	
	if (direction==1)
	{
	
	if (root) 
	{
		depth++;
		btUpView(root->left);
		printf("%d ", root->key);
		depth--;
		if (depth!=0) return;
		else
		{
			
			
			if (root->right) root=root->right;
			else return;
		}
			
		
	}
	else
	{
	
		direction = 2;
		
		return;

	}
	}
	
	if (direction==2)
	{
		
	if (root) 
	{
	printf("%d ", root->key);
		
		btUpView(root->right);

	}
	else
	{

		direction = 1;
	}
	}
		
	
}

int main()
{
	tree *p = malloc(sizeof(tree));
	p->key = 2;
	p->left = NULL;
	p->right = NULL;
	
	tree *p1 = malloc(sizeof(tree));
	p1->key = 1;
	p1->left = NULL;
	p1->right = NULL;
	
	p->left = p1;
	
	tree *p2 = malloc(sizeof(tree));
	p2->key = 3;
	p2->left = NULL;
	p2->right = NULL;
	
	p->right = p2;
	
	//direcion = 1;
	
	printTree(p);
	printf("\n");
	btUpView(p);
	
	printf("\n====================\n");
	printf("\n");
	printf("\n");
	
	p = malloc(sizeof(tree));
	p->key = 3;
	p->left = NULL;
	p->right = NULL;
	
	p1 = malloc(sizeof(tree));
	p1->key = 2;
	p1->left = NULL;
	p1->right = NULL;
	
	p->left = p1;
	
	p2 = malloc(sizeof(tree));
	p2->key = 1;
	p2->left = NULL;
	p2->right = NULL;
	
	p1->left = p2;
	
	printTree(p);
	printf("\n");
	btUpView(p);
	
	
	
		printf("=====================\n");
	printf("\n");
	printf("\n");
	
		 p = malloc(sizeof(tree));
	p->key = 1;
	p->left = NULL;
	p->right = NULL;
	
	 p1 = malloc(sizeof(tree));
	p1->key = 2;
	p1->left = NULL;
	p1->right = NULL;
	
	p->right = p1;
	
	 p2 = malloc(sizeof(tree));
	p2->key = 3;
	p2->left = NULL;
	p2->right = NULL;
	
	p1->right = p2;
	
	printTree(p);
	printf("\n");
	btUpView(p);
	
	
	
	
	
	
	
}
