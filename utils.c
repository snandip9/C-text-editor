#include <curses.h>
#include <menu.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"

typedef struct line {
  int size;
  char *chars;
} line;


typedef struct Editor {

	int row;
	int col;

	int cursorX; 
	int cursorY;

	int numLines;
	line *lines;

	WINDOW *my_win;

}Editor;

//need to pass in struct as a pointer in this function 

void initEditor(Editor* t){

	t->row = 3;
	t->col = 5;

	t->cursorX = 5;
	t->cursorY = 3;

	t->numLines;
	line *lines;

	WINDOW *my_win; 

	initscr();
	getmaxyx(stdscr,t->row,t->col);	
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	raw();	
	t->my_win=newwin(t->row, t->col, 0, 0);

}

FILE* openFile(char * filename){

	FILE* src;

	src = fopen (filename, "r");

	if (src == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE);}

	return src;
}

void processCursorKey (int ch, Editor* t) {

	switch(ch)
	{	case KEY_LEFT:
		    t->cursorX--;
		    break;

		case KEY_RIGHT:
		    t->cursorX++;
		    break;

		case KEY_UP:
		    t->cursorY--;
		    break;

		case KEY_DOWN:
		    t->cursorY++;
		    break;
	}

	if (t->cursorX < 0)
	    t->cursorX = 0;
	if (t->cursorY < 0)
	    t->cursorY = 0;

	if (t->cursorX > getmaxx(t->my_win) - 1)
	    t->cursorX = getmaxx(t->my_win) - 1;
	if (t->cursorY > getmaxy(t->my_win) - 1)
	    t->cursorY = getmaxy(t->my_win) - 1;

	wmove(t->my_win, t->cursorY, t->cursorX);
	wrefresh(t->my_win);
}

/*
void procesSpecialKeys (int ch, Editor* t) {

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

	wmove(t->my_win, t->cursorY, t->cursorX);
	wrefresh(t->my_win);
}
*/
