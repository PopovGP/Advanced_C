/* D2
Найти брата
В программе описано двоичное дерево:
typedef struct tree {
datatype key;
struct tree *left, *right;
struct tree *parent; //ссылка на родителя
} tree;
Требуется реализовать функцию, которая по ключу возвращает адрес соседнего элемента - брата. Если такого ключа нет или у узла нет брата, то необходимо вернуть 0.
Прототип функции:

tree * findBrother(tree *root, int key)
Examples
Input
10 5 15 3 7 13 18 1 6 14 0 3
Output
7

*/
#include <stdio.h>
#include <stdlib.h>

#define datatype int

typedef struct tree {
datatype key;
struct tree *left, *right;
struct tree *parent; //ссылка на родителя
} tree;

/* Обход дерева
 */
tree * findBrother(tree *root, int key)
{
	
	static int found = 0;
	static int direction = 0;
	tree *p;
	
	//Это тестовый обход для отладки
	//printf("Key: %d, depth: %d \n", root->key, depth);
	//if (root->left) 
	//{
		
		//printf("Going left, depth: %d \n", depth);
		//depth ++;
		//btUpView(root->left);
		//depth --;
		////printf("%d ", root->key);
	//}
	
	//if (root->right) 
	//{
		//printf("Going right, depth: %d \n", depth);
		//depth ++;
		//btUpView(root->right);
		//depth --;
		////printf("%d ", root->key);
	//}
	
	//tree *p = root;
	
	
	//if (direction==1)
	//{
	
	if (root->key == key)
	{
		found = 1;
		if (root->parent)
		{
			if (direction==0 && root->parent->right)
			{
				return root->parent->right;
			} 
			
			if (direction==1 && root->parent->left)
			{
				return root->parent->left;
			} 
			return 0;
				
		}
		
		return 0;
			
	}
	
	if (root->left) 
	{
		//depth++;
		direction = 0;
		p = findBrother(root->left, key);
		if (found)
			return p;
		//printf("%d ", root->key);
		//depth--;
		//if (depth!=0) return;
		//else
		//{
			
			
			//if (root->right) root=root->right;
			//else return;
		//}
			
		
	}
	else
	{
		//printf("%d ", root->key);
		//direction = 2;
		
		//return;

	}
	//}
	
	//if (direction==2)
	//{
	if (root->right) 
	{
		direction = 1;
		//printf("%d ", root->key);
		p = findBrother(root->right, key);
		if (found)
			return p;
	}
	else
	{
		//printf("%d ", root->key);
		//direction = 3;
	}
	//}
		
	 return 0;
	
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
	
	findBrother(p, 3);
}

