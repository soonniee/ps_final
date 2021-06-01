#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include <conio.h>
#include<time.h>
#include "tetris.h"
int main() {
	system("mode con cols=60 lines=50 | title TETRIS");

	while (1) {
		cursor_hide();

		char input = start_view();
		if (input == 's' || input == 'S') {
			system("cls");
			random_block();
			block_init();
			map_init();
			map_view();
			start_count();

		}
		int time = 0;
		while (1) {

			while (_kbhit()) {

				unsigned char key = _getch();
				if (key == 224) {
					key = _getch();
					if (key == 75) {
						move_left();

					}
					else if (key == 77) {
						move_right();

					}
					else if (key == 72) {
						rotation();


					}


				}
				else if (key == 32) {
					move_down();
				}
				else if (key == 'c') {
					clear_map();
				}


			}


			int end_check = map_view();
			if (end_check == END) {
				Sleep(2000);
				system("cls");
				Sleep(2000);
				score_text();
				system("cls");

				break;
			}
			else {
				time += 1;
				tictoc();

			}
		}
		Sleep(2000);
	}

	Sleep(2000);

	return 0;
}
