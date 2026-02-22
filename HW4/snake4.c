#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <inttypes.h>
#include <string.h>
#include <unistd.h>

#define MIN_Y  2
enum {LEFT=1, UP, RIGHT, DOWN, STOP_GAME=KEY_F(10)};
enum {MAX_TAIL_SIZE=100, START_TAIL_SIZE=3, MAX_FOOD_SIZE=20, FOOD_EXPIRE_SECONDS=10};



// Здесь храним коды управления змейкой
struct control_buttons
{
    int down;
    int up;
    int left;
    int right;
}control_buttons;

struct control_buttons default_controls = {KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT};

#define MAX_KEYS 3
struct keys
{
	int direction;
	int buttons[MAX_KEYS];
} ;

/*
 Голова змейки содержит в себе
 x,y - координаты текущей позиции
 direction - направление движения
 tsize - размер хвоста
 *tail -  ссылка на хвост
 */
typedef struct snake_t
{
    int x;
    int y;
    int direction;
    size_t tsize;
    struct tail_t *tail;
    struct control_buttons controls;
    struct keys mycontrols[4]; //Доработал
} snake_t;

/*
 Хвост это массив состоящий из координат x,y
 */
typedef struct tail_t
{
    int x;
    int y;
} tail_t;

void initTail(struct tail_t t[], size_t size)
{
    struct tail_t init_t={0,0};
    for(size_t i=0; i<size; i++)
    {
        t[i]=init_t;
    }
}
void initHead(struct snake_t *head, int x, int y)
{
    head->x = x;
    head->y = y;
    head->direction = RIGHT;
    //начало вставки
    head->mycontrols[0].direction = RIGHT;
    head->mycontrols[0].buttons[0] = KEY_RIGHT;
    head->mycontrols[0].buttons[1] = 'D';
    head->mycontrols[0].buttons[2] = 'd';
    
    head->mycontrols[1].direction = LEFT;
    head->mycontrols[1].buttons[0] = KEY_LEFT;
    head->mycontrols[1].buttons[1] = 'A';
    head->mycontrols[1].buttons[2] = 'a';
    
    head->mycontrols[2].direction = UP;
    head->mycontrols[2].buttons[0] = KEY_UP;
    head->mycontrols[2].buttons[1] = 'W';
    head->mycontrols[2].buttons[2] = 'w';
    
    head->mycontrols[3].direction = DOWN;
    head->mycontrols[3].buttons[0] = KEY_DOWN;
    head->mycontrols[3].buttons[1] = 'S';
    head->mycontrols[3].buttons[2] = 's';
    
    
    
}

void initSnake(snake_t *head, size_t size, int x, int y)
{
	tail_t*  tail  = (tail_t*) malloc(MAX_TAIL_SIZE*sizeof(tail_t));
    initTail(tail, MAX_TAIL_SIZE);
    initHead(head, x, y);
    head->tail = tail; // прикрепляем к голове хвост
    head->tsize = size+1;
    head->controls = default_controls;
}

/*
 Движение головы с учетом текущего направления движения
 */
void go(struct snake_t *head)
{
    char ch = '@';
    int max_x=0, max_y=0;
    getmaxyx(stdscr, max_y, max_x); // macro - размер терминала
    mvprintw(head->y, head->x, " "); // очищаем один символ
    switch (head->direction)
    {
        case LEFT:
            //if(head->x <= 0) // Циклическое движение, чтобы не
 //уходить за пределы экрана
                //head->x = max_x;
                
                //стало:
            
            if (head->x <= 0)
            {
				 head->direction = DOWN;
				 head->x=0;
				 head->y= head->y+1;
			}
			else
			{
				
				head->x =  head->x - 1;
			}
           
            //----
            mvprintw(head->y, head->x, "%c", ch);
        break;
        case RIGHT:
        
        //стало:
            if (head->x >= max_x-1)
            {
				 head->direction = UP;
				 head->x=max_x - 1;
				 head->y=head->y==MIN_Y-1?MIN_Y-1:head->y - 1;
			}
			else
			{
				head->x  = head->x + 1;
				
			}
			//-----	
        
            mvprintw(head->y, head->x, "%c", ch);
        break;
        case UP:
        
         
            //стало:
            if (head->y <= MIN_Y-1)
            {
				 head->direction = LEFT;
				 head->y=MIN_Y-1;
				 head->x=head->x-1;
			}
			else
			{
				head->y  = head->y - 1;
				
			}
			//-----	
			
            mvprintw(head->y, head->x, "%c", ch);
        break;
        case DOWN:
        
        //стало:
            if (head->y >= max_y - 1)
            {
				 head->direction = RIGHT;
				 head->y=max_y - 1;
				 head->x=head->x+1;
			}
			else
			{
				head->y = head->y + 1;
				
			}
			//-----	
            mvprintw(head->y, head->x, "%c", ch);
        break;
        default:
        break;
    }
    refresh();
}

