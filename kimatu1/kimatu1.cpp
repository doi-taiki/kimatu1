#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <windows.h>
#include <mmsystem.h>
#include <time.h>
#include <vector>
#include "game.h"
#include "SL.h"
#define BUFFSIZE 1024

#pragma comment(lib, "winmm.lib")
#define NUMTHREAD 2

#define USEMUTEX

HANDLE threadMutex;

stage* st1 = (stage*)malloc(sizeof(stage));
stage* new_stage = (stage*)malloc(sizeof(stage));
character c1;
command* cd= (command*)malloc(sizeof(command));

void processA(stage* a) {
	while (cd->prev_state!=100){
		noecho();
		cbreak();
		keypad(stdscr, TRUE);
		cd->key1 = getch();
#ifdef USEMUTEX
		WaitForSingleObject(threadMutex, INFINITE);
#endif
		cd->key = cd->key1;
#ifdef USEMUTEX
		ReleaseMutex(threadMutex);
#endif
	}
}
void processB() {
	cd->load_mode = false;
	while (cd->mode == 0) {
		if (cd->load_mode == false) {
			start_color();
			init_pair(0, COLOR_WHITE, COLOR_BLACK);	// 色1 は黒地に白文字
			mvaddstr(10, 50, "作る");
			mvaddstr(15, 50, "遊ぶ");
			mvaddstr(20, 50, "操作説明");
			if (cd->mode_select == 0) {
				mvaddstr(10, 70, "<-");
				mvaddstr(15, 70, "  ");
				mvaddstr(20, 70, "  ");
			}
			else if (cd->mode_select == 1) {
				mvaddstr(10, 70, "  ");
				mvaddstr(15, 70, "<-");
				mvaddstr(20, 70, "  ");
			}
			else if (cd->mode_select == 2) {
				mvaddstr(10, 70, "  ");
				mvaddstr(15, 70, "  ");
				mvaddstr(20, 70, "<-");
			}
#ifdef USEMUTEX
			WaitForSingleObject(threadMutex, INFINITE);
#endif
			if (cd->key == KEY_UP  ) {
				if (cd->mode_select > 0) {
					cd->mode_select = (cd->mode_select - 1) % 3;
				}
				else {
					cd->mode_select = cd->mode_select + 2;
				}
			}
			else if(cd->key == KEY_DOWN){
				cd->mode_select = (cd->mode_select + 1) % 3;
			}
			else if (cd->key == 'a') {
				if (cd->mode_select == 0) {
					cd->prev_state = 100;
					cd->mode = cd->mode_select + 1;
				}
				else if(cd->mode_select == 1){
					cd->mode_select = 0;
					cd->load_mode = true;
					erase();
				}
				else {
					cd->prev_state = 100;
					cd->mode = cd->mode_select + 1;
				}
			}
			cd->key = 0;
#ifdef USEMUTEX
			ReleaseMutex(threadMutex);
#endif
			// 画面を更新
			refresh();
		}
		else {
			mvaddstr(5, 50, "ロードするセーブを選んでください");
			mvaddstr(10, 57, "セーブ１");
			mvaddstr(15, 57, "セーブ２");
			mvaddstr(20, 57, "セーブ３");
			mvaddstr(23, 59, "戻る");
			if (cd->mode_select == 0) {
				mvaddstr(10, 65, "<-");
				mvaddstr(15, 65, "  ");
				mvaddstr(20, 65, "  ");
				mvaddstr(23, 64, "  ");
			}
			else if (cd->mode_select == 1) {
				mvaddstr(10, 65, "  ");
				mvaddstr(15, 65, "<-");
				mvaddstr(20, 65, "  ");
				mvaddstr(23, 64, "  ");
			}
			else if (cd->mode_select == 2) {
				mvaddstr(10, 65, "  ");
				mvaddstr(15, 65, "  ");
				mvaddstr(20, 65, "<-");
				mvaddstr(23, 64, "  ");
			}
			else if (cd->mode_select == 3) {
				mvaddstr(10, 65, "  ");
				mvaddstr(15, 65, "  ");
				mvaddstr(20, 65, "  ");
				mvaddstr(23, 64, "<-");
			}
#ifdef USEMUTEX
			WaitForSingleObject(threadMutex, INFINITE);
#endif
			if (cd->key == KEY_UP) {
				if (cd->mode_select > 0) {
					cd->mode_select = (cd->mode_select - 1) % 4;
				}
				else {
					cd->mode_select = cd->mode_select + 3;
				}
			}
			else if (cd->key == KEY_DOWN) {
				cd->mode_select = (cd->mode_select + 1) % 4;
			}
			else if (cd->key == 'a') {
				if (cd->mode_select != 3) {
					load_map(cd->mode_select, st1->map);
					cd->mode_select=0;
					cd->mode = 2;
					cd->load_mode = false;
					cd->prev_state = 100;
				}
				else {
					erase();
					cd->load_mode = false;
					cd->mode_select = 0;
				}
			}
			cd->key = 0;
#ifdef USEMUTEX
			ReleaseMutex(threadMutex);
#endif
			// 画面を更新
			refresh();
		}
	}
}

