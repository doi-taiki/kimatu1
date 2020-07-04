#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include "game.h"

#include "character.h"
/*
extern unsigned char background1[16][16];
extern unsigned char background2[16][16];
extern unsigned char N_brock[16][16];
extern unsigned char Q_brock[16][16];
extern unsigned char LdotU_N[16][16];
extern unsigned char LdotU_A[16][16];
extern unsigned char LdotD_N[16][16];
extern unsigned char LdotD2_N[16][16];
extern unsigned char LdotD_A[16][16];
extern unsigned char LdotL_N[16][16];
extern unsigned char LdotL2_N[16][16];
extern unsigned char LdotL_A[16][16];
extern unsigned char LdotR_N[16][16];
extern unsigned char LdotR_A[16][16];
extern unsigned char LdotR2_N[16][16];
extern unsigned char Octarock[16][16];
extern unsigned char Octarock2[16][16];
extern unsigned char Sword1[16][16];
extern unsigned char Sword2[16][16];
extern unsigned char Sword3[16][16];
extern unsigned char DarknutU[16][16];
extern unsigned char DarknutD1[16][16];
extern unsigned char DarknutD2[16][16];
extern unsigned char DarknutL1[16][16];
extern unsigned char DarknutL2[16][16];
extern unsigned char Pole[16][16];
extern unsigned char Pole_Ball[16][16];
*/
void make_character(unsigned char dot[16][16],extern character* c,stage* st) {
	int i = 0;
	int j = 0;
	start_color();
	init_pair(0, COLOR_WHITE, COLOR_BLACK);	// 色1 は黒地に白文字
	init_pair(1, COLOR_WHITE, COLOR_GREEN);	// 色1 は緑地に白文字
	init_pair(2, COLOR_WHITE, COLOR_YELLOW);	// 色2 は黄地に白文字
	init_pair(3, COLOR_WHITE, COLOR_RED);	// 色3 は赤地に白文字
	init_pair(4, COLOR_WHITE, COLOR_BLUE);	// 色4 は青地に白文字
	init_pair(5, COLOR_WHITE, COLOR_CYAN);	// 色5 はシアン地に白文字
	init_pair(6, COLOR_WHITE, COLOR_WHITE);	// 色6 は白地に白文字
	for (i = 0; i < 16; i++) {
		move(30 - c->y + i, c->x);
		for (j = 0; j < 16; j++) {
			if (i - c->y < 0) {
				if (dot[i][j] == 1) {
					attrset(COLOR_PAIR(1));			// 色1 を使う
				}
				else if (dot[i][j] == 2) {
					attrset(COLOR_PAIR(2));			// 色2 を使う
				}
				else if (dot[i][j] == 3) {
					attrset(COLOR_PAIR(3));			// 色1 を使う
				}
				else if (dot[i][j] == 4) {
					attrset(COLOR_PAIR(4));			// 色1 を使う
				}
				else if (dot[i][j] == 5) {
					attrset(COLOR_PAIR(5));			// 色2 を使う
				}
				else if (dot[i][j] == 6) {
					attrset(COLOR_PAIR(6));			// 色1 を使う
				}
				else {
					attrset(COLOR_PAIR(0));
				}
				addch(0x20);
			}
		}
	}
}
int key_operation(int key,int prev_state,character* c,stage* st) {
	int state=prev_state;
	switch (prev_state) {
	case 0:
		make_character(LdotU_N, c,st);
		break;
	case 1:
		make_character(LdotD_N, c,st);
		break;
	case 2:
		make_character(LdotL_N, c,st);
		break;
	case 3:
		make_character(LdotL2_N, c,st);
		break;
	case 4:
		make_character(LdotR_N, c,st);
		break;
	case 5:
		make_character(LdotR2_N, c,st);
		break;
	case 6:
		make_character(LdotU_A, c,st);
		make_sword(c->x, c->y+16, Sword2, st);
		break;
	case 7:
		make_character(LdotD_A, c, st);
		break;
	case 8:
		make_character(LdotL_A, c, st);
		make_sword(c->x-16, c->y, Sword1, st);
		break;
	case 9:
		make_character(LdotR_A, c, st);
		make_sword(c->x+16, c->y, Sword3, st);
		break;

	default:
		break;
	}
	switch (key) {
	case KEY_UP:
		state = 0;
		make_character(LdotU_N, c, st);
		break;
	case KEY_DOWN:
		state = 1;
		make_character(LdotD_N, c, st);
		break;
	case KEY_LEFT:
		if (st->map[(st->x + c->x - 1) / 16][(st->y + c->y - 1) / 16] > 9 || st->map[(st->x + c->x - 1) / 16][(st->y + c->y - 16) / 16] > 9) {
			c->goal_flag = true;
			state = 100;
		}
		else if (st->map[(st->x + c->x - 1) / 16][(st->y + c->y - 1) / 16] == 0 && st->map[(st->x + c->x - 1) / 16][(st->y + c->y - 16) / 16] == 0) {
			if (c->x > 30) {
				c->x = c->x - 2;
			}
			else {
				if (st->x > 0) {
					st->x = st->x - 2;
				}
				else if (c->x > 0) {
					c->x = c->x - 2;
				}
			}
			if (prev_state != 2) {
				state = 2;
				make_character(LdotL_N, c, st);
			}
			else {
				state = 3;
				make_character(LdotL2_N, c, st);
			}
		}
		break;
	case KEY_RIGHT:
		if (st->map[(st->x + c->x + 16) / 16][(st->y + c->y - 1) / 16] > 9 || st->map[(st->x + c->x + 16) / 16][(st->y + c->y - 16) / 16] > 9) {
			c->goal_flag = true;
			state = 100;
		}
		else if (st->map[(st->x + c->x + 16) / 16][(st->y + c->y - 1) / 16] == 0 && st->map[(st->x + c->x + 16) / 16][(st->y + c->y - 16) / 16] == 0) {
			if (c->x < 70) {
				c->x = c->x + 2;
			}
			else {
				st->x = st->x + 2;
			}
			if (prev_state != 4) {
				state = 4;
				make_character(LdotR_N, c, st);
			}
			else {
				state = 5;
				make_character(LdotR2_N, c, st);
			}
		}
		break;
	case 'a':
		switch (prev_state) {
		case 0:
			state = 6;
			make_character(LdotU_A,c,st); 
			make_sword(c->x, c->y-16, Sword2, st);
			break;
		case 1:
			state = 7;
			make_character(LdotD_A,c,st);
			break;
		case 2 :
			state = 8;
			make_character(LdotL_A,c,st);
			make_sword(c->x-16, c->y, Sword1, st);
			break;
		case  3:
			state = 8;
			make_character(LdotL_A,c,st);
			make_sword(c->x-16, c->y, Sword1, st);
			break;
		case 4:
			state = 9;
			make_character(LdotR_A,c,st);
			make_sword(c->x+16, c->y, Sword3, st);
			break;
		case 5:
			state = 9;
			make_character(LdotR_A,c,st);
			make_sword(c->x+16, c->y , Sword3, st);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	if (c->jump > 0) {
		if (c->j_count > 0) {
			c->j_count--;
		}
		else {
			c->jump--;
			c->j_count = c->j_count + 10;
			if (st->map[(st->x + c->x) / 16][(st->y + c->y ) / 16] == 0 && st->map[(st->x + c->x + 15) / 16][(st->y + c->y ) / 16] == 0) {
				if (c->y <30) {
					c->y = c->y + 2;
				}
				else {
					if (st->y < 160) {
						st->y = st->y + 2;
					}
				}
			}
			else if (st->map[(st->x + c->x) / 16][(st->y + c->y-1) / 16] == 0 && st->map[(st->x + c->x + 15) / 16][(st->y + c->y-1) / 16] == 0) {
				if (c->y < 30) {
					c->y++;
				}
				else {
					if (st->y < 160) {
						st->y++;
					}
				}
			}
			else {
				c->jump = 0;
				c->j_count = 0;
			}
		}
	}
	else if (st->map[(st->x + c->x) / 16][(st->y + c->y-17) / 16] == 0 && st->map[(st->x + c->x + 15) / 16][(st->y + c->y-17) / 16] == 0) {
		if (c->j_count > 0) {
			c->j_count--;
		}
		else {
			if (c->y > 26) {
				c->y--;
			}
			else {
				if (st->y > 10) {
					st->y--;
				}
				else if(c->y>1){
					c->y--;
				}
				else {
					state = 100;//ゲームオーバー
				}
			}
			c->j_count = c->j_count + 6;
		}
	}
	else if (key == 's') {
		c->jump = 25;
	}
	return state;
}
void make_obj(int m,int n,unsigned char obj[16][16],stage* st) {
	int i = 0;
	int j = 0;
	start_color();
	init_pair(0, COLOR_WHITE, COLOR_BLACK);	// 色0 は黒地に白文字
	init_pair(1, COLOR_WHITE, COLOR_GREEN);	// 色1 は緑地に白文字
	init_pair(2, COLOR_WHITE, COLOR_YELLOW);	// 色2 は黄地に白文字
	init_pair(3, COLOR_WHITE, COLOR_RED);	// 色3 は赤地に白文字
	init_pair(4, COLOR_WHITE, COLOR_BLUE);	// 色4 は青地に白文字
	init_pair(5, COLOR_WHITE, COLOR_CYAN);	// 色5 はシアン地に白文字
	init_pair(6, COLOR_WHITE, COLOR_WHITE);	// 色6 は白地に白文字
	for (i = 0; i < 16; i++) {
		for (j = 0; j < 16; j++) {
			if (obj[i][j] == 1) {
				attrset(COLOR_PAIR(1));			// 色1 を使う
			}
			else if (obj[i][j] == 2) {
				attrset(COLOR_PAIR(2));			// 色2 を使う
			}
			else if (obj[i][j] == 3) {
				attrset(COLOR_PAIR(3));			// 色3 を使う
			}
			else if (obj[i][j] == 4) {
				attrset(COLOR_PAIR(4));			// 色4 を使う
			}
			else if (obj[i][j] == 5) {
				attrset(COLOR_PAIR(5));			// 色5 を使う
			}
			else if (obj[i][j] == 6) {
				attrset(COLOR_PAIR(6));			// 色6 を使う
			}
			else {
				attrset(COLOR_PAIR(0));
			}
			mvaddstr(14-n*16+st->y+i, (m*16-st->x) + j, " ");
		}
	}
}
void make_sword(int m, int n, unsigned char obj[16][16], stage* st) {
	int i = 0;
	int j = 0;
	start_color();
	init_pair(0, COLOR_WHITE, COLOR_BLACK);	// 色1 は黒地に白文字
	init_pair(1, COLOR_WHITE, COLOR_GREEN);	// 色1 は緑地に白文字
	init_pair(2, COLOR_WHITE, COLOR_YELLOW);	// 色2 は黄地に白文字
	init_pair(3, COLOR_WHITE, COLOR_RED);	// 色3 は赤地に白文字
	init_pair(4, COLOR_WHITE, COLOR_BLUE);	// 色4 は青地に白文字
	init_pair(5, COLOR_WHITE, COLOR_CYAN);	// 色5 はシアン地に白文字
	init_pair(6, COLOR_WHITE, COLOR_WHITE);	// 色6 は白地に白文字
	for (i = 0; i < 16; i++) {
		for (j = 0; j < 16; j++) {
			if (obj[i][j] == 1) {
				attrset(COLOR_PAIR(1));			// 色1 を使う
			}
			else if (obj[i][j] == 2) {
				attrset(COLOR_PAIR(2));			// 色2 を使う
			}
			else if (obj[i][j] == 3) {
				attrset(COLOR_PAIR(6));			// 色3 を使う
			}
			else if (obj[i][j] == 4) {
				attrset(COLOR_PAIR(4));			// 色3 を使う
			}
			else if (obj[i][j] == 5) {
				attrset(COLOR_PAIR(5));			// 色3 を使う
			}
			else if (obj[i][j] == 6) {
				attrset(COLOR_PAIR(6));			// 色3 を使う
			}
			else {
				attrset(COLOR_PAIR(0));
			}
			mvaddstr(30-n + i, m + j, " ");
		}
	}
}
void make_stage(stage* st) {
	int i, j;
	for (i = st->x / 16; i < (st->x + 119)/16+1; i++) {
		for (j = st->y / 16; j < (st->y + 30)/16+1; j++) {
			switch (st->map[i][j]) {
			case 0:
				make_obj(i, j, background1, st);
				break;
			case 1:
				make_obj(i,j,N_brock, st);
				break;
			case 2:
				make_obj(i,j,Q_brock, st);
				break;
			case 10:
				make_obj(i, j, Pole, st);
				break;
			case 11:
				make_obj(i, j, N_brock , st);
				break;
			case 12:
				make_obj(i, j, Pole_Ball, st);
				break;
			default:
				break;
			}
		}
	}
}
void add_dot(void) {
	int i, j;
	for (i = 0; i < 16; i++) {
		for (j = 0; j < 16; j++) {
			LdotR_N[i][j] = LdotL_N[i][15 - j];
			LdotR2_N[i][j] = LdotL2_N[i][15 - j];
			LdotR_A[i][j] = LdotL_A[i][15 - j];
			Sword3[i][j] = Sword1[i][15 - j];
		}
	}
}
void make_map(int key, stage* ns) {
	int i;
	
	switch(key) {
	case KEY_UP:
		if (ns->goal_mode == false) {
			if (ns->y < 9) {
				ns->y++;
			}
		}
		break;
	case KEY_DOWN:
		if (ns->goal_mode == false) {
			if (ns->y > 0) {
				ns->y--;
			}
		}
		break;
	case KEY_LEFT:
		if (ns->goal_mode == false) {
			if (ns->x > 0) {
				ns->x--;
			}
		}
		break;
	case KEY_RIGHT:
		if (ns->goal_mode == false) {
			if (ns->x < 99) {
				ns->x++;
			}
		}
		break;
	case 'a':
		if (ns->goal_mode == false) {
			if (ns->map[ns->x][ns->y] < 10) {
				ns->map[ns->x][ns->y] = (ns->map[ns->x][ns->y] + 1) % 3;
			}
			else {
				ns->goal_mode = true;
			}
		}
		else {
			ns->goal_mode = false;
		}
		break;
	default:
		break;
	}
	init_pair(0, COLOR_WHITE, COLOR_BLACK);	// 色1 は黒地に白文字
	init_pair(1, COLOR_WHITE, COLOR_RED);	// 色1 は赤地に白文字
	init_pair(2, COLOR_WHITE, COLOR_YELLOW);	// 色2 は黄地に白文字
	init_pair(10, COLOR_WHITE, COLOR_WHITE);	// 色2 は黄地に白文字
	init_pair(11, COLOR_YELLOW, COLOR_RED);	// 色2 は黄地に白文字
	init_pair(12, COLOR_YELLOW, COLOR_GREEN);	// 色2 は黄地に白文字
	if (ns->goal_mode == false) {
		attrset(COLOR_PAIR(ns->map[ns->x][ns->y]));			// 色1 を使う
		mvaddstr((9 - ns->y) + 10, ns->x + 10, " ");
		move((9 - ns->y) + 10, ns->x + 10);
	}
	else {
		if (key == KEY_RIGHT) {
			if (ns->x < 99) {
				ns->map[ns->x][0] = 0;
				ns->map[ns->x + 1][0] = 11;
				for (i = 1; i < 6; i++) {
					ns->map[ns->x][i] = 0;
					ns->map[ns->x+1][i] = 10;
				}
				ns->map[ns->x][6] = 0;
				ns->map[ns->x + 1][6] = 12;
				for (i = 0; i < 7; i++) {
					attrset(COLOR_PAIR(ns->map[ns->x][i]));			// 色1 を使う
					mvaddstr((9 - i) + 10, ns->x + 10, " ");
					attrset(COLOR_PAIR(ns->map[ns->x+1][i]));			// 色1 を使う
					mvaddstr((9 - i) + 10, ns->x + 11, " ");
					move((9 - i) + 10, ns->x + 11);
				}
				ns->x++;
			}
		}
		else if (key == KEY_LEFT) {
			if (ns->x >20) {
				ns->map[ns->x][0] = 0;
				ns->map[ns->x - 1][0] = 11;
				for (i =1; i < 6; i++) {
					ns->map[ns->x][i] = 0;
					ns->map[ns->x - 1][i] = 10;
				}
				ns->map[ns->x][6] = 0;
				ns->map[ns->x - 1][6] = 12;
				for (i = 0; i < 7; i++) {
					attrset(COLOR_PAIR(ns->map[ns->x][i]));			// 色1 を使う
					mvaddstr((9 - i) + 10, ns->x + 10, " ");
					attrset(COLOR_PAIR(ns->map[ns->x - 1][i]));			// 色1 を使う
					mvaddstr((9 - i) + 10, ns->x + 9, " ");
					move((9 - i) + 10, ns->x + 9);
				}
				ns->x--;
			}
		}
	}
}
void init_map(stage* ns) {
	int i, j;
	init_pair(0, COLOR_WHITE, COLOR_BLACK);	// 色1 は黒地に白文字
	init_pair(1, COLOR_WHITE, COLOR_RED);	// 色1 は赤地に白文字
	init_pair(2, COLOR_WHITE, COLOR_YELLOW);	// 色2 は黄地に白文字
	init_pair(10, COLOR_WHITE, COLOR_WHITE);	// 色2 は黄地に白文字
	init_pair(11, COLOR_YELLOW, COLOR_YELLOW);	// 色2 は黄地に白文字
	for (i = 0; i < 100; i++) {
		for (j = 0; j < 10; j++) {
			attrset(COLOR_PAIR(ns->map[i][j]));			// 色1 を使う
			mvaddstr((9 - j) + 10, i + 10, " ");
			move((9 - i) + 10, j + 10);
		}
	}
}