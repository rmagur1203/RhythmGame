#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <Windows.h>
#include <assert.h>
#include <conio.h>  // _kbhit(), _getch() �Լ� ����� ���� ���̺귯��

#include "consts.h"
#include "double_buffer.h"
#include "menu.h"

#pragma once
#pragma comment(lib, "winmm.lib") // timeGetTime() �Լ� ����� ���� ���̺귯��

using namespace std;

double speed = 2;
char KeyList[] = { 'a', 's', 'd', 'f' };
char screenText[65535];
//int main()
//{
//	timeBeginPeriod(1); // timer interrupt �ػ󵵸� 1�� ����ϴ�.
//
//	char pointList[4][256] = { // ���� ����Ʈ
//		{"Bad"},
//		{"NoGood"},
//		{"Good"},
//		{"Gread"},
//	};
//
//	int g_Timing[] = { 5, 10, 14, 17, 20, 25, 29, 34, 37 }; // Ÿ�̹�
//
//	char userPoint[9][256] = { {" "} }; // ������ ���� ����ϴ� �迭
//
//	double begin; // ó�� ���۽� �ð�
//
//	double end; // ���α׷� ���� �� �ݺ����ȿ��� üũ�� �ð�
//
//	double checkC; // begin - end ��
//
//	int tIndex = 0; // �������� üũ
//
//	begin = timeGetTime();
//
//	ScreenInit();
//	ScreenClear();
//
//	while (1) {
//		char screenText[32767];
//		memset(screenText, '\0', 32767);
//
//		end = timeGetTime();
//
//		checkC = (end - begin) / 1000; // ����ð� ���ϱ�
//
//		sprintf(&screenText[strlen(screenText)], "Ÿ�̸� : %.3f\n\n", checkC);
//
//		if (_kbhit()) {
//
//			// fabs�� double�� ���밪 ���ϴ� �Լ��Դϴ�.
//			if (fabs((double)g_Timing[tIndex] - checkC) >= (double)1) { // ���� �Է� �ð��� 1���̻� ���̳� ��� 
//				strcpy_s(userPoint[tIndex], strlen(pointList[0]) + 1, pointList[0]);
//			}
//
//			// 0.75���Ϸ� ���̳��� 0.5�� �ʰ��� ���̳����
//			else if (fabs((double)g_Timing[tIndex] - checkC) <= (double)0.75 && fabs((double)g_Timing[tIndex] - checkC) > (double)0.5) {
//				strcpy_s(userPoint[tIndex], strlen(pointList[1]) + 1, pointList[1]);
//
//			}
//
//			// 0.5���Ϸ� ���̳��� 0.25�� �ʰ��� ���̳����
//			else if (fabs((double)g_Timing[tIndex] - checkC) <= (double)0.5 && fabs((double)g_Timing[tIndex] - checkC) > (double)0.25) {
//				strcpy_s(userPoint[tIndex], strlen(pointList[2]) + 1, pointList[2]);
//
//			}
//			// 0.25 ���Ϸ� ���̳� ���
//			else if (fabs((double)g_Timing[tIndex] - checkC) <= (double)0.25) {
//				strcpy_s(userPoint[tIndex], strlen(pointList[3]) + 1, pointList[3]);
//			}
//
//			_getch(); // ���� ����
//			tIndex++; // �������� ���
//		}
//
//		// ������ �Է����� �ʾ��� ��� �ڵ����� Bad���� ����
//		if (checkC > 6 && tIndex == 0) {
//			strcpy_s(userPoint[tIndex], strlen(pointList[0]) + 1, pointList[0]);
//			tIndex++;
//		}
//		else if (checkC > 11 && tIndex == 1) {
//			strcpy_s(userPoint[tIndex], strlen(pointList[0]) + 1, pointList[0]);
//			tIndex++;
//		}
//		else if (checkC > 15 && tIndex == 2) {
//			strcpy_s(userPoint[tIndex], strlen(pointList[0]) + 1, pointList[0]);
//			tIndex++;
//		}
//		else if (checkC > 18 && tIndex == 3) {
//			strcpy_s(userPoint[tIndex], strlen(pointList[0]) + 1, pointList[0]);
//			tIndex++;
//		}
//		else if (checkC > 21 && tIndex == 4) {
//			strcpy_s(userPoint[tIndex], strlen(pointList[0]) + 1, pointList[0]);
//			tIndex++;
//		}
//		else if (checkC > (double)26 && tIndex == 5) {
//			strcpy_s(userPoint[tIndex], strlen(pointList[0]) + 1, pointList[0]);
//			tIndex++;
//		}
//		else if (checkC > (double)30 && tIndex == 6) {
//			strcpy_s(userPoint[tIndex], strlen(pointList[0]) + 1, pointList[0]);
//			tIndex++;
//		}
//		else if (checkC > (double)35 && tIndex == 7) {
//			strcpy_s(userPoint[tIndex], strlen(pointList[0]) + 1, pointList[0]);
//			tIndex++;
//		}
//		else if (checkC > (double)38 && tIndex == 8) {
//			strcpy_s(userPoint[tIndex], strlen(pointList[0]) + 1, pointList[0]);
//			tIndex++;
//			break;
//		}
//
//
//		for (int i = 0; i < 9; i++) { // ���� ���������� ������ ������ ���
//			sprintf(&screenText[strlen(screenText)], "%d Sec : %s\n", g_Timing[i], userPoint[i]);
//		}
//		ScreenPrint(0, 0, screenText);
//		ScreenFlipping();
//
//		if (tIndex == 9) // ���������� 8�� ������ ��� ����
//			break;
//
//		ScreenClear();
//	}
//
//	timeEndPeriod(1); // timer interrupt �ʱ�ȭ
//}

int main() {
	char str[255];
	sprintf_s(str, sizeof(str), "mode con cols=%d lines=%d", MENU_SCREEN_WIDTH, MENU_SCREEN_HEIGHT);
	system(str);
	MainMenu();
}