#ifndef _GAME_H_
#define _GAME_H_
typedef unsigned short hword;		// Half word (2 bytes)
typedef struct {
	int prev_state;
	int count;
	int key1;
	int key;
	bool save_mode;
	bool load_mode;
	int mode;
	int mode_select;
} command;
typedef struct {
	hword x;		/* x coordinate for point */
	hword y;		/* y coordinate for point */
	int map[100][10];
	bool goal_mode;
	bool on_off_switch;
} stage;
typedef struct {
	hword mode;
	hword x;		/* x coordinate for point */
	hword y;		/* y coordinate for point */
	/*hword MAX_HP;
	hword HP;
	hword Attack;
	hword A_flag;
	hword type;
	hword dot_status[16][16];
	*/
	hword j_count;
	hword jump;
	hword j_time;
	bool goal_flag;
	int coin;
} character;
void make_character(unsigned char dot[16][16],character*,stage*);
int key_operation(int,int,character*,stage*);
void make_obj(int,int,unsigned char obj[16][16], stage*,chtype);
void make_sword(int,int, unsigned char obj[16][16], stage*);
void make_stage(stage*);
void add_dot();
void make_map(int,stage*);
void init_map(stage* );
bool Passing(int,int,stage*);
bool PassingIby(int,stage*);
bool PassingCloud(stage*,character*);
bool switch_change(int);
bool Q_push(int a);
#endif
