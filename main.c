#include <curses.h>
#include <menu.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#include <menu.h>
#include <panel.h>

#define CTRL_KEY(k) ((k) & 0x1f)


// this is what each line of the txt file will be saved as 

typedef struct line {
  int size;
  char *chars;
} line;

//instead of looping everything in main fucntion we can just define the editor from the start 

struct editor {

	int size;

	char* srcPtr = (int*)malloc(size * sizeof(int));

};


int main(int argc, char ** argv)

	//initialising variables 
{	
	FILE *src;
	char s[500]; // text from the file
	int row, col;

	int cursorX = 5;
	int cursorY = 3;
	int ch;

	WINDOW *my_win;

	// checking if the file exists 

	if (argc != 2) {
		printf("Filename missing!\n");
		exit(EXIT_FAILURE);}

	src = fopen (argv[1], "r");

	if (src == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE);}

	// initialising screen and window and the settings for them 

	initscr();
	getmaxyx(stdscr,row,col);	
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	raw();	
	my_win=newwin(row, col, 0, 0);

	// getting the text from the file and presenting it on the screen 

	fgets(s, sizeof(s), src);
	mvwprintw(my_win, 3, 5, "%s", s);
	wrefresh(my_win);

	keypad(my_win, TRUE);


	// where all commands are performed 


	while((ch = wgetch(my_win)) != CTRL_KEY('q'))
	{	switch(ch)
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


	fclose(src);
	endwin();
	return 0;

}