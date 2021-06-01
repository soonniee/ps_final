#include "tetris.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#pragma warning (disable: 4996)
int max_score = 0;
int play_score = 0;
int before_score = 0;
MAP map[MAP_H + 1][MAP_W + 1];
LOC BLOC;
ELOC EBLOC[4];
int score_board = 0;

int speed_score = 0;
int clear_cnt = 0;
void tictoc() {
    if (play_score >= 20 && clear_cnt==0) {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handle, 14);
        cursor_gotoxy(4, 3);
        printf("Clear Blocks : Press c");
    }
    else {
        cursor_gotoxy(4, 3);
        printf("                      ");
    }
    int speed = 300;
    BLOC.Y = BLOC.Y + 1;

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    cursor_gotoxy(4, 0);
    SetConsoleTextAttribute(handle, 12);

    if (clear_cnt == 1) {
        int s = (before_score / 20);

        if (s >= 1) {
            if (speed >= 150) {
                speed = speed - 25 * s;
            }
            Sleep(speed);

        }
        else {
            Sleep(speed);
        }
    }
    else {
        int s = play_score / 20;

        if (s >= 1) {
            if (speed >= 150) {
                speed = speed - 25 * s;
            }
            Sleep(speed);

        }
        else {
            Sleep(speed);
        }
    }

}
int block[7][4][4] = {
    {{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}},
    {{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}},
    {{0,0,0,0},{0,1,0,0},{1,1,1,0},{0,0,0,0}},
    {{0,0,0,0},{0,0,1,0},{0,1,1,0},{0,1,0,0}},
    {{0,0,0,0},{0,1,1,1},{0,1,0,0},{0,0,0,0}},
    {{0,0,0,0},{0,1,0,0},{0,1,1,1},{0,0,0,0}},
    {{0,0,0,0},{0,1,0,0},{0,1,1,0},{0,0,1,0}},

};
int each_block[4][4];
int rotate_block[4][4];
int block_coord[4][2];
void each_block_loc(int block[4][4]) {
    int cnt = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (block[i][j] == 1) {
                EBLOC[cnt].r = i;
                EBLOC[cnt].c = j;
                cnt++;
            }
        }
    }
}
void map_init() {
    for (int i = 0; i <= MAP_H; i++) {
        for (int j = 0; j <= MAP_W; j++) {
            if (i == 0 || j == 0 || i == MAP_H || j == MAP_W) {
                map[i][j].state = WALL;
            }
            else {
                map[i][j].state = EMPTY;
            }
        }
    }
}
void score_text() {

    if (play_score > 0) {
        FILE* fp;
        char name[50];
        if ((fp = fopen("score.txt", "r")) == NULL) {
            /*max_score = play_score;*/
            FILE* fp1;
            fp1 = fopen("score.txt", "w");
            HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(handle, 11);
            cursor_gotoxy(6, 10);
            printf("You are the First Player!");
            cursor_gotoxy(6, 12);
            printf("-----------------");
            cursor_gotoxy(6, 14);
            printf("Input Your Name : ");
            cursor_gotoxy(6, 16);
            printf("-----------------");
            cursor_gotoxy(26, 14);
            CONSOLE_CURSOR_INFO info;
            info.dwSize = 1;
            info.bVisible = TRUE;
            SetConsoleCursorInfo(handle, &info);
            fgets(name, sizeof(name), stdin);
            fprintf(fp1, "%d\n", play_score);
            fputs(name, fp1);
            fclose(fp1);
            play_score = 0;
            before_score = 0;
            clear_cnt = 0;

        }
        else {
            FILE* fp1;
            fp1 = fopen("score.txt", "r");
            fscanf(fp1, "%d\n", &max_score);
            if (play_score > max_score) {
                HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(handle, 11);
                /*max_score = play_score;*/
                cursor_gotoxy(6, 10);
                printf("You are the TOP Player!");
                cursor_gotoxy(6, 12);
                printf("-----------------");
                cursor_gotoxy(6, 14);
                printf("Input Your Name : ");
                cursor_gotoxy(6, 16);
                printf("-----------------");
                cursor_gotoxy(26, 14);
                CONSOLE_CURSOR_INFO info;
                info.dwSize = 1;
                info.bVisible = TRUE;
                SetConsoleCursorInfo(handle, &info);
                fgets(name, sizeof(name), stdin);
                fclose(fp1);
                FILE* fp2;
                fp2 = fopen("score.txt", "w");
                fprintf(fp2, "%d\n", play_score);
                fputs(name, fp2);
                fclose(fp2);
                play_score = 0;
                before_score = 0;
                clear_cnt = 0;

            }
            play_score = 0;
            before_score = 0;
            clear_cnt = 0;

            fclose(fp1);
        }
    }

}
void clear_map() {
    if (clear_cnt == 0) {
        if (play_score >= 20) {
            before_score = play_score;
            play_score = 0;

            for (int i = 1; i < MAP_H; i++) {
                for (int j = 1; j < MAP_W; j++) {
                    map[i][j].state = EMPTY;
                }
            }
            clear_cnt += 1;
        }
    }

}
 void block_init() {
     BLOC.X = 8;
     BLOC.Y = 0;
 }
