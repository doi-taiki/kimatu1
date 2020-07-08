#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include "game.h"

#include "character.h"
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
int key_operation(int key,int prev_state,character* c,stage* st) {//キー操作でキャラクターを動かす
	int state=prev_state;
	switch (prev_state) {//キー操作が無かった場合、前の状態を保持する
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
		make_sword(c->x, c->y - 16, Sword4, st);
		break;
	case 8:
		make_character(LdotL_A, c, st);
		make_sword(c->x-16, c->y, Sword1, st);
		break;
	case 9:
		make_character(LdotR_A, c, st);
		make_sword(c->x+16, c->y, Sword3, st);
		break;
	case 10:
		make_character(LdotU2_N, c, st);
		break;
	default:
		break;
	}
	switch (key) {
	case KEY_UP://上が押された場合
		if (prev_state != 0) {//状態を上向きにする
			state = 0;
			make_character(LdotU_N, c, st);
		}
		else {
			state = 10;
			make_character(LdotU2_N, c, st);
		}
		if (PassingIby(st->map[(st->x + c->x) / 16][(st->y + c->y) / 16],st) && PassingIby(st->map[(st->x + c->x + 15) / 16][(st->y + c->y) / 16],st)) {//ニマスのブロックが通り抜けられるかどうか
			if (Passing(st->map[(st->x + c->x) / 16][(st->y + c->y) / 16], state,st) && Passing(st->map[(st->x + c->x + 15) / 16][(st->y + c->y) / 16], state,st)&& Passing(st->map[(st->x + c->x) / 16][(st->y + c->y-15) / 16], state,st) && Passing(st->map[(st->x + c->x + 15) / 16][(st->y + c->y-15) / 16], state,st)) {//ニマス先のブロックが上向き状態且つ蔦の場合は蔦を掴む
			}else{
				if (c->y < 30) {
					c->y = c->y + 2;
				}
				else {
					if (st->y < 160) {
						st->y = st->y + 2;
					}
				}
			}
		}
		else if (PassingIby(st->map[(st->x + c->x) / 16][(st->y + c->y - 1) / 16],st) && PassingIby(st->map[(st->x + c->x + 15) / 16][(st->y + c->y - 1) / 16],st)) {//一マスのブロックが通り抜けられるかどうか
			if (Passing(st->map[(st->x + c->x) / 16][(st->y + c->y) / 16], state,st) && Passing(st->map[(st->x + c->x + 15) / 16][(st->y + c->y) / 16], state,st) && Passing(st->map[(st->x + c->x) / 16][(st->y + c->y - 15) / 16], state,st) && Passing(st->map[(st->x + c->x + 15) / 16][(st->y + c->y - 15) / 16], state,st)) {//一マス先のブロックが上向き状態且つ蔦の場合は蔦を掴む
			}else{
				if (c->y < 30) {
					c->y++;
				}
				else {
					if (st->y < 160) {
						st->y++;
					}
				}
			}
		}
		break;
	case KEY_DOWN://当たり判定は上を押した時と同じ
		if (PassingIby(st->map[(st->x + c->x) / 16][(st->y + c->y - 17) / 16],st) && PassingIby(st->map[(st->x + c->x + 15) / 16][(st->y + c->y - 17) / 16],st)) {
			if (Passing(st->map[(st->x + c->x) / 16][(st->y + c->y - 1) / 16], state,st) && Passing(st->map[(st->x + c->x + 15) / 16][(st->y + c->y - 1) / 16], state,st) && Passing(st->map[(st->x + c->x) / 16][(st->y + c->y - 17) / 16], state,st) && Passing(st->map[(st->x + c->x + 15) / 16][(st->y + c->y - 17) / 16], state,st)) {
			state=1;
			make_character(LdotD_N, c, st);
			}else{
				if (c->y > 26) {
					c->y--;
				}
				else {
					if (st->y > 10) {
						st->y--;
					}
					else if (c->y > 1) {
						c->y--;
					}
				}
				if (prev_state != 0) {
					state = 0;
					make_character(LdotU_N, c, st);
				}
				else {
					state = 10;
					make_character(LdotU2_N, c, st);
				}
			}
		}
		else {
			state = 1;
			make_character(LdotD_N, c, st);
		}
		break;
	case KEY_LEFT://当たり判定は上を押した時と同じ
		if (st->map[(st->x + c->x - 1) / 16][(st->y + c->y - 1) / 16] > 9 || st->map[(st->x + c->x - 1) / 16][(st->y + c->y - 16) / 16] > 9) {
			c->goal_flag = true;
			state = 100;
		}
		else if (PassingIby(st->map[(st->x + c->x - 1) / 16][(st->y + c->y - 1) / 16],st )&& PassingIby(st->map[(st->x + c->x - 1) / 16][(st->y + c->y - 16) / 16],st)) {
			if (Passing(st->map[(st->x + c->x - 1) / 16][(st->y + c->y - 1) / 16], state,st) && Passing(st->map[(st->x + c->x - 1) / 16][(st->y + c->y - 16) / 16], state,st) && Passing(st->map[(st->x + c->x + 15) / 16][(st->y + c->y - 1) / 16], state,st) && Passing(st->map[(st->x + c->x + 15) / 16][(st->y + c->y - 16) / 16], state,st)) {
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
			else {
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
				if (prev_state != 0) {
					state = 0;
					make_character(LdotU_N, c, st);
				}
				else {
					state = 10;
					make_character(LdotU2_N, c, st);
				}
			}
		}
		break;
	case KEY_RIGHT://当たり判定は上を押した時と同じ
		if (st->map[(st->x + c->x + 16) / 16][(st->y + c->y - 1) / 16] > 9 || st->map[(st->x + c->x + 16) / 16][(st->y + c->y - 16) / 16] > 9) {
			c->goal_flag = true;
			state = 100;
		}
		else if (PassingIby(st->map[(st->x + c->x + 16) / 16][(st->y + c->y - 1) / 16],st) && PassingIby(st->map[(st->x + c->x + 16) / 16][(st->y + c->y - 16) / 16],st)) {
			if (Passing(st->map[(st->x + c->x) / 16][(st->y + c->y - 1) / 16], state,st) && Passing(st->map[(st->x + c->x) / 16][(st->y + c->y - 16) / 16], state,st)&&Passing(st->map[(st->x + c->x + 16) / 16][(st->y + c->y - 1) / 16], state,st) && Passing(st->map[(st->x + c->x + 16) / 16][(st->y + c->y - 16) / 16], state,st)) {
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
			else {
				if (c->x < 70) {
					c->x = c->x + 2;
				}
				else {
					st->x = st->x + 2;
				}
				if (prev_state != 0) {
					state = 0;
					make_character(LdotU_N, c, st);
				}
				else {
					state = 10;
					make_character(LdotU2_N, c, st);
				}
			}
		}
		break;
	case 'a':
		switch (prev_state) {//剣の描画・当たり判定は当たり半手のある頂点4マスを調べる
		case 0:
			if (Q_push(st->map[(st->x + c->x) / 16][(st->y + c->y) / 16])) {
				st->map[(st->x + c->x) / 16][(st->y + c->y) / 16] = 9;
				c->coin++;
			}
			else if (Q_push(st->map[(st->x + c->x + 15) / 16][(st->y + c->y) / 16])) {
				st->map[(st->x + c->x + 15) / 16][(st->y + c->y) / 16] = 9;
				c->coin++;
			}
			else if (Q_push(st->map[(st->x + c->x) / 16][(st->y + c->y+15) / 16])) {
				st->map[(st->x + c->x) / 16][(st->y + c->y) / 16] = 9;
				c->coin++;
			}
			else if (Q_push(st->map[(st->x + c->x + 15) / 16][(st->y + c->y+15) / 16])) {
				st->map[(st->x + c->x + 15) / 16][(st->y + c->y) / 16] = 9;
				c->coin++;
			}
			state = 6;
			make_character(LdotU_A,c,st); 
			make_sword(c->x, c->y-16, Sword2, st);
			break;
		case 1:
			if (Q_push(st->map[(st->x + c->x) / 16][(st->y + c->y-17) / 16])) {
				st->map[(st->x + c->x) / 16][(st->y + c->y-17) / 16] = 9;
				c->coin++;
			}
			else if (Q_push(st->map[(st->x + c->x + 15) / 16][(st->y + c->y-17) / 16])) {
				st->map[(st->x + c->x + 15) / 16][(st->y + c->y-17) / 16] = 9;
				c->coin++;
			}
			else if (Q_push(st->map[(st->x + c->x) / 16][(st->y + c->y -33) / 16])) {
				st->map[(st->x + c->x) / 16][(st->y + c->y - 33) / 16] = 9;
				c->coin++;
			}
			else if (Q_push(st->map[(st->x + c->x + 15) / 16][(st->y + c->y - 33) / 16])) {
				st->map[(st->x + c->x + 15) / 16][(st->y + c->y - 33) / 16] = 9;
				c->coin++;
			}
			state = 7;
			make_character(LdotD_A,c,st);
			make_sword(c->x, c->y+16, Sword4, st);
			break;
		case 2 :
			if (Q_push(st->map[(st->x + c->x-15) / 16][(st->y + c->y-1) / 16])) {
				st->map[(st->x + c->x-15) / 16][(st->y + c->y-1) / 16] = 9;
				c->coin++;
			}
			else if (Q_push(st->map[(st->x + c->x -15) / 16][(st->y + c->y - 15) / 16])) {
				st->map[(st->x + c->x-15 ) / 16][(st->y + c->y - 15) / 16] = 9;
				c->coin++;
			}
			else if (Q_push(st->map[(st->x + c->x ) / 16][(st->y + c->y - 1) / 16])) {
				st->map[(st->x + c->x ) / 16][(st->y + c->y - 1) / 16] = 9;
				c->coin++;
			}
			else if (Q_push(st->map[(st->x + c->x ) / 16][(st->y + c->y - 15) / 16])) {
				st->map[(st->x + c->x ) / 16][(st->y + c->y - 15) / 16] = 9;
				c->coin++;
			}
			state = 8;
			make_character(LdotL_A,c,st);
			make_sword(c->x-16, c->y, Sword1, st);
			break;
		case  3:
			if (Q_push(st->map[(st->x + c->x - 15) / 16][(st->y + c->y - 1) / 16])) {
				st->map[(st->x + c->x - 15) / 16][(st->y + c->y - 1) / 16] = 9;
				c->coin++;
			}
			else if (Q_push(st->map[(st->x + c->x - 15) / 16][(st->y + c->y - 15) / 16])) {
				st->map[(st->x + c->x - 15) / 16][(st->y + c->y - 15) / 16] = 9;
				c->coin++;
			}
			else if (Q_push(st->map[(st->x + c->x) / 16][(st->y + c->y - 1) / 16])) {
				st->map[(st->x + c->x) / 16][(st->y + c->y - 1) / 16] = 9;
				c->coin++;
			}
			else if (Q_push(st->map[(st->x + c->x) / 16][(st->y + c->y - 15) / 16])) {
				st->map[(st->x + c->x) / 16][(st->y + c->y - 15) / 16] = 9;
				c->coin++;
			}
			state = 8;
			make_character(LdotL_A,c,st);
			make_sword(c->x-16, c->y, Sword1, st);
			break;
		case 4:
			if (Q_push(st->map[(st->x + c->x+16) / 16][(st->y + c->y-1) / 16])) {
				st->map[(st->x + c->x+16) / 16][(st->y + c->y-1) / 16] = 9;
				c->coin++;
			}
			else if (Q_push(st->map[(st->x + c->x+16) / 16][(st->y + c->y - 15) / 16])) {
				st->map[(st->x + c->x+16) / 16][(st->y + c->y - 16) / 15] = 9;
				c->coin++;
			}
			else if (Q_push(st->map[(st->x + c->x + 32) / 16][(st->y + c->y - 1) / 16])) {
				st->map[(st->x + c->x + 32) / 16][(st->y + c->y - 1) / 16] = 9;
				c->coin++;
			}
			else if (Q_push(st->map[(st->x + c->x + 32) / 16][(st->y + c->y - 15) / 16])) {
				st->map[(st->x + c->x + 32) / 16][(st->y + c->y - 16) / 15] = 9;
				c->coin++;
			}
			state = 9;
			make_character(LdotR_A,c,st);
			make_sword(c->x+16, c->y, Sword3, st);
			break;
		case 5:
			if (Q_push(st->map[(st->x + c->x + 16) / 16][(st->y + c->y - 1) / 16])) {
				st->map[(st->x + c->x + 16) / 16][(st->y + c->y - 1) / 16] = 9;
				c->coin++;
			}
			else if (Q_push(st->map[(st->x + c->x + 16) / 16][(st->y + c->y - 15) / 16])) {
				st->map[(st->x + c->x + 16) / 16][(st->y + c->y - 16) / 15] = 9;
				c->coin++;
			}
			else if (Q_push(st->map[(st->x + c->x + 32) / 16][(st->y + c->y - 1) / 16])) {
				st->map[(st->x + c->x + 32) / 16][(st->y + c->y - 1) / 16] = 9;
				c->coin++;
			}
			else if (Q_push(st->map[(st->x + c->x + 32) / 16][(st->y + c->y - 15) / 16])) {
				st->map[(st->x + c->x + 32) / 16][(st->y + c->y - 16) / 15] = 9;
				c->coin++;
			}
			state = 9;
			make_character(LdotR_A,c,st);
			make_sword(c->x+16, c->y , Sword3, st);
			break;
		case 10:
			if (Q_push(st->map[(st->x + c->x) / 16][(st->y + c->y) / 16])) {
				st->map[(st->x + c->x) / 16][(st->y + c->y) / 16] = 9;
				c->coin++;
			}
			else if (Q_push(st->map[(st->x + c->x + 15) / 16][(st->y + c->y) / 16])) {
				st->map[(st->x + c->x + 15) / 16][(st->y + c->y) / 16] = 9;
				c->coin++;
			}
			else if (Q_push(st->map[(st->x + c->x) / 16][(st->y + c->y + 15) / 16])) {
				st->map[(st->x + c->x) / 16][(st->y + c->y) / 16] = 9;
				c->coin++;
			}
			else if (Q_push(st->map[(st->x + c->x + 15) / 16][(st->y + c->y + 15) / 16])) {
				st->map[(st->x + c->x + 15) / 16][(st->y + c->y) / 16] = 9;
				c->coin++;
			}
			state = 6;
			make_character(LdotU_A, c, st);
			make_sword(c->x, c->y - 16, Sword2, st);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	if (c->jump > 0) {//ジャンプで上に上がる回数
		if (c->j_count > 0) {//ジャンプの速度調整
			c->j_count--;
		}
		else {
			c->jump--;
			c->j_count = c->j_count + 10;
			if (PassingIby(st->map[(st->x + c->x) / 16][(st->y + c->y ) / 16] ,st) && PassingIby(st->map[(st->x + c->x + 15) / 16][(st->y + c->y ) / 16],st)) {
				if (c->y <30) {
					c->y = c->y + 2;
				}
				else {
					if (st->y < 160) {
						st->y = st->y + 2;
					}
				}
			}
			else if (PassingIby(st->map[(st->x + c->x) / 16][(st->y + c->y-1) / 16],st) && PassingIby(st->map[(st->x + c->x + 15) / 16][(st->y + c->y-1) / 16] ,st)) {
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
				if (switch_change(st->map[(st->x + c->x) / 16][(st->y + c->y) / 16]) || switch_change(st->map[(st->x + c->x + 15) / 16][(st->y + c->y) / 16])) {
					st->on_off_switch = (st->on_off_switch + 1) % 2;
				}
				if (Q_push(st->map[(st->x + c->x) / 16][(st->y + c->y) / 16]) ) {//マップのy座標は一定の高さを保つので書き込みエラーは起こらない
					st->map[(st->x + c->x) / 16][(st->y + c->y) / 16] = 9;
					c->coin++;
				}
				else if (Q_push(st->map[(st->x + c->x+15) / 16][(st->y + c->y) / 16])){
					st->map[(st->x + c->x + 15) / 16][(st->y + c->y) / 16] = 9;
					c->coin++;
				}
				c->jump = 0;
				c->j_count = 0;
			}
		}
	}
	else if ((Passing(st->map[(st->x + c->x) / 16][(st->y + c->y-17) / 16], state,st) && Passing(st->map[(st->x + c->x + 15) / 16][(st->y + c->y-17) / 16],state,st))&& PassingCloud(st,c)) {//落下処理
		if (c->j_count > 0) {//落下速度調整
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
void make_obj(int m,int n,unsigned char obj[16][16],stage* st,chtype on_off_color) {//ブロックの種類に応じたドットを出力する
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
			else if(obj[i][j] == 7){
				if (on_off_color==COLOR_RED) {
					attrset(COLOR_PAIR(3));			// 色6 を使う
				}
				else if (on_off_color == COLOR_BLUE) {
					attrset(COLOR_PAIR(4));			// 色6 を使う
				}
			}
			else {
				attrset(COLOR_PAIR(0));
			}
			mvaddstr(14-n*16+st->y+i, (m*16-st->x) + j, " ");
		}
	}
}
void make_sword(int m, int n, unsigned char obj[16][16], stage* st) {//剣を描画する
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
void make_stage(stage* st) {//マップのｘ座標とｙ座標から今画面上に出てるブロックを画面上に描画する
	int i, j;
	for (i = st->x / 16; i < (st->x + 119)/16+1; i++) {
		for (j = st->y / 16; j < (st->y + 30)/16+1; j++) {
			if (j < 10) {
				switch (st->map[i][j]) {
				case 0:
					make_obj(i, j, background1, st,NULL);
					break;
				case 1:
					make_obj(i, j, N_brock, st, NULL);
					break;
				case 2:
					make_obj(i, j, Q_brock, st, NULL);
					break;
				case 3:
					make_obj(i, j, Iby, st, NULL);
					break;
				case 4:
					make_obj(i, j, Cloud, st, NULL);
					break;
				case 5:
					if (st->on_off_switch) {
						make_obj(i, j, ON_SWITCH, st, NULL);
					}
					else {
						make_obj(i, j, OFF_SWITCH, st, NULL);
					}
					break;
				case 6:
					if (st->on_off_switch) {
						make_obj(i, j, ON_BROCK, st, COLOR_RED);
					}
					else {
						make_obj(i, j, OFF_BROCK, st, COLOR_RED);
					}
					break;
				case 7:
					if (st->on_off_switch) {
						make_obj(i, j, OFF_BROCK, st, COLOR_BLUE);
					}
					else {
						make_obj(i, j, ON_BROCK , st, COLOR_BLUE);
					}
					break;
				case 8:
					make_obj(i, j, Heart, st, NULL);
					break;
				case 9:
					make_obj(i, j, Used_brock, st, NULL);
					break;
				case 10:
					make_obj(i, j, Pole, st, NULL);
					break;
				case 11:
					make_obj(i, j, N_brock, st, NULL);
					break;
				case 12:
					make_obj(i, j, Pole_Ball, st, NULL);
					break;
				default:
					break;
				}
			}
			
		}
	}
}
void add_dot(void) {//逆向きや反転したドットを加える
	int i, j;
	for (i = 0; i < 16; i++) {
		for (j = 0; j < 16; j++) {
			LdotU2_N[i][j] = LdotU_N[i][15 - j];
			LdotR_N[i][j] = LdotL_N[i][15 - j];
			LdotR2_N[i][j] = LdotL2_N[i][15 - j];
			LdotR_A[i][j] = LdotL_A[i][15 - j];
			Sword3[i][j] = Sword1[i][15 - j];
			Sword4[i][j] = Sword2[15-i][15 - j];
		}
	}
}
void make_map(int key, stage* ns) {//作るモードでマップを作成する
	int i;
	switch(key) {//ゴールポールを動かさない時はカーソルを移動する
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
			if (ns->map[ns->x][ns->y] < 10) {//ゴールポールではない時
				ns->map[ns->x][ns->y] = (ns->map[ns->x][ns->y] + 1) % 8;
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
	init_pair(3, COLOR_WHITE, COLOR_GREEN);	// 色3 は緑地に白文字
	init_pair(4, COLOR_WHITE, COLOR_WHITE);	// 色4 は白地に白文字
	init_pair(5, COLOR_WHITE, COLOR_MAGENTA);	// 色5 はマゼンタ地に白文字
	init_pair(6, COLOR_WHITE, COLOR_RED);	// 色6 は赤地に白文字
	init_pair(7, COLOR_WHITE, COLOR_BLUE);	// 色7 は青地に白文字
	init_pair(10, COLOR_WHITE, COLOR_WHITE);	// 色2 は黄地に白文字
	init_pair(11, COLOR_YELLOW, COLOR_RED);	// 色2 は黄地に白文字
	init_pair(12, COLOR_YELLOW, COLOR_GREEN);	// 色2 は黄地に白文字
	if (ns->goal_mode == false) {
		attrset(COLOR_PAIR(ns->map[ns->x][ns->y]));			// 色1 を使う
		if (ns->map[ns->x][ns->y] == 6) {
			mvaddstr((9 - ns->y) + 10, ns->x + 10, "O");
		}
		else {
			mvaddstr((9 - ns->y) + 10, ns->x + 10, " ");
		}
		move((9 - ns->y) + 10, ns->x + 10);
	}
	else {
		if (key == KEY_RIGHT) {//ゴールポールを右に移動する（移動したところは上塗り）
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
		else if (key == KEY_LEFT) {//ゴールポールを左に移動する（移動したところは上塗り）
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
void init_map(stage* ns) {//一度マップモードから離れた時にもう一度描画し直す
	int i, j;
	init_pair(0, COLOR_WHITE, COLOR_BLACK);	// 色1 は黒地に白文字
	init_pair(1, COLOR_WHITE, COLOR_RED);	// 色1 は赤地に白文字
	init_pair(2, COLOR_WHITE, COLOR_YELLOW);	// 色2 は黄地に白文字
	init_pair(3, COLOR_WHITE, COLOR_GREEN);	// 色3 は黄地に白文字
	init_pair(4, COLOR_WHITE, COLOR_WHITE);	// 色4 は白地に白文字
	init_pair(5, COLOR_WHITE, COLOR_MAGENTA);	// 色5 はマゼンタ地に白文字
	init_pair(6, COLOR_WHITE, COLOR_RED);	// 色6 は赤地に白文字
	init_pair(7, COLOR_WHITE, COLOR_BLUE);	// 色7 は青地に白文字
	init_pair(10, COLOR_WHITE, COLOR_WHITE);	// 色2 は黄地に白文字
	init_pair(11, COLOR_YELLOW, COLOR_RED);	// 色2 は黄地に白文字
	init_pair(12, COLOR_YELLOW, COLOR_GREEN);	// 色2 は黄地に白文字
	for (i = 0; i < 100; i++) {
		for (j = 0; j < 10; j++) {
			attrset(COLOR_PAIR(ns->map[i][j]));			// 色1 を使う
			if (ns->map[i][j] == 6) {
				mvaddstr((9 - ns->y) + 10, ns->x + 10, "O");
			}
			else {
				mvaddstr((9 - ns->y) + 10, ns->x + 10, " ");
			}
			mvaddstr((9 - j) + 10, i + 10, " ");
			move((9 - i) + 10, j + 10);
		}
	}
}
bool Passing(int a,int state,stage* st) {//当たり判定
	bool judge=false;
	if (a == 0 || a == 3||a==4 || (a == 6 && st->on_off_switch == false) || (a == 7 && st->on_off_switch == true)) {
		if (a == 3 && (state == 0||state==10)) {
		}
		else {
			judge = true;
		}
	}
	return judge;
}
bool PassingIby(int a,stage* st) {//当たり判定（蔦を掴むとき）
	bool judge = false;
	if (a == 0 || a == 3||a==4|| (a == 6 && st->on_off_switch == false) || (a == 7 && st->on_off_switch == true)) {
		judge = true;
	}
	return judge;
}
bool PassingCloud(stage* st,character* c) {//当たり判定（雲に乗る時）
	bool judge = true;
	if (st->map[(st->x + c->x) / 16][(st->y + c->y - 17) / 16] == 4 || st->map[(st->x + c->x + 15) / 16][(st->y + c->y - 17) / 16] == 4) {
		if (st->map[(st->x + c->x) / 16][(st->y + c->y - 15) / 16] != 4 && st->map[(st->x + c->x + 15) / 16][(st->y + c->y - 15) / 16] != 4) {
			judge = false;
		}
	}
	return judge;
}
bool switch_change(int a) {//ON/OFFスイッチを切り替える
	bool judge = false;
	if (a == 5) {
		judge = true;
	}
	return judge;
}
bool Q_push(int a) {//？ブロックを押す
	bool judge = false;
	if (a == 2) {
		judge = true;
	}
	return judge;
}
