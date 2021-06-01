//#pragma once
#ifndef TETRIS_H_
#define TETRIS_H_
#define MAP_H 20
#define MAP_W 10
#define EMPTY 0
#define BLOCK 1
#define WALL 2
#define INIT_X 4
#define INIT_Y 4
#define END 30

typedef struct Map {
	int state;
}MAP;
typedef struct Block_Loc {
	int X;
	int Y;
}LOC;

typedef struct EachBLock_Loc {
	int r;
	int c;
}ELOC;
void random_block();
void cursor_gotoxy(short x, short y);
void cursor_hide();
char start_view();
void start_count();
void wall_view();
void map_init();
void block_init();
void score_text();
void block_view();
void move_left();
void move_right();
void move_down();
void rotation();
int map_view();
int check_line();
void remove_line();
void clear_map();
void tictoc();
int game_end();
void each_block_loc(int block[4][4]);
void copy_block(int des[4][4], int src[4][4]);
#endif
