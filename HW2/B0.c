/*
 * 
Максимальный блок
Описана структура данных
typedef struct list {
uint64_t address;
size_t size;
char comment[64];
struct list *next;
} list;
Требуется реализовать только одну функцию, которая в данном списке находит адрес блока памяти занимающий больше всего места.
Адрес хранится в поле address, поле size - соответствующий размер данного блока. Если список пустой, то функция должна возвращать 0. Если есть несколько таких блоков, то вернуть адрес любого из них.
Прототип функции:

uint64_t findMaxBlock(list *head)

 
 */
 
#include <stdio.h>
#include <stdint.h>

typedef struct list {
uint64_t address;
size_t size;
char comment[64];
struct list *next;
} list;

uint64_t findMaxBlock(list *head)
{
    list *l;
    l=head;
    
    size_t max = 0;
    uint64_t maxAddress = 0;
    
    while(l){
        
        if (l->size>max)
        {
            max=l->size;
            maxAddress=l->address;
        }
        l = l->next;
    }
    
    return maxAddress;
     
}
        
        
    
    




//int main(int argc, char *argv[])
//{
   
        
    //return 0;
//}
