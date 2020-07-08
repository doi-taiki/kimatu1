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
	init_pair(0, COLOR_WHITE, COLOR_BLACK);	// �F1 �͍��n�ɔ�����
	init_pair(1, COLOR_WHITE, COLOR_GREEN);	// �F1 �͗Βn�ɔ�����
	init_pair(2, COLOR_WHITE, COLOR_YELLOW);	// �F2 �͉��n�ɔ�����
	init_pair(3, COLOR_WHITE, COLOR_RED);	// �F3 �͐Ԓn�ɔ�����
	init_pair(4, COLOR_WHITE, COLOR_BLUE);	// �F4 �͐n�ɔ�����
	init_pair(5, COLOR_WHITE, COLOR_CYAN);	// �F5 �̓V�A���n�ɔ�����
	init_pair(6, COLOR_WHITE, COLOR_WHITE);	// �F6 �͔��n�ɔ�����
	for (i = 0; i < 16; i++) {
		move(30 - c->y + i, c->x);
		for (j = 0; j < 16; j++) {
			if (i - c->y < 0) {
				if (dot[i][j] == 1) {
					attrset(COLOR_PAIR(1));			// �F1 ���g��
				}
				else if (dot[i][j] == 2) {
					attrset(COLOR_PAIR(2));			// �F2 ���g��
				}
				else if (dot[i][j] == 3) {
					attrset(COLOR_PAIR(3));			// �F1 ���g��
				}
				else if (dot[i][j] == 4) {
					attrset(COLOR_PAIR(4));			// �F1 ���g��
				}
				else if (dot[i][j] == 5) {
					attrset(COLOR_PAIR(5));			// �F2 ���g��
				}
				else if (dot[i][j] == 6) {
					attrset(COLOR_PAIR(6));			// �F1 ���g��
				}
				else {
					attrset(COLOR_PAIR(0));
				}
				addch(0x20);
			}
		}
	}
}
int key_operation(int key,int prev_state,character* c,stage* st) {//�L�[����ŃL�����N�^�[�𓮂���
	int state=prev_state;
	switch (prev_state) {//�L�[���삪���������ꍇ�A�O�̏�Ԃ�ێ�����
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
	case KEY_UP://�オ�����ꂽ�ꍇ
		if (prev_state != 0) {//��Ԃ�������ɂ���
			state = 0;
			make_character(LdotU_N, c, st);
		}
		else {
			state = 10;
			make_character(LdotU2_N, c, st);
		}
		if (PassingIby(st->map[(st->x + c->x) / 16][(st->y + c->y) / 16],st) && PassingIby(st->map[(st->x + c->x + 15) / 16][(st->y + c->y) / 16],st)) {//�j�}�X�̃u���b�N���ʂ蔲�����邩�ǂ���
			if (Passing(st->map[(st->x + c->x) / 16][(st->y + c->y) / 16], state,st) && Passing(st->map[(st->x + c->x + 15) / 16][(st->y + c->y) / 16], state,st)&& Passing(st->map[(st->x + c->x) / 16][(st->y + c->y-15) / 16], state,st) && Passing(st->map[(st->x + c->x + 15) / 16][(st->y + c->y-15) / 16], state,st)) {//�j�}�X��̃u���b�N���������Ԋ��ӂ̏ꍇ�͒ӂ�͂�
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
		else if (PassingIby(st->map[(st->x + c->x) / 16][(st->y + c->y - 1) / 16],st) && PassingIby(st->map[(st->x + c->x + 15) / 16][(st->y + c->y - 1) / 16],st)) {//��}�X�̃u���b�N���ʂ蔲�����邩�ǂ���
			if (Passing(st->map[(st->x + c->x) / 16][(st->y + c->y) / 16], state,st) && Passing(st->map[(st->x + c->x + 15) / 16][(st->y + c->y) / 16], state,st) && Passing(st->map[(st->x + c->x) / 16][(st->y + c->y - 15) / 16], state,st) && Passing(st->map[(st->x + c->x + 15) / 16][(st->y + c->y - 15) / 16], state,st)) {//��}�X��̃u���b�N���������Ԋ��ӂ̏ꍇ�͒ӂ�͂�
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
	case KEY_DOWN://�����蔻��͏�����������Ɠ���
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
	case KEY_LEFT://�����蔻��͏�����������Ɠ���
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
	case KEY_RIGHT://�����蔻��͏�����������Ɠ���
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
		switch (prev_state) {//���̕`��E�����蔻��͓����蔼��̂��钸�_4�}�X�𒲂ׂ�
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
	if (c->jump > 0) {//�W�����v�ŏ�ɏオ���
		if (c->j_count > 0) {//�W�����v�̑��x����
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
				if (Q_push(st->map[(st->x + c->x) / 16][(st->y + c->y) / 16]) ) {//�}�b�v��y���W�͈��̍�����ۂ̂ŏ������݃G���[�͋N����Ȃ�
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
	else if ((Passing(st->map[(st->x + c->x) / 16][(st->y + c->y-17) / 16], state,st) && Passing(st->map[(st->x + c->x + 15) / 16][(st->y + c->y-17) / 16],state,st))&& PassingCloud(st,c)) {//��������
		if (c->j_count > 0) {//�������x����
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
					state = 100;//�Q�[���I�[�o�[
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
void make_obj(int m,int n,unsigned char obj[16][16],stage* st,chtype on_off_color) {//�u���b�N�̎�ނɉ������h�b�g���o�͂���
	int i = 0;
	int j = 0;
	start_color();
	init_pair(0, COLOR_WHITE, COLOR_BLACK);	// �F0 �͍��n�ɔ�����
	init_pair(1, COLOR_WHITE, COLOR_GREEN);	// �F1 �͗Βn�ɔ�����
	init_pair(2, COLOR_WHITE, COLOR_YELLOW);	// �F2 �͉��n�ɔ�����
	init_pair(3, COLOR_WHITE, COLOR_RED);	// �F3 �͐Ԓn�ɔ�����
	init_pair(4, COLOR_WHITE, COLOR_BLUE);	// �F4 �͐n�ɔ�����
	init_pair(5, COLOR_WHITE, COLOR_CYAN);	// �F5 �̓V�A���n�ɔ�����
	init_pair(6, COLOR_WHITE, COLOR_WHITE);	// �F6 �͔��n�ɔ�����
	for (i = 0; i < 16; i++) {
		for (j = 0; j < 16; j++) {
			if (obj[i][j] == 1) {
				attrset(COLOR_PAIR(1));			// �F1 ���g��
			}
			else if (obj[i][j] == 2) {
				attrset(COLOR_PAIR(2));			// �F2 ���g��
			}
			else if (obj[i][j] == 3) {
				attrset(COLOR_PAIR(3));			// �F3 ���g��
			}
			else if (obj[i][j] == 4) {
				attrset(COLOR_PAIR(4));			// �F4 ���g��
			}
			else if (obj[i][j] == 5) {
				attrset(COLOR_PAIR(5));			// �F5 ���g��
			}
			else if (obj[i][j] == 6) {
				attrset(COLOR_PAIR(6));			// �F6 ���g��
			}
			else if(obj[i][j] == 7){
				if (on_off_color==COLOR_RED) {
					attrset(COLOR_PAIR(3));			// �F6 ���g��
				}
				else if (on_off_color == COLOR_BLUE) {
					attrset(COLOR_PAIR(4));			// �F6 ���g��
				}
			}
			else {
				attrset(COLOR_PAIR(0));
			}
			mvaddstr(14-n*16+st->y+i, (m*16-st->x) + j, " ");
		}
	}
}
void make_sword(int m, int n, unsigned char obj[16][16], stage* st) {//����`�悷��
	int i = 0;
	int j = 0;
	start_color();
	init_pair(0, COLOR_WHITE, COLOR_BLACK);	// �F1 �͍��n�ɔ�����
	init_pair(1, COLOR_WHITE, COLOR_GREEN);	// �F1 �͗Βn�ɔ�����
	init_pair(2, COLOR_WHITE, COLOR_YELLOW);	// �F2 �͉��n�ɔ�����
	init_pair(3, COLOR_WHITE, COLOR_RED);	// �F3 �͐Ԓn�ɔ�����
	init_pair(4, COLOR_WHITE, COLOR_BLUE);	// �F4 �͐n�ɔ�����
	init_pair(5, COLOR_WHITE, COLOR_CYAN);	// �F5 �̓V�A���n�ɔ�����
	init_pair(6, COLOR_WHITE, COLOR_WHITE);	// �F6 �͔��n�ɔ�����
	for (i = 0; i < 16; i++) {
		for (j = 0; j < 16; j++) {
			if (obj[i][j] == 1) {
				attrset(COLOR_PAIR(1));			// �F1 ���g��
			}
			else if (obj[i][j] == 2) {
				attrset(COLOR_PAIR(2));			// �F2 ���g��
			}
			else if (obj[i][j] == 3) {
				attrset(COLOR_PAIR(6));			// �F3 ���g��
			}
			else if (obj[i][j] == 4) {
				attrset(COLOR_PAIR(4));			// �F3 ���g��
			}
			else if (obj[i][j] == 5) {
				attrset(COLOR_PAIR(5));			// �F3 ���g��
			}
			else if (obj[i][j] == 6) {
				attrset(COLOR_PAIR(6));			// �F3 ���g��
			}
			else {
				attrset(COLOR_PAIR(0));
			}
			mvaddstr(30-n + i, m + j, " ");
		}
	}
}
void make_stage(stage* st) {//�}�b�v�̂����W�Ƃ����W���獡��ʏ�ɏo�Ă�u���b�N����ʏ�ɕ`�悷��
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
void add_dot(void) {//�t�����┽�]�����h�b�g��������
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
void make_map(int key, stage* ns) {//��郂�[�h�Ń}�b�v���쐬����
	int i;
	switch(key) {//�S�[���|�[���𓮂����Ȃ����̓J�[�\�����ړ�����
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
			if (ns->map[ns->x][ns->y] < 10) {//�S�[���|�[���ł͂Ȃ���
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
	init_pair(0, COLOR_WHITE, COLOR_BLACK);	// �F1 �͍��n�ɔ�����
	init_pair(1, COLOR_WHITE, COLOR_RED);	// �F1 �͐Ԓn�ɔ�����
	init_pair(2, COLOR_WHITE, COLOR_YELLOW);	// �F2 �͉��n�ɔ�����
	init_pair(3, COLOR_WHITE, COLOR_GREEN);	// �F3 �͗Βn�ɔ�����
	init_pair(4, COLOR_WHITE, COLOR_WHITE);	// �F4 �͔��n�ɔ�����
	init_pair(5, COLOR_WHITE, COLOR_MAGENTA);	// �F5 �̓}�[���^�n�ɔ�����
	init_pair(6, COLOR_WHITE, COLOR_RED);	// �F6 �͐Ԓn�ɔ�����
	init_pair(7, COLOR_WHITE, COLOR_BLUE);	// �F7 �͐n�ɔ�����
	init_pair(10, COLOR_WHITE, COLOR_WHITE);	// �F2 �͉��n�ɔ�����
	init_pair(11, COLOR_YELLOW, COLOR_RED);	// �F2 �͉��n�ɔ�����
	init_pair(12, COLOR_YELLOW, COLOR_GREEN);	// �F2 �͉��n�ɔ�����
	if (ns->goal_mode == false) {
		attrset(COLOR_PAIR(ns->map[ns->x][ns->y]));			// �F1 ���g��
		if (ns->map[ns->x][ns->y] == 6) {
			mvaddstr((9 - ns->y) + 10, ns->x + 10, "O");
		}
		else {
			mvaddstr((9 - ns->y) + 10, ns->x + 10, " ");
		}
		move((9 - ns->y) + 10, ns->x + 10);
	}
	else {
		if (key == KEY_RIGHT) {//�S�[���|�[�����E�Ɉړ�����i�ړ������Ƃ���͏�h��j
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
					attrset(COLOR_PAIR(ns->map[ns->x][i]));			// �F1 ���g��
					mvaddstr((9 - i) + 10, ns->x + 10, " ");
					attrset(COLOR_PAIR(ns->map[ns->x+1][i]));			// �F1 ���g��
					mvaddstr((9 - i) + 10, ns->x + 11, " ");
					move((9 - i) + 10, ns->x + 11);
				}
				ns->x++;
			}
		}
		else if (key == KEY_LEFT) {//�S�[���|�[�������Ɉړ�����i�ړ������Ƃ���͏�h��j
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
					attrset(COLOR_PAIR(ns->map[ns->x][i]));			// �F1 ���g��
					mvaddstr((9 - i) + 10, ns->x + 10, " ");
					attrset(COLOR_PAIR(ns->map[ns->x - 1][i]));			// �F1 ���g��
					mvaddstr((9 - i) + 10, ns->x + 9, " ");
					move((9 - i) + 10, ns->x + 9);
				}
				ns->x--;
			}
		}
	}
}
void init_map(stage* ns) {//��x�}�b�v���[�h���痣�ꂽ���ɂ�����x�`�悵����
	int i, j;
	init_pair(0, COLOR_WHITE, COLOR_BLACK);	// �F1 �͍��n�ɔ�����
	init_pair(1, COLOR_WHITE, COLOR_RED);	// �F1 �͐Ԓn�ɔ�����
	init_pair(2, COLOR_WHITE, COLOR_YELLOW);	// �F2 �͉��n�ɔ�����
	init_pair(3, COLOR_WHITE, COLOR_GREEN);	// �F3 �͉��n�ɔ�����
	init_pair(4, COLOR_WHITE, COLOR_WHITE);	// �F4 �͔��n�ɔ�����
	init_pair(5, COLOR_WHITE, COLOR_MAGENTA);	// �F5 �̓}�[���^�n�ɔ�����
	init_pair(6, COLOR_WHITE, COLOR_RED);	// �F6 �͐Ԓn�ɔ�����
	init_pair(7, COLOR_WHITE, COLOR_BLUE);	// �F7 �͐n�ɔ�����
	init_pair(10, COLOR_WHITE, COLOR_WHITE);	// �F2 �͉��n�ɔ�����
	init_pair(11, COLOR_YELLOW, COLOR_RED);	// �F2 �͉��n�ɔ�����
	init_pair(12, COLOR_YELLOW, COLOR_GREEN);	// �F2 �͉��n�ɔ�����
	for (i = 0; i < 100; i++) {
		for (j = 0; j < 10; j++) {
			attrset(COLOR_PAIR(ns->map[i][j]));			// �F1 ���g��
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
bool Passing(int a,int state,stage* st) {//�����蔻��
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
bool PassingIby(int a,stage* st) {//�����蔻��i�ӂ�͂ނƂ��j
	bool judge = false;
	if (a == 0 || a == 3||a==4|| (a == 6 && st->on_off_switch == false) || (a == 7 && st->on_off_switch == true)) {
		judge = true;
	}
	return judge;
}
bool PassingCloud(stage* st,character* c) {//�����蔻��i�_�ɏ�鎞�j
	bool judge = true;
	if (st->map[(st->x + c->x) / 16][(st->y + c->y - 17) / 16] == 4 || st->map[(st->x + c->x + 15) / 16][(st->y + c->y - 17) / 16] == 4) {
		if (st->map[(st->x + c->x) / 16][(st->y + c->y - 15) / 16] != 4 && st->map[(st->x + c->x + 15) / 16][(st->y + c->y - 15) / 16] != 4) {
			judge = false;
		}
	}
	return judge;
}
bool switch_change(int a) {//ON/OFF�X�C�b�`��؂�ւ���
	bool judge = false;
	if (a == 5) {
		judge = true;
	}
	return judge;
}
bool Q_push(int a) {//�H�u���b�N������
	bool judge = false;
	if (a == 2) {
		judge = true;
	}
	return judge;
}
