#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <inttypes.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>

#define MIN_Y  2
enum {LEFT=1, UP, RIGHT, DOWN, STOP_GAME=KEY_F(10)};
enum {MAX_TAIL_SIZE=100, START_TAIL_SIZE=3, MAX_FOOD_SIZE=50, FOOD_EXPIRE_SECONDS=10};


struct food_type
{
	int x,y;  //где стоит еда
	int type; //1 - взрыв, 2 - уменьшение, 3 - увеличение
	clock_t start; //когда еда появилась
};
struct food_type arrFood[MAX_FOOD_SIZE]={{-1,-1,-1,-1}};


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
void initHead2(struct snake_t *head, int x, int y)
{
    head->x = x;
    head->y = y;
    head->direction = RIGHT;
    //начало вставки
    head->mycontrols[0].direction = RIGHT;

    head->mycontrols[0].buttons[1] = 'D';
    head->mycontrols[0].buttons[2] = 'd';
    
    head->mycontrols[1].direction = LEFT;

    head->mycontrols[1].buttons[1] = 'A';
    head->mycontrols[1].buttons[2] = 'a';
    
    head->mycontrols[2].direction = UP;
 
    head->mycontrols[2].buttons[1] = 'W';
    head->mycontrols[2].buttons[2] = 'w';
    
    head->mycontrols[3].direction = DOWN;

    head->mycontrols[3].buttons[1] = 'S';
    head->mycontrols[3].buttons[2] = 's';
    
    
    
}