void changeDirection(struct snake_t* snake, const int32_t key)
{
	for (size_t i=0; i<4; i++)
	{
		for (size_t j=0; j<MAX_KEYS; j++)
		{
			if (key==snake->mycontrols[i].buttons[j])
			{
				if 
					((snake->direction==UP&&snake->mycontrols[i].direction==DOWN) ||
					(snake->direction==DOWN&&snake->mycontrols[i].direction==UP) ||
					(snake->direction==LEFT&&snake->mycontrols[i].direction==RIGHT) ||
					(snake->direction==RIGHT&&snake->mycontrols[i].direction==LEFT) )
						break;
					
				snake->direction = snake->mycontrols[i].direction;
				break;
				
			}
		}
	}
    //if (key == snake->controls.down)
        //snake->direction = DOWN;
    //else if (key == snake->controls.up)
        //snake->direction = UP;
    //else if (key == snake->controls.right)
        //snake->direction = RIGHT;
    //else if (key == snake->controls.left)
        //snake->direction = LEFT;
        
     
}

/*
 Движение хвоста с учетом движения головы
 */
void goTail(struct snake_t *head)
{
    char ch = '*';
    mvprintw(head->tail[head->tsize-1].y, head->tail[head->tsize-1].x, " ");
    for(size_t i = head->tsize-1; i>0; i--)
    {
        head->tail[i] = head->tail[i-1];
        if( head->tail[i].y || head->tail[i].x)
            mvprintw(head->tail[i].y, head->tail[i].x, "%c", ch);
    }
    head->tail[0].x = head->x;
    head->tail[0].y = head->y;

}
void myTimeout(size_t tm)
{
	clock_t start = clock();

        while(1)
        {
			clock_t finish = clock();
			double ms = (double)(finish - start)/CLOCKS_PER_SEC*1000;
		   
			if (ms>=tm)
			{
				break;
			}
		}
}


//Вставленный код
bool isBittenByItself(struct snake_t* snake)
{
    for(size_t i = snake->tsize-1; i>0; i--){
		for(size_t j = snake->tsize-1; j>0; j--){
			if (i!=j) {
				if (snake->tail[i].x == snake->tail[j].x && snake->tail[i].y == snake->tail[j].y
				&& (snake->tail[i].x || snake->tail[i].y 
					|| snake->tail[j].x|| snake->tail[j].y )
				){
					return true;
				}
			}
		}
	}
	return false;
}
//==

int main()
{
	

	snake_t* snake = (snake_t*)malloc(sizeof(snake_t));
    initSnake(snake,START_TAIL_SIZE,10,10);
    initscr();
    keypad(stdscr, TRUE); // Включаем F1, F2, стрелки и т.д.
    raw();                // Откдючаем line buffering
    noecho();            // Отключаем echo() режим при вызове getch
    curs_set(FALSE);    //Отключаем курсор
    mvprintw(0, 0,"Use arrows for control. Press 'F10' for EXIT");
    timeout(0);    //Отключаем таймаут после нажатия клавиши в цикле
    int key_pressed=0;
    while( key_pressed != STOP_GAME )
    {
       
        go(snake);
        goTail(snake);
        
        if (isBittenByItself(snake))
        {
			break;
			
		}
        
        key_pressed = getch(); // Считываем клавишу
        //mvprintw(1, 1, "%c", key_pressed);
        //mvprintw(2, 1, "%u", key_pressed);
        
        myTimeout(100);
        //timeout(100); // Задержка при отрисовке
        changeDirection(snake, key_pressed);
        
    }
    free(snake->tail);
    free(snake);
    endwin(); // Завершаем режим curses mod
    return 0;
}
