#include <curses.h>
#include <menu.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#include <menu.h>
#include <panel.h>

#define CTRL_KEY(k) ((k) & 0x1f)


int main(int argc, char ** argv)
{	
	FILE *src;
	char s[500];
	int cursorX = 5;
	int cursorY = 3;
	int ch;
	WINDOW *my_win;

	if (argc != 2) {
		printf("Filename missing!\n");
		exit(EXIT_FAILURE);}

	src = fopen (argv[1], "r");

	if (src == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE);}

	initscr();
	cbreak();
	noecho();
	my_win=newwin(100, 100, 0, 0);

	fgets(s, sizeof(s), src);
	mvwprintw(my_win, 3, 5, "%s", s);
	wrefresh(my_win);

	keypad(my_win, TRUE);


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

		wmove(my_win, cursorY, cursorX);
		wrefresh(my_win);
	}


	fclose(src);
	endwin();
	return 0;

}