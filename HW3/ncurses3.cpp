#ifdef __MINGW32__
#include <ncurses/ncurses.h>
#else
#include <ncurses.h>
#endif
#include <iostream>
int main() {
initscr();
// Init the Library.
noecho();
// Do not echo user input.
cbreak(); // Do not buffer user input, retain Ctrl-Z & Ctrl-C functions.
//raw(); // Do nut buffer any user input. Present all input to program.
keypad (stdscr, TRUE); // Enable extended character (e.g. F-keys, numpad) input.
curs_set(1); // Change cursor appearance. O invisible, 1 normal, 2 strong.
if (has_colors()== FALSE) {
endwin();
std::cout << "Your terminal doesn't support colours." << std::endl;
return 1;
}
start_color();
init_pair(1, COLOR_WHITE, COLOR_BLUE); // fore & background colours.
attron (COLOR_PAIR(1));
int y, x;
getmaxyx(stdscr, y, x);
y = y * 0.5;
x = (x * 0.5) - 6;
mvwprintw(stdscr, y, x, "Hello World!");
mvwprintw(stdscr, 2, 2, "Hello World!");
refresh();
attroff (COLOR_PAIR(1));
getch();
// Wait for key press before exiting.
endwin(); // Main ncurses clean-up.
return 0;
}
