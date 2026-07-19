#include <curses.h>
#include <menu.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct line {
  int size;
  char *chars;
} line;

//instead of looping everything in main fucntion we can just define the editor from the start 

typedef struct Editor {

	int row, col;

	int cursorX = 5, cursorY = 3;

	int numLines;
	line *lines;

	WINDOW *my_win;

}Editor;

void procesCursorkey (int ch) {

	switch(ch)
	{	case KEY_LEFT:
		    cursorX--;
		    break;

		case KEY_RIGHT:
		    cursorX++;
		    break;

		case KEY_UP:
		    cursorY--;
		    break;

		case KEY_DOWN:
		    cursorY++;
		    break;
	}

	if (cursorX < 0)
	    cursorX = 0;
	if (cursorY < 0)
	    cursorY = 0;

	if (cursorX > getmaxx(my_win) - 1)
	    cursorX = getmaxx(my_win) - 1;
	if (cursorY > getmaxy(my_win) - 1)
	    cursorY = getmaxy(my_win) - 1;

	wmove(my_win, cursorY, cursorX);
	wrefresh(my_win);
}

void procesSpecialKeys (int ch) {

	switch(ch)
	{	case CTRL_KEY('s'):
		    
		    break;

		case CTRL_KEY('x'):
		    break;

		case CTRL_KEY(''):
		    break;

		case CTRL_KEY('q'):
		    break;
	}

	wmove(my_win, cursorY, cursorX);
	wrefresh(my_win);
}

void initEditor(Editor editor){

	// initialise the editor 

	initscr();
	getmaxyx(stdscr,row,col);	
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	raw();	
	my_win=newwin(row, col, 0, 0);


}
