/*

Всего памяти
Описана структура данных для хранения информации об использованной памяти:
typedef struct list {
void *address;
size_t size;
char comment[64];
struct list *next;
} list;
Требуется реализовать только одну функцию, которая анализирует данный список и возвращает сколько 
всего памяти 
используется. 
Адрес хранится в поле address, поле size - соответствующий размер данного блока. 
Если список пустой, то функция должна возвращать 0.
Прототип функции:

size_t totalMemoryUsage(list *head)

 
*/
 
#include <stdio.h>
#include <stdint.h>

typedef struct list {
uint64_t address;
size_t size;
char comment[64];
struct list *next;
} list;


size_t totalMemoryUsage(list *head)
{
    list *l;
    l=head;
    
    if(!head) return 0;
    
    size_t max = 0;

    
    while(l){
        
        
        max+=l->size;
        
        l = l->next;
    }
    
    return max;
     
}
        
        
    
    




int main(int argc, char *argv[])
{
   
        
    return 0;
}