void cursor_gotoxy(short x, short y) {
    COORD C = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), C);
}
char start_view() {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    cursor_gotoxy(1, 1);
    SetConsoleTextAttribute(handle, 11);
    printf("================= Welcome to TETRIS !! =================");
    SetConsoleTextAttribute(handle, 13);
    cursor_gotoxy(2, 3);
    printf("< Top Player >");
    FILE* fp1;
    if ((fp1=fopen("score.txt","r"))==NULL) {
        cursor_gotoxy(2, 5);
        printf("Score : 0");
    }
    else {
        char name[50];
        FILE* fp = fopen("score.txt", "r");
        fscanf(fp, "%d\n", &score_board);
        fgets(name, sizeof(name), fp);
        fclose(fp);
        name[strlen(name) - 1] = '\0';
        cursor_gotoxy(2, 5);
        printf("Name : %s", name);
        cursor_gotoxy(2, 7);
        printf("Score: %d", score_board);
    }

    SetConsoleTextAttribute(handle, 14);
    cursor_gotoxy(2, 10);
    printf("<Key Instructions>");
    cursor_gotoxy(2, 12);
    printf("Move the block to the Left : Left Arrow ");
    cursor_gotoxy(2, 14);
    printf("Move the block to the Right : Right Arrow ");
    cursor_gotoxy(2, 16);
    printf("Rotate the block 90 degress clockwise : Up Arrow ");
    cursor_gotoxy(2, 18);
    printf("Move the block to Down directly: Space ");
    cursor_gotoxy(8, 22);
    SetConsoleTextAttribute(handle, 12);
    printf("===== Press 's' to start the game ===== ");
    char input;
    while (1) {
        input = _getch();

        if (input == 's' || input == 'S') break;
    }
    return input;

}
void cursor_hide() {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 1;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(handle, &info);
}
void start_count() {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i <= 3; i++) {
        cursor_gotoxy(4, 1);
        SetConsoleTextAttribute(handle, 12);
        printf("START : %d sec", 3 - i);
        Sleep(1000);
    }
}
int get_left() {
    int left = 4;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (each_block[i][j] == 1) {
                if (left > j) left = j;
            }
        }
    }
    return left;
}
int get_right() {
    int right = -1;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (each_block[i][j] == 1) {
                if (right < j) right = j;
            }
        }
    }
    return right;
}
int get_bottom() {
    int bottom = 4;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (each_block[i][j] == 1) {
                if (bottom > i) bottom = i;
            }
        }
    }
    return bottom;
}
void move_left() {
    each_block_loc(each_block);
    int left = get_left();
    int check = 0;
    if (left + BLOC.X / 2 >= 2) {
        for (int i = 0; i < 4; i++) {
            int col = BLOC.X / 2 + EBLOC[i].c - 1;
            int row = BLOC.Y + EBLOC[i].r;

            if (map[row][col].state == BLOCK || col == 0 || col==MAP_W || row ==MAP_H) {
                check = 1;
                break;
            }
        }
        if (check == 0) {
            BLOC.X = BLOC.X - 2;
        }
    }
}
void move_right() {
    each_block_loc(each_block);
    int right = get_right();
    int check = 0;
    if (right + BLOC.X / 2 <= 8) {
        for (int i = 0; i < 4; i++) {
            int col = BLOC.X / 2 + EBLOC[i].c + 1;
            int row = BLOC.Y + EBLOC[i].r;

            if (map[row][col].state == BLOCK || col == 0 || col == MAP_W || row == MAP_H) {
                check = 1;
                break;
            }
        }
        if (check == 0) {
            BLOC.X = BLOC.X + 2;
        }
    }
}
void rotation() {
    int check = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (each_block[i][j] == 1) {
                rotate_block[j][3 - i] = each_block[i][j];
            }
        }
    }

    each_block_loc(rotate_block);

    while (1) {
        for (int i = 3; i >= 0; i--) {
            int col = BLOC.X / 2 + EBLOC[i].c;
            int row = BLOC.Y + EBLOC[i].r;

            if (map[row][col].state == BLOCK || row == MAP_H) {
                check = 1;
                BLOC.Y = BLOC.Y - 1;
                break;
            }

            else if (col == 0) {
                check = 1;
                BLOC.X = BLOC.X + 2;
                break;
            }
            else if (col == MAP_W) {
                check = 1;
                BLOC.X = BLOC.X - 2;
                break;
            }
            else check = 0;
        }
        if (check == 0) {

            break;
        }

    }
    copy_block(each_block, rotate_block);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            rotate_block[i][j] = 0;
        }
    }

}


