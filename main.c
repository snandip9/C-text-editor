#include <curses.h>
#include <menu.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"

#define CTRL_KEY(k) ((k) & 0x1f)



int main(int argc, char ** argv)
 
{	
	char s[500]; // text from the file
	int ch;
	Editor t;

	if (argc != 2)
	{
    printf("Filename missing!\n");
    return 1;
	}


	initEditor(&t);
	FILE *src = openFile(argv[1]);

	fgets(s, sizeof(s), src);
	mvwprintw(t.my_win, 3, 5, "%s", s);
	wrefresh(t.my_win);

	keypad(t.my_win, TRUE);


	while((ch = wgetch(t.my_win)) != CTRL_KEY('q'))
	{	processCursorKey(ch, &t);
		//processSpecialKey(ch, &t);

		wmove(t.my_win, t.cursorY, t.cursorX);
		wrefresh(t.my_win);
	}
	
	fclose(src);
	endwin();
	return 0;

}

