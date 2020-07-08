#include "SL.h"
#include "Setting.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFSIZE 1024

void CSV_read(const char* filename) {
	FILE* fp;
	int data[100][10];
	int i = 0;
	int j = 0;
	int count = 0;
	char s[BUFFSIZE];
	char* p1; // char型ポインタワーク
	char delim[] = ", ";
	char* ctx;
	errno_t error;
	error = fopen_s(&fp, filename, "r");
	if (error != 0)
		fprintf_s(stderr, "failed to open");
	else {
		if (fgets(s, BUFFSIZE, fp) != NULL);
		while (fgets(s, BUFFSIZE, fp) != NULL) {
			p1 = strtok_s(s, delim, &ctx);
			data[i][j] = atoi(p1);
			j++;
			while (p1 != NULL) {
				p1 = strtok_s(NULL, delim, &ctx); // 2個目以降の部分文字列取得
				if (p1 != NULL) {
					data[i][j] = atoi(p1);
					j++;
				}
			}
			i++;
			j = 0;
		}
		fclose(fp);
	}
	char currentDirectory[CHARBUFF];
	getCurrentDirectory(currentDirectory);
	char section[CHARBUFF];
	char keyword[CHARBUFF];
	char file[CHARBUFF];
	char settingFile[CHARBUFF];
	sprintf_s(file, "%s", "stage.ini");
	sprintf_s(settingFile, "%s\\%s", currentDirectory, file);
	error = fopen_s(&fp, file, "w");
	if (error != 0)
		fprintf_s(stderr, "failed to open");
	else {
		fclose(fp);
	}
	for (i = 0; i < 100; i++) {
		for (j = 0; j < 10; j++) {
			sprintf_s(section, "%d", i);
			sprintf_s(keyword, "%d", j);
			if (writeInt(section, keyword, data[i][j], settingFile));
		}
	}
}
void ini_read(const char* filename, int data[100][10]) {
	int i, j;
	char currentDirectory[CHARBUFF];
	getCurrentDirectory(currentDirectory);
	char section[CHARBUFF];
	char keyword[CHARBUFF];
	char settingFile[CHARBUFF];
	sprintf_s(settingFile, "%s\\%s", currentDirectory, filename);
	for (i = 0; i < 100; i++) {
		for (j = 0; j < 10; j++) {
			sprintf_s(section, "%d", i);
			sprintf_s(keyword, "%d", j);
			data[i][j] = readInt(section, keyword, -1, settingFile);
		}
	}
}
void ini_write(const char* filename, int data[100][10]) {
	if (filename != "stage.ini") {
		int i, j;
		char currentDirectory[CHARBUFF];
		getCurrentDirectory(currentDirectory);
		char section[CHARBUFF];
		char keyword[CHARBUFF];
		char settingFile[CHARBUFF];
		sprintf_s(settingFile, "%s\\%s", currentDirectory, filename);
		for (i = 0; i < 100; i++) {
			for (j = 0; j < 10; j++) {
				sprintf_s(section, "%d", i);
				sprintf_s(keyword, "%d", j);
				writeInt(section, keyword, data[i][j], settingFile);
			}
		}
	}
}
bool save_map(int num,const char* filename, int data[100][10]) {
	bool flag = true;
	if (filename == "savefile" || filename == "stage") {
		flag = false;
	}
	else {
		char currentDirectory[CHARBUFF];
		getCurrentDirectory(currentDirectory);
		char section[CHARBUFF];
		char keyword[CHARBUFF];
		char settingFile[CHARBUFF];
		sprintf_s(settingFile, "%s\\%s", currentDirectory, "savefile.ini");
		sprintf_s(section, "%d", num + 1);
		sprintf_s(keyword, "セーブ%d",num+1 );
		writeChar(section, keyword, filename, settingFile);
		char newFile[CHARBUFF];
		sprintf_s(newFile, "%s%s", filename, ".ini");
		ini_write(newFile, data);
	}
	return flag;
}
void load_map(int num,int data[100][10]) {
	char filename[CHARBUFF];
	char currentDirectory[CHARBUFF];
	getCurrentDirectory(currentDirectory);
	char section[CHARBUFF];
	char keyword[CHARBUFF];
	char settingFile[CHARBUFF];
	sprintf_s(settingFile, "%s\\%s", currentDirectory, "savefile.ini");
	sprintf_s(section, "%d", num + 1);
	sprintf_s(keyword, "セーブ%d", num + 1);
	readChar(section, keyword, NULL,filename, settingFile);
	sprintf_s(filename, "%s%s", filename, ".ini");
	ini_read(filename, data);
}
int param_init(const char* section, const char* keyword) {
	char currentDirectory[CHARBUFF];
	getCurrentDirectory(currentDirectory);
	char settingFile[CHARBUFF];
	sprintf_s(settingFile, "%s\\%s", currentDirectory, "Initilize.ini");
	return readInt(section, keyword, -1, settingFile);
}