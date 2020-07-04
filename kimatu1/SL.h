#pragma once
void CSV_read(const char*);
void ini_read(const char*, int data[100][10]);
void ini_write(const char* , int data[100][10]);
bool save_map(int,const char*, int data[100][10]);
void load_map(int, int data[100][10]);