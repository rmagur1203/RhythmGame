#include "menu.h"

void Settings();
void Musics();

void CreateLine(char string[], int length) {
	const int size = MENU_SCREEN_WIDTH - 4;
	memset(string, '\0', MENU_SCREEN_WIDTH + 1);
	strcpy(string, "│ ");
	memset(&string[strlen(string)], ' ', (size - length) / 2);
	strcpy(&string[strlen(string)], "%s");
	memset(&string[strlen(string)], ' ', (size - length) / 2);
	strcpy(&string[strlen(string)], "│\n");
}

void CreateLine(char string[], int length, bool selected) {
	const int size = MENU_SCREEN_WIDTH - 4;
	memset(string, '\0', 61);
	strcpy(string, "│ ");
	if (selected) {
		memset(&string[strlen(string)], ' ', (size - length) / 2 - 2);
		memset(&string[strlen(string)], '>', 1);
		memset(&string[strlen(string)], ' ', 1);
	}
	else {
		memset(&string[strlen(string)], ' ', (size - length) / 2);
	}
	strcpy(&string[strlen(string)], "%s");
	memset(&string[strlen(string)], ' ', (size - length) / 2);
	strcpy(&string[strlen(string)], "│\n");
}

const char* CreateRotateString(const char* text) {
	int length = strlen(text);
	char* string = (char*)malloc(sizeof(char) * length * 3 + 1);
	if (string == nullptr)
		return "에러 발생";
	strcpy(string, text);
	memset(string + length, ' ', length); // Heap Corruption?
	strcpy(string + length * 2, text);
	string[length * 3] = '\00';
	return string;
}

void DrawMainMenu(const char* rotate_str, const char* title, const int SubTitleLength, const int TitleLength, int &rotate_index, int &selected_index) {
	char tempStr[255];
	memset(screenText, '\0', 32767);
	ScreenClear();

	char new_str[255];
	rotate_index = (int)((double)timeGetTime() / 1000 * 12) % (SubTitleLength * 2);
	strcpy(new_str, rotate_str + rotate_index);
	new_str[SubTitleLength] = '\00';

	sprintf(&screenText[strlen(screenText)], header_line); // 0
	sprintf(&screenText[strlen(screenText)], empty_line); // 1
	CreateLine(tempStr, TitleLength);
	sprintf(&screenText[strlen(screenText)], tempStr, title); // 2
	CreateLine(tempStr, SubTitleLength);
	sprintf(&screenText[strlen(screenText)], tempStr, new_str); // 3
	for (int i = 4; i < 28 - 2; i++)
		sprintf(&screenText[strlen(screenText)], empty_line); // 4~25
	CreateLine(tempStr, 4, (selected_index == 0));
	sprintf(&screenText[strlen(screenText)], tempStr, "시작"); // 26
	CreateLine(tempStr, 4, (selected_index == 1));
	sprintf(&screenText[strlen(screenText)], tempStr, "설정"); // 27
	sprintf(&screenText[strlen(screenText)], empty_line); // 28
	sprintf(&screenText[strlen(screenText)], footer_line); //29
}

void MainMenu() {
	ScreenInit();
	double begin = timeGetTime();

	const int TitleLength = strlen("Moderato");
	const char* title = "Moderato";
	const int SubTitleLength = strlen("Single Player Version ");
	const char* rotate_str = CreateRotateString("Single Player Version ");
	int rotate_index = 0;
	int selected_index = 0;

	bool selected = false;
	while(!selected){
		DrawMainMenu(rotate_str, title, SubTitleLength, TitleLength, rotate_index, selected_index);
		if (_kbhit()) {
			int key_code = _getch();
			if (key_code == 72 && selected_index > 0) // arrow up
				selected_index--;
			if (key_code == 80 && selected_index < 1) // arrow down
				selected_index++;

			if (key_code == 13) { // enter
				switch (selected_index) {
				case 0:
					Musics();
					break;
				case 1:
					Settings();
					break;
				}
			}
		}
		ScreenPrint(0, 0, screenText);
		ScreenFlipping();
	}
}