void processC(stage* a) {
	while (cd->prev_state!=100) {
		initscr();
		make_stage(a);
		init_pair(0, COLOR_WHITE, COLOR_BLACK);	// 色1 は黒地に白文字
		mvprintw(1, 100, "コイン×%d", c1.coin);
#ifdef USEMUTEX
		WaitForSingleObject(threadMutex, INFINITE);
#endif
		cd->prev_state = key_operation(cd->key, cd->prev_state, &c1, a);
		cd->key = 0;
#ifdef USEMUTEX
		ReleaseMutex(threadMutex);
#endif
		// 画面を更新
		refresh();
	}
}
void processD(stage* a) {
	cd->save_mode = false;
	new_stage->goal_mode = false;
	int i,j;
	char input[BUFFSIZE] = { 0 };
	a->x = 0;
	a->y = 0;
	for (i = 0; i < 100; i++) {
		for (j = 0; j < 10; j++) {
			a->map[i][j] = 0;
		}
	}
	a->map[80][0] = 11;
	for (i = 1; i < 6; i++) {
		a->map[80][i] = 10;
	}
	a->map[80][6] = 12;
	init_map(new_stage);
	while (cd->prev_state!=100) {
		if (cd->save_mode == TRUE) {
			start_color();
			init_pair(0, COLOR_WHITE, COLOR_BLACK);	// 色1 は黒地に白文字
			mvaddstr(5, 50, "どこにセーブしますか？");
			mvaddstr(10, 57, "セーブ１");
			mvaddstr(15, 57, "セーブ２");
			mvaddstr(20, 57, "セーブ３");
			mvaddstr(23, 59, "戻る");
			if (cd->mode_select == 0) {
				mvaddstr(10, 65, "<-");
				mvaddstr(15, 65, "  ");
				mvaddstr(20, 65, "  ");
				mvaddstr(23, 64, "  ");
			}
			else if (cd->mode_select == 1) {
				mvaddstr(10, 65, "  ");
				mvaddstr(15, 65, "<-");
				mvaddstr(20, 65, "  ");
				mvaddstr(23, 64, "  ");
			}
			else if (cd->mode_select == 2) {
				mvaddstr(10, 65, "  ");
				mvaddstr(15, 65, "  ");
				mvaddstr(20, 65, "<-");
				mvaddstr(23, 64, "  ");
			}
			else if (cd->mode_select == 3) {
				mvaddstr(10, 65, "  ");
				mvaddstr(15, 65, "  ");
				mvaddstr(20, 65, "  ");
				mvaddstr(23, 64, "<-");
			}
#ifdef USEMUTEX
			WaitForSingleObject(threadMutex, INFINITE);
#endif
			if (cd->key == KEY_UP ) {
				if (cd->mode_select == 0) {
					cd->mode_select = 3;
				}
				else {
					cd->mode_select = (cd->mode_select - 1) % 4;
				}
			}else if( cd->key == KEY_DOWN) {
				cd->mode_select = (cd->mode_select + 1) % 4;
			}
			else if (cd->key == 'a') {
				if (cd->mode_select != 3) {
					endwin();
					printf("コース名を入力してください。(.等の使用は不可)\n");
					while (true) {
						scanf_s("%s", input, BUFFSIZE);
						if (save_map(cd->mode_select,input, new_stage->map) == true) {
							erase();
							cd->prev_state = 100;
							break;
						}
					}
				}
				else {
					erase();
					cd->save_mode = false;
					init_map(new_stage);
				}
			}
			cd->key = 0;
#ifdef USEMUTEX
			ReleaseMutex(threadMutex);
#endif
			// 画面を更新
			refresh();
		}
		else {
			start_color();
			init_pair(9, COLOR_WHITE, COLOR_WHITE);	// 色1 は白地に白文字
			attrset(COLOR_PAIR(9));			// 色1 を使う
			for (i = 0; i < 102; i++) {
				for (j = 0; j < 12; j++) {
					if (i == 0 || i == 101 || j == 0 || j == 11) {
						mvaddstr(9 + j, 9 + i, " ");
					}
				}
			}
			attrset(COLOR_PAIR(1));			// 色1 を使う
			mvaddstr(3, 10, " ");
			attrset(COLOR_PAIR(0));			// 色1 を使う
			mvaddstr(3, 11, "…レンガブロック");
			attrset(COLOR_PAIR(2));			// 色1 を使う
			mvaddstr(3, 40, " ");
			attrset(COLOR_PAIR(0));			// 色1 を使う
			mvaddstr(3, 41, "…?ブロック");
			attrset(COLOR_PAIR(3));			// 色1 を使う
			mvaddstr(3, 70, " ");
			attrset(COLOR_PAIR(0));			// 色1 を使う
			mvaddstr(3, 71, "…蔦");
			attrset(COLOR_PAIR(4));			// 色1 を使う
			mvaddstr(3, 100, " ");
			attrset(COLOR_PAIR(0));			// 色1 を使う
			mvaddstr(3, 101, "…雲ブロック");
			attrset(COLOR_PAIR(5));			// 色1 を使う
			mvaddstr(4, 10, " ");
			attrset(COLOR_PAIR(0));			// 色1 を使う
			mvaddstr(4, 11, "…ON/OFFブロック");
			attrset(COLOR_PAIR(1));			// 色1 を使う
			mvaddstr(4, 40, "O");
			attrset(COLOR_PAIR(0));			// 色1 を使う
			mvaddstr(4, 41, "…赤ブロック");
			attrset(COLOR_PAIR(7));			// 色1 を使う
			mvaddstr(4, 70, " ");
			attrset(COLOR_PAIR(0));			// 色1 を使う
			mvaddstr(4, 71, "…青ブロック");
#ifdef USEMUTEX
			WaitForSingleObject(threadMutex, INFINITE);
#endif
			make_map(cd->key, a);
			if (cd->key == 's') {
				erase();
				cd->save_mode = true;
			}
			cd->key = 0;
#ifdef USEMUTEX
			ReleaseMutex(threadMutex);
#endif
			refresh();
		}
	}
}