void move_down() {
    each_block_loc(each_block);
    int check = 0;
    int row, col;
    while (1) {
        for (int i = 0; i < 4; i++) {
            col = BLOC.X / 2 + EBLOC[i].c;
            row = BLOC.Y + EBLOC[i].r+1;

            if (map[row][col].state == BLOCK || row== MAP_H) {
                check = 1;

                break;
            }
        }
        if (check == 1) {

            break;
        }
        else BLOC.Y = BLOC.Y + 1;

    }
}
void wall_view() {

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, 11);
    for (int i = 0; i <= MAP_H; i++) {
        for (int j = 0; j <= MAP_W; j++) {
            cursor_gotoxy(j * 2 + INIT_X, i + INIT_Y);
            if (i == 0 || j == 0 || i == MAP_H || j == MAP_W) {
                printf("*");
            }
        }
        printf("\n");
    }
    SetConsoleTextAttribute(handle, 12);

    cursor_gotoxy(MAP_W * 2 + 10, 7);
    printf("Playing Score : %d     ", play_score);
    if (clear_cnt == 1) {
        if ((before_score / 20) >= 1) {
            SetConsoleTextAttribute(handle, 15);
            cursor_gotoxy(17, 1);

            printf("SPEED UP X%d", (before_score / 20) +1);
        }
    }
    else {
        if (play_score / 20 >= 1) {
            SetConsoleTextAttribute(handle, 14);
            cursor_gotoxy(17, 1);

            printf("SPEED UP X%d", (play_score / 20) + 1);
        }
    }

}
void block_view() {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, 12);
    for (int i = 1; i < MAP_H; i++) {
        for (int j = 1; j < MAP_W; j++) {
            if (map[i][j].state == BLOCK) {
                cursor_gotoxy(j * 2 + INIT_X, i + INIT_Y);
                printf("*");
            }
            else {
                cursor_gotoxy(j * 2 + INIT_X, i + INIT_Y);
                printf(" ");
            }

        }
        printf("\n");
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cursor_gotoxy(BLOC.X + j * 2 + INIT_X, BLOC.Y + i + INIT_Y);
            if (each_block[i][j] == 1) {
                SetConsoleTextAttribute(handle, 12);
                printf("*");
            }

        }
        printf("\n");
    }
}
int check_line() {
    int check = 0;
    int row, col;
    each_block_loc(each_block);
    for (int i = 0; i < 4; i++) {
        col = BLOC.X / 2 + EBLOC[i].c;
        row = BLOC.Y + EBLOC[i].r;
        if (row == 0) {
            BLOC.Y += 1;
        }
    }
    for (int i = 0; i < 4; i++) {
         col = BLOC.X / 2 + EBLOC[i].c;
         row = BLOC.Y + EBLOC[i].r +1;

         if (map[row][col].state == BLOCK || row == MAP_H) {
             check = 1;
             break;
         }
    }
    if (check == 1) {
        for (int i = 0; i < 4; i++) {
            int co = BLOC.X / 2 + EBLOC[i].c;
            int ro = BLOC.Y + EBLOC[i].r;
            map[ro][co].state = BLOCK;

        }
        return 1;
    }
    else return 2;
}
void remove_line() {

    int flag = 0;
    int cnt = 0;
    int remove = 0;
    int rem_start = 0;

        for (int i = MAP_H -1; i > 0; i--) {
            cnt = 0;
            for (int j = 1; j < MAP_W; j++) {
                if (map[i][j].state == EMPTY) {

                    break;
                }
                else cnt += 1;
            }
            if (cnt == MAP_W - 1) {
                rem_start = i;
                remove += 1;
                flag = 1;


            }
            else flag = 0;
            if (flag == 0 && remove > 0) break;
        }
        if (remove == 1) {
            play_score += 5;
            before_score += 5;
        }
        else if (remove > 1) {
            play_score += remove * 2 * 5;
            before_score += remove * 2 * 5;
        }


            wall_view();
            cursor_gotoxy(4, 31);

            for (int i = rem_start + remove - 1; i > remove; i--) {
                for (int j = 1; j < MAP_W; j++) {
                    map[i][j].state = map[i-remove][j].state;
                }
            }
            for (int i = remove; i > 0; i--) {
                for (int j = 1; j < MAP_W; j++) {
                    map[i][j].state = EMPTY;
                }
            }
            HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(handle, 12);
            for (int i = 1; i < MAP_H; i++) {
                for (int j = 1; j < MAP_W; j++) {
                    if (map[i][j].state == BLOCK) {
                        cursor_gotoxy(j * 2 + INIT_X, i + INIT_Y);
                        printf("*");
                    }

                }
                printf("\n");
            }
        }