void DrawSettings(int& selected_index, bool& wait_key_select) {
	char tempStr[255];
	memset(screenText, '\0', 32767);
	ScreenClear();

	double second = (double)timeGetTime() / 1000;

	sprintf(&screenText[strlen(screenText)], header_line); // 0
	sprintf(&screenText[strlen(screenText)], empty_line); // 1
	CreateLine(tempStr, 4);
	sprintf(&screenText[strlen(screenText)], tempStr, "설정"); // 2
	sprintf(&screenText[strlen(screenText)], empty_line); // 3
	sprintf(&screenText[strlen(screenText)], empty_line); // 4
	sprintf(&screenText[strlen(screenText)], empty_line); // 5

	bool cursor = (int)(second * 2) % 2;
	char keystr[255];
	sprintf(keystr, "Key 1: %c", KeyList[0]);
	CreateLine(tempStr, 8, (selected_index == 0 && (cursor || !wait_key_select)));
	sprintf(&screenText[strlen(screenText)], tempStr, keystr); // 6
	sprintf(keystr, "Key 2: %c", KeyList[1]);
	CreateLine(tempStr, 8, (selected_index == 1 && (cursor || !wait_key_select)));
	sprintf(&screenText[strlen(screenText)], tempStr, keystr); // 7
	sprintf(keystr, "Key 3: %c", KeyList[2]);
	CreateLine(tempStr, 8, (selected_index == 2 && (cursor || !wait_key_select)));
	sprintf(&screenText[strlen(screenText)], tempStr, keystr); // 8
	sprintf(keystr, "Key 4: %c", KeyList[3]);
	CreateLine(tempStr, 8, (selected_index == 3 && (cursor || !wait_key_select)));
	sprintf(&screenText[strlen(screenText)], tempStr, keystr); // 9
	sprintf(&screenText[strlen(screenText)], empty_line); // 10
	sprintf(keystr, "Sync: %lf", syncSetting);
	CreateLine(tempStr, strlen(keystr), (selected_index == 4 && (cursor || !wait_key_select)));
	sprintf(&screenText[strlen(screenText)], tempStr, keystr); // 11
	for (int i = 12; i < 29; i++)
		sprintf(&screenText[strlen(screenText)], empty_line); // 12~28
	sprintf(&screenText[strlen(screenText)], footer_line); //29
}

void Settings() {
	const int selected_max = 4;
	int selected_index = 0;
	bool wait_key_select = false;
	while (true) {
		DrawSettings(selected_index, wait_key_select);
		ScreenPrint(0, 0, screenText);
		ScreenFlipping();
		if (_kbhit()) {
			int key_code = _getch();

			if (!wait_key_select) {
				if (key_code == 72 && selected_index > 0) // arrow up
					selected_index--;
				if (key_code == 80 && selected_index < selected_max) // arrow down
					selected_index++;
			}
			else {
				if (key_code >= '0' && key_code <= '9')
					KeyList[selected_index] = key_code;
				if (key_code >= 'a' && key_code <= 'z')
					KeyList[selected_index] = key_code;
				//if (key_code >= 'A' && key_code <= 'Z')
				//	KeyList[selected_index] = key_code + ('a' - 'A');
			}

			if (key_code == 13) {
				switch (selected_index) {
				case 0:
				case 1:
				case 2:
				case 3:
					wait_key_select = !wait_key_select;
					break;
				}
			}
			if (GetAsyncKeyState(0x25) & 0x8000) { //왼쪽 화살표
				if (selected_index == 4)
					syncSetting -= 0.005;
			}
			if (GetAsyncKeyState(0x27) & 0x8000) { //오른쪽 화살표
				if (selected_index == 4)
					syncSetting += 0.005;
			}
			if (key_code == 27)
				return;
		}
	}
}

void DrawMusics(int& selected_index, bool& wait_key_select) {
	char tempStr[255];
	memset(screenText, '\0', 32767);
	ScreenClear();

	double second = (double)timeGetTime() / 1000;

	sprintf(&screenText[strlen(screenText)], header_line); // 0
	sprintf(&screenText[strlen(screenText)], empty_line); // 1
	CreateLine(tempStr, 10);
	sprintf(&screenText[strlen(screenText)], tempStr, "음악  선택"); // 2
	sprintf(&screenText[strlen(screenText)], empty_line); // 3
	sprintf(&screenText[strlen(screenText)], empty_line); // 4
	sprintf(&screenText[strlen(screenText)], empty_line); // 5
	CreateLine(tempStr, 12, (selected_index == 0));
	sprintf(&screenText[strlen(screenText)], tempStr, "Bad Apple!! "); // 6

	for (int i = 7; i < 29; i++)
		sprintf(&screenText[strlen(screenText)], empty_line); // 11~28
	sprintf(&screenText[strlen(screenText)], footer_line); //29
}

void Musics() {
	const int selected_max = 0;
	int selected_index = 0;
	bool wait_key_select = false;
	while (true) {
		DrawMusics(selected_index, wait_key_select);
		ScreenPrint(0, 0, screenText);
		ScreenFlipping();
		if (_kbhit()) {
			int key_code = _getch();

			if (key_code == 72 && selected_index > 0) // arrow up
				selected_index--;
			if (key_code == 80 && selected_index < selected_max) // arrow down
				selected_index++;

			if (key_code == 13) {
				GamePlay(selected_index);
			}
			if (key_code == 27)
				return;
		}
	}
}