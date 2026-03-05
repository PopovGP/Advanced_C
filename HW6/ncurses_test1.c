#include <ncurses.h>
#include <locale.h>

/* Строка в параметрах Geany:
 * gcc -Wall -o "%e" "%f" -lncurses -DNCURSES_STATIC -D_DEFAULT_SOURCE -D_XOPEN_SOURCE=600 
 */
 
/* Makefile

CC     = gcc
CFLAGS = -D_DEFAULT_SOURCE -D_XOPEN_SOURCE=600 
CLIBS  = -lncursesw

all: colors.run
	./$^

%.run: %.c
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)
	
*/

int main()
{
	
	setlocale(LC_ALL,""); //Протащить локальные настройки из родительского терминала
	//Инициализация
	initscr(); 
	
	noecho(); //не выводить вводимый символ
	curs_set(0); //убираем курсор
	
	
	//Начнем с цветом работу:
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_WHITE);
	init_pair(2, COLOR_CYAN, COLOR_MAGENTA);
	init_pair(3, COLOR_RED, COLOR_WHITE);
	init_pair(4, COLOR_GREEN, COLOR_YELLOW);
	init_pair(5, COLOR_RED, COLOR_WHITE);
	init_pair(6, COLOR_WHITE, COLOR_RED);
	
	
	box(stdscr, 0, 0);
	
	move(10,5);
	
	printw("Привет!");
	getch();
	
	clear();
	
	move(15,10);
	
	printw("Пока!");
	getch();
	
	
	WINDOW* w = newwin(5,13, 2, 3); //Размер окна 
	if (!w) perror("Невозможно создать окно!\n");
	
	box(w, 0, 0);
	wrefresh(w);
	wgetch(w);

	cchar_t vert_char1, horiz_char1, tl_corner1, tr_corner1, bl_corner1, br_corner1;
	
	//Unicode box set: https://en.wikipedia.org/wiki/Box-drawing_characters
	setcchar(&vert_char1, L"\u2503", WA_NORMAL, 0, NULL);
	setcchar(&tl_corner1, L"\u256d", WA_NORMAL, 0, NULL);
	setcchar(&tr_corner1, L"\u256e", WA_NORMAL, 0, NULL);
	setcchar(&horiz_char1,L"\u2501", WA_NORMAL, 0, NULL);
	setcchar(&br_corner1, L"\u256f", WA_NORMAL, 0, NULL);
	setcchar(&bl_corner1, L"\u2570", WA_NORMAL, 0, NULL);
	
	wborder_set(w, &vert_char1, &vert_char1, //left, right
				   &horiz_char1, &horiz_char1, //top, bottom
				   &tl_corner1, &tr_corner1, //top-right cornet, top-left corner
				   &bl_corner1, &br_corner1); //bottom-left corner, bottom-right corner
	wmove(w, 2, 2);
	waddstr(w, "Привет!!!");
	wrefresh(w);
	wgetch(w);
	
	
	wmove(w, 3, 2);
	waddstr(w, "Как дела?");
	wrefresh(w);
	wgetch(w);
	
	wmove(w, 4, 2);
	waddstr(w, "Нормуль!");
	wrefresh(w);
	wgetch(w);
	
	delwin(w);
	
	//Эксперименты с цветами
	
	WINDOW* u = newwin(20, 20, 5, 8); //Размер окна 
	if (!u) perror("Невозможно создать окно 2!\n");
	for (int i = 1; i<7; i++)
	{
	wbkgd(u, COLOR_PAIR(i));
	
	box(u, 0, 0);
	wrefresh(u);
	wgetch(u);
	
	//delwin(u);
	}
	
	wbkgd(u, COLOR_PAIR(1));
	wmove(w, 6, 6);
	waddstr(u, "Норм!");
	//wrefresh(w);
	wgetch(u);
	
	delwin(u);
	//Деинициализация
	int r_end = endwin();
	return (r_end == ERR);
}