int game_end() {
    each_block_loc(each_block);
    int check = 0;
    for (int i = 0; i < 4; i++) {
        int col = BLOC.X / 2 + EBLOC[i].c;
        int row = BLOC.Y + EBLOC[i].r;
        if (map[row + 1][col].state == BLOCK) {
            check = 1;
            break;
        }
    }
    if (check == 0) return 0;
    else return 1;
}
int map_view() {

    cursor_gotoxy(4, 1);
    printf("PLAYING....   ");
    wall_view();
    int check = check_line();
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, 12);


    if (check == 1) {
        remove_line();
        cursor_gotoxy(4, 30);

        random_block();
        block_init();
        block_view();

        int end = game_end();
        if (end == 1) {
            cursor_gotoxy(4, 1);
            SetConsoleTextAttribute(handle, 15);
            printf("GAME END!!                 ");
            return END;
        }
    }
    else {
        cursor_gotoxy(0, 30);
        block_view();
    }
}
void copy_block(int des[4][4], int src[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            des[i][j] = src[i][j];
        }
    }
}
void random_block() {
    srand((unsigned int)(time(NULL)));
    int num = rand() % 7;
    switch (num) {
    case 0:
        copy_block(each_block, block[0]);
        break;
    case 1:
        copy_block(each_block, block[1]);
        break;
    case 2:
        copy_block(each_block, block[2]);
        break;
    case 3:
        copy_block(each_block, block[3]);
        break;
    case 4:
        copy_block(each_block, block[4]);
        break;
    case 5:
        copy_block(each_block, block[5]);
        break;
    case 6:
        copy_block(each_block, block[6]);
        break;
    }
}