void initHead(struct snake_t *head, int x, int y)
{
    head->x = x;
    head->y = y;
    head->direction = RIGHT;
    //начало вставки
    head->mycontrols[0].direction = RIGHT;
    head->mycontrols[0].buttons[0] = KEY_RIGHT;
 
    
    head->mycontrols[1].direction = LEFT;
    head->mycontrols[1].buttons[0] = KEY_LEFT;

    
    head->mycontrols[2].direction = UP;
    head->mycontrols[2].buttons[0] = KEY_UP;

    
    head->mycontrols[3].direction = DOWN;
    head->mycontrols[3].buttons[0] = KEY_DOWN;
  
  
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

void initSnake2(snake_t *head, size_t size, int x, int y)
{
	tail_t*  tail  = (tail_t*) malloc(MAX_TAIL_SIZE*sizeof(tail_t));
    initTail(tail, MAX_TAIL_SIZE);
    initHead2(head, x, y);
    head->tail = tail; // прикрепляем к голове хвост
    head->tsize = size+1;
    head->controls = default_controls;
}

/*
 Движение головы с учетом текущего направления движения
 */
void go(struct snake_t *head, char ch)
{
    //char ch = ch;
   
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
void goTail(struct snake_t *head, char ch)
{
  //  char ch = '*';
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

int displayMenu(int numMenu)
{
	switch(numMenu)
	{
		case 0:
		 erase();
	 mvprintw(0, 0, "0 - Начать игру ");
	 mvprintw(1, 0, "1 - Настройки скорости ");
	 mvprintw(2, 0, "2 - Настройки цвета ");
	 mvprintw(3, 0, "3 - Выход ");
	 break;
	 
	case 1: 
	  erase();
	 mvprintw(0, 0, "0 - Нормальная скорость ");
	 mvprintw(1, 0, "1 - Повышенная скорость ");
	 mvprintw(2, 0, "9 - Возврат в предыдущее меню ");
	break;
	
	case 2:
	
	  erase();
	 
	mvprintw(0, 0, "0 - COLOR_GREEN, COLOR_WHITE");
	mvprintw(1, 0, "1 - COLOR_CYAN, COLOR_MAGENTA");
	mvprintw(2, 0, "2 - COLOR_RED, COLOR_WHITE");
	mvprintw(3, 0, "3 - COLOR_GREEN, COLOR_YELLOW");
	mvprintw(4, 0, "4 - COLOR_RED, COLOR_WHITE");
	mvprintw(5, 0, "5 - COLOR_WHITE, COLOR_RED");
	mvprintw(6, 0, "9 - Возврат в предыдущее меню ");
	
	break;
}

 int key_pressed = getch(); // Считываем клавишу
 erase();
 return key_pressed;
	
	
		
	
}

void initFood()
{
	for (int i=0; i<MAX_FOOD_SIZE; i++)	
	{
		arrFood[i].type = -1;
		arrFood[i].x = -1;
		arrFood[i].y = -1;
	}
}
	
void foodExpire()
{
	for (int i=0; i<MAX_FOOD_SIZE; i++)	
	{
		if (arrFood[i].x!=-1&&arrFood[i].y!=-1)
		{
			clock_t finish = clock();
			if ((double)(finish - arrFood[i].start)/CLOCKS_PER_SEC>FOOD_EXPIRE_SECONDS)
			{
				mvprintw(arrFood[i].y, arrFood[i].x, " ");
				arrFood[i].type = -1;
				arrFood[i].x = -1;
				arrFood[i].y = -1;
			}
		}
	}
}

void addFood(int x, int y, int type)
{
	//mvprintw(0, 60, " x=%d, y=%d, type=%d  ", x, y, type);
	
	for (int i=0; i<MAX_FOOD_SIZE; i++)	
	{
		if (arrFood[i].x==-1&&arrFood[i].y==-1)
		{
			//mvprintw(0, 90, " i=%d  ", i);
			
			char f;
			switch (type)
			{
				case 1: f='X'; break;
				case 2: f='-'; break;
				case 3: f='+'; break;
			}
				//mvprintw(0, 90, " i=%d  ", i);
				
				arrFood[i].type = type;
				arrFood[i].x = x;
				arrFood[i].y = y;
				arrFood[i].start = clock();
				
				mvprintw(arrFood[i].y, arrFood[i].x, "%c", f);
				
				//mvprintw(0, 0, " x=%d, y=%d, type=%c   ", x, y, f);
				return;
			
		}
	}
}

int isFoodTaken(struct snake_t *head)
{
	for (int i=0; i<MAX_FOOD_SIZE; i++)	
	{
		if (arrFood[i].x!=-1&&arrFood[i].y!=-1)
		{
			 if (head->y==arrFood[i].y&&head->x==arrFood[i].x)
			 {
				 if (arrFood[i].type == 1) return 1; //Съели яд для змеи
				 if (arrFood[i].type == 2) //уменьшаем размер
				 {
					 
					 mvprintw(head->tail[head->tsize-1].y, head->tail[head->tsize-1].x, " ");
					 
						head->tail[head->tsize-1].x = 0;
						head->tail[head->tsize-1].y = 0;
						
						head->tsize--;
    
				 }
				 
				 if (arrFood[i].type == 3) //увеличиваем размер размер
				 {
					 
						
						
						
						head->tail[head->tsize].x = head->tail[head->tsize-1].x;
						head->tail[head->tsize].y = head->tail[head->tsize-1].y;
						head->tsize++;
				 }
				 
				 arrFood[i].y=-1;
				 arrFood[i].x=-1;
				 arrFood[i].type=-1;
				 
				 
				 
				 return 0;
				 
				
			}
		}
	}	
		return 0;	
	
	
}	

int main()
{
	int max_x=0, max_y=0;
	
	setlocale(LC_ALL,""); //Протащить локальные настройки из родительского терминала
	
	snake_t* snake = (snake_t*)malloc(sizeof(snake_t));
	snake_t* snake2 = (snake_t*)malloc(sizeof(snake_t));
    initSnake(snake,START_TAIL_SIZE,10,10);
    initSnake2(snake2,START_TAIL_SIZE,20,20);
    initFood();
    
    initscr();
    keypad(stdscr, TRUE); // Включаем F1, F2, стрелки и т.д.
    raw();                // Отключаем line buffering
    noecho();            // Отключаем echo() режим при вызове getch
    curs_set(FALSE);    //Отключаем курсор
    
    
    start_color();
	init_pair(1, COLOR_GREEN, COLOR_WHITE);
	init_pair(2, COLOR_CYAN, COLOR_MAGENTA);
	init_pair(3, COLOR_RED, COLOR_WHITE);
	init_pair(4, COLOR_GREEN, COLOR_YELLOW);
	init_pair(5, COLOR_RED, COLOR_WHITE);
	init_pair(6, COLOR_WHITE, COLOR_RED);
	
	 
	int level = 0;
	int speed = 100;
	
_ret:

    int key_pressed = displayMenu(level);
    
    if (level==0) 
	 switch(key_pressed)
	 {
		 case '0': break;
		 case '1': level=1; goto _ret; ;
		 case '2': level=2; goto _ret; ;
		 case '3': 
		 free(snake->tail);
         free(snake);
         endwin(); // Завершаем режим curses mod
		 exit(0);
		 default:		  goto _ret; 
	 }
	 
	  if (level==1) 
	 switch(key_pressed)
	 {
		 case '0': speed = 100; level=0; goto _ret; ;
		 case '1': speed = 50; level =0; goto _ret; ;
		 case '9': 
		level=0; goto _ret; 
		default:		   goto _ret; 
	 }
	 
	 if (level==2) 
	 switch(key_pressed)
	 {
		 case '0': ;
		 case '1': ;
		 case '2': ;
		 case '3': ;
		 case '4': ;
		 case '5': 
		 bkgd(COLOR_PAIR(key_pressed-48));
		 
	
		      
		 case '9': 
		 level=0; goto _ret; 
		 default:		  goto _ret; 
	 }
    
    srand(time(NULL)); 
     
    mvprintw(0, 0,"Use arrows for control. Press 'F10' for EXIT");
    timeout(0);    //Отключаем таймаут после нажатия клавиши в цикле
    key_pressed=0;
    int timing = 0;
    while( key_pressed != STOP_GAME )
    {
       
        go(snake, '@');
        goTail(snake, '*');
        
        go(snake2, '#');
        goTail(snake2, '=');
        
        if (isBittenByItself(snake))
        {
			break;
			
		}
		
		 if (isBittenByItself(snake2))
        {
			break;
			
		}
		
		if (isFoodTaken(snake))
		{
			break;
		}
		
		if (isFoodTaken(snake2))
		{
			break;
		}
        
        key_pressed = getch(); // Считываем клавишу
        //mvprintw(1, 1, "%c", key_pressed);
        //mvprintw(2, 1, "%u", key_pressed);
        
        myTimeout(speed);
        //timeout(100); // Задержка при отрисовке
        changeDirection(snake, key_pressed);
        changeDirection(snake2, key_pressed);
        
        timing++;
        //mvprintw(0, 40, " timing: %d   ", timing);
        if (timing > 100)
        {
			 srand(time(NULL)); 

			//Расставляем еду
			int num = (rand() % (3 - 1 + 1)) + 1;
			getmaxyx(stdscr, max_y, max_x); // macro - размер терминала
			int newX = (rand() % (max_x - 0 + 1)) + 0;
			int newY = (rand() % (max_y - 0 + 1)) + 0;
			
			
			
			
			addFood(newX, newY, num);
			
			timing = 0;
		}
		
		foodExpire();
        
    }
    free(snake->tail);
    free(snake);
    endwin(); // Завершаем режим curses mod
    return 0;
}