void threadSample(LPVOID data) {
	processA((stage*)data);
}
void threadSample1() {
	processB();
}
void threadSample2(LPVOID data) {
	processC((stage*)data);
}
void threadSample3(LPVOID data) {
	processD((stage*)data);
}

int main(void) {
	cd->mode = param_init("command", "mode");
	cd->mode_select = param_init("command", "mode_select");
	cd->key = param_init("command", "key");
	add_dot();
	initscr();
	cd->prev_state = param_init("command", "prev_state");
	HANDLE threadHandler[NUMTHREAD];
	DWORD threadID[NUMTHREAD];
	while (true) {
		cd->mode = param_init("command", "mode");
		while (cd->mode == 0) {
			threadMutex = CreateMutex(NULL, FALSE, NULL);//ミューテックス生成
			threadHandler[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadSample, (LPVOID)st1, 0, &threadID[0]);
			threadHandler[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadSample1, NULL, 0, &threadID[1]);
			//threadHandler[2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadSample3, (LPVOID)st1, 0, &threadID[2]);
			for (int i = 0; i < 2; i++) {
				WaitForSingleObject(threadHandler[i], INFINITE);
				CloseHandle(threadHandler[i]);
			}
			CloseHandle(threadMutex);
			erase();
			cd->prev_state = param_init("command", "prev_state");
		}
		while (cd->mode == 1) {
			threadMutex = CreateMutex(NULL, FALSE, NULL);//ミューテックス生成
			threadHandler[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadSample, (LPVOID)st1, 0, &threadID[0]);
			threadHandler[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadSample3, (LPVOID)new_stage, 0, &threadID[1]);
			for (int i = 0; i < 2; i++) {
				WaitForSingleObject(threadHandler[i], INFINITE);
				CloseHandle(threadHandler[i]);
			}
			CloseHandle(threadMutex);
			erase();
			cd->mode = param_init("command", "mode");
			cd->prev_state = param_init("command", "prev_state");
		}
		while (cd->mode==2) {
			c1.x = param_init("character", "x");
			c1.y=  param_init("character", "y");
			c1.goal_flag = param_init("character", "goalflag");
			c1.coin= param_init("character", "coin");
			st1->x = param_init("stage", "x");
			st1->y = param_init("stage", "y");
			st1->on_off_switch = param_init("stage", "on_off_switch");
			threadMutex = CreateMutex(NULL, FALSE, NULL);//ミューテックス生成
			threadHandler[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadSample, (LPVOID)st1, 0, &threadID[0]);
			threadHandler[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadSample2, (LPVOID)st1, 0, &threadID[1]);
			//threadHandler[2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadSample3, (LPVOID)st1, 0, &threadID[2]);
			for (int i = 0; i < 2; i++) {
				WaitForSingleObject(threadHandler[i], INFINITE);
				CloseHandle(threadHandler[i]);
			}
			CloseHandle(threadMutex);
			erase();
			cd->mode = 3;
			cd->prev_state = param_init("command", "prev_state");
		}
		while (cd->mode == 3) {
			if (cd->mode_select == 2) {
				while (cd->mode == 3) {
					start_color();
					init_pair(0, COLOR_WHITE, COLOR_BLACK);	// 色1 は黒地に白文字
					mvaddstr(5, 30, "作る");
					mvaddstr(7, 30, "Ａ：ブロックの種類を変える");
					mvaddstr(9, 30, "S：セーブする");
					mvaddstr(15, 30, "作る");
					mvaddstr(17, 30, "Ａ：攻撃");
					mvaddstr(19, 30, "S：ジャンプする");
					mvaddstr(29, 100, "戻る　＜-");
					refresh();
					cd->key = getch();
					if (cd->key == 'a') {
						cd->mode = param_init("command", "mode");
						cd->key = param_init("command", "key");
					}
				}
			}
			else if (c1.goal_flag) {
				start_color();
				init_pair(0, COLOR_WHITE, COLOR_BLACK);	// 色1 は黒地に白文字
				mvaddstr(15, 60, "ステージクリア");
				mvprintw(18, 60, "獲得コイン：%d枚",c1.coin);
				refresh();
				Sleep(3000);
			}
			else {
				start_color();
				init_pair(0, COLOR_WHITE, COLOR_BLACK);	// 色1 は黒地に白文字
				mvaddstr(15, 60, "ゲームオーバー");
				refresh();
				Sleep(3000);
			}

			erase();
			cd->mode = param_init("command", "mode");
		}
	}
	return 0;
}
