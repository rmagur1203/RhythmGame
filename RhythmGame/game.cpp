#define _CRT_SECURE_NO_WARNINGS
#include "game.h"
#include "treasury.h"

int prev;
double begin;
bool touched[] = { false, false, false, false };

const char borderline[] = "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■";
const char emptyline[] = "■                           ㅣ                           ■\n";

bool noteList[59][4];

std::deque<double> k0note;
std::deque<double> k1note;
std::deque<double> k2note;
std::deque<double> k3note;

void CreateNoteLine(char* line, int index) {
	memset(line, '\0', 255);
	strcpy(line, "■ ");
	strcpy(&line[strlen(line)], noteList[index][0] ? "-〓〓◆〓〓-" : "            ");
	strcpy(&line[strlen(line)], "  ");
	strcpy(&line[strlen(line)], noteList[index][1] ? "-〓〓◆〓〓-" : "            ");
	strcpy(&line[strlen(line)], "ㅣ");
	strcpy(&line[strlen(line)], noteList[index][2] ? "-〓〓◆〓〓-" : "            ");
	strcpy(&line[strlen(line)], "  ");
	strcpy(&line[strlen(line)], noteList[index][3] ? "-〓〓◆〓〓-" : "            ");
	strcpy(&line[strlen(line)], " ■\n");
}

void CreateTouchLine(char* line) {
	memset(line, '\0', 255);
	strcpy(line, "■ ");
	strcpy(&line[strlen(line)], touched[0] ? "●●●●●●" : "○○○○○○");
	strcpy(&line[strlen(line)], "ㅣ");
	strcpy(&line[strlen(line)], touched[1] ? "●●●●●●" : "○○○○○○");
	strcpy(&line[strlen(line)], "ㅣ");
	strcpy(&line[strlen(line)], touched[2] ? "●●●●●●" : "○○○○○○");
	strcpy(&line[strlen(line)], "ㅣ");
	strcpy(&line[strlen(line)], touched[3] ? "●●●●●●" : "○○○○○○");
	strcpy(&line[strlen(line)], " ■\n");
}

void Drop() {
	int now = (timeGetTime() * 2) / 100;
	if (prev != now) {
		prev = now;
		for (int y = 57; y >= 0; y--) {
			for (int x = 0; x < 4; x++) {
				noteList[y + 1][x] = noteList[y][x];
			}
		}
		for (int x = 0; x < 4; x++) {
			noteList[0][x] = noteList[58][x];
		}
		//memset(noteList, false, 4);
	}
}

void DrawGame() {
    char tempStr[255];
    memset(screenText, '\0', 32767);
	sprintf(&screenText[strlen(screenText)], borderline);
	for (int i = 1; i < GAME_SCREEN_HEIGHT - 9; i++) {
		CreateNoteLine(tempStr, i - 1);
		sprintf(&screenText[strlen(screenText)], tempStr);
	}
	char keyline[255];
	CreateTouchLine(keyline);
	sprintf(&screenText[strlen(screenText)], keyline); // 52
	sprintf(&screenText[strlen(screenText)], keyline); // 53
	for (int i = 54; i < GAME_SCREEN_HEIGHT; i++) {
		CreateNoteLine(tempStr, i - 1);
		sprintf(&screenText[strlen(screenText)], tempStr);
	}
	sprintf(&screenText[strlen(screenText)], borderline); // 60
    ScreenClear();
}

// Mixer settings
// 컴퓨터\HKEY_CURRENT_USER\Software\Microsoft\Internet Explorer\LowRegistry\Audio\PolicyConfig\PropertyStore\57ff2ba1_0

void GamePlay(const int musicIndex) {
	ScreenRelease();
	char str[255];
	sprintf_s(str, sizeof(str), "mode con cols=%d lines=%d", GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
	system(str);
	ScreenInit();
	timeBeginPeriod(1);


	begin = timeGetTime();
	memset(noteList, false, 4 * 59);
	
	switch (musicIndex) {
	case 0:
		PlaySound(TEXT("music_0.wav"), NULL, SND_NODEFAULT | SND_ASYNC);
		break;
	}
	noteList[0][0] = true;
	// 재생까지 3초 딜레이
	while (true) {
		Drop();
		DrawGame();
		ScreenPrint(0, 0, screenText);
		ScreenFlipping();

		double time = (timeGetTime() - begin) / 1000;

		short key0 = 0, key1 = 0, key2 = 0, key3 = 0;
		if (KeyList[0] >= '0' && KeyList[0] <= '9')
			key0 = GetAsyncKeyState(KeyList[0] + 48);
		else if (KeyList[0] >= 'a' && KeyList[0] <= 'z')
			key0 = GetAsyncKeyState(KeyList[0] - 32);

		if (KeyList[1] >= '0' && KeyList[1] <= '9')
			key1 = GetAsyncKeyState(KeyList[1] + 48);
		else if (KeyList[1] >= 'a' && KeyList[1] <= 'z')
			key1 = GetAsyncKeyState(KeyList[1] - 32);

		if (KeyList[2] >= '0' && KeyList[2] <= '9')
			key2 = GetAsyncKeyState(KeyList[2] + 48);
		else if (KeyList[2] >= 'a' && KeyList[2] <= 'z')
			key2 = GetAsyncKeyState(KeyList[2] - 32);
		
		if (KeyList[3] >= '0' && KeyList[3] <= '9')
			key3 = GetAsyncKeyState(KeyList[3] + 48);
		else if (KeyList[3] >= 'a' && KeyList[3] <= 'z')
			key3 = GetAsyncKeyState(KeyList[3] - 32);

		touched[0] = key0 & 0x8000;
		touched[1] = key1 & 0x8000;
		touched[2] = key2 & 0x8000;
		touched[3] = key3 & 0x8000;
		if (_kbhit()) {
			int key_code = _getch();
			if (key_code == 27)
				break;
		}

		if (time > (double)3 * 60 + 39) {
			break;
		}
	}
	timeEndPeriod(1);
	PlaySound(NULL, NULL, SND_PURGE);
	ScreenRelease();
	sprintf_s(str, sizeof(str), "mode con cols=%d lines=%d", MENU_SCREEN_WIDTH, MENU_SCREEN_HEIGHT);
	system(str);
	ScreenInit();
}