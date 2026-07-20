#ifndef UTILS_H
#define UTILS_H

#include <curses.h>

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
} Editor;

void initEditor(Editor *t);
FILE *openFile(char *filename);
void processCursorKey(int ch, Editor *t);

#endif