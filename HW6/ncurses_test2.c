#include <ncurses.h>

int main() {
    initscr();            // Start ncurses mode
    cbreak();             // Line buffering disabled
    keypad(stdscr, TRUE); // Enable special keys
    noecho();             // Don't echo input

    // Set a simple character 'H' at the current position (0,0 initially)
    addch('H'); 

    // Move to position (5, 10) and add the character '!'
    mvaddch(5, 10, '!'); 

    // Combine a character with an attribute (e.g., bold)
    addch('B' | A_BOLD);

    refresh();            // Refresh the screen to show output
    getch();              // Wait for user input
    endwin();             // End ncurses mode

    return 0;
}
