#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <string.h>
#include <ctype.h>

int nanosleep(const struct timespec *req, struct timespec *rem);
void print_hero(int y, int x, int row, int column, const char player[row][column]);
void print_child(int y, int x, int row, int column, const char player[row][column], const char player1[row][column], int lines, int cols, char world[lines][cols], bool happy);
void print_shot(int y, int x, int row, int column, const char player[row][column], int COL);
void print_empty(int y, int x, int row, int column, char dir);
void print_empty_direction(int y, int x, int row, int column, char dir);
void jump(int y, int x, int row, int column, const char player[row][column], int dir, int lines, int cols, char world[lines][cols], int mas[2], int start_col, int col);
void map1(int start_row, int start_col, int lines, int cols, char world[lines][cols]);
void map2(int start_row, int start_col, int lines, int cols, char world[lines][cols]);
void map3(int start_row, int start_col, int lines, int cols, char world[lines][cols]);
bool detect(int y, int x, int row, int column, int lines, int cols, const char world[lines][cols], char dir);
int falling(int y, int x, int row, int column, const char player[row][column], int lines, int cols, const char world[lines][cols], int start_row);
void print_shots(int start_col, int start_row, int lines, int cols, char world[lines][cols]);
bool check_shot(int y1, int x1, int row1, int column1, int y2, int x2, int row2, int column2);
void boundaries_func(int lines, int cols, int mas[4]);
void all();

int menu(int y, int rows, int columns, char text[rows][columns], int a, int color);
void option(char mas[], int columns, int y, int x, int choose, int guess, int color);
void draw_logo(int rows, int columns, const char logo[rows][columns], int target , bool col);
int levels();
int winner();
int loser();
void instruction();
void color_logo(int y, int center, int rows, int columns,const char logo[rows][columns], int index );
