#include "util.h"
#include "player.h"
#include "resource.h"

current_enemy = 0;
mainmenuNumber = 1;

//Ŀ���� �����ִ� �Լ�
void hideCursor(void)
{
	CONSOLE_CURSOR_INFO consoleCursor;
	consoleCursor.bVisible = 0;
	consoleCursor.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursor);
}

//�ܼ�ũ�⸦ ���ϴ� �Լ�(���� ����, ���� ����)
void resizeConsole(short console_w, short console_h) {
	char chTemp[100];
	sprintf(chTemp, "mode con cols=%d lines=%d", console_w, console_h);
	system(chTemp);
}

//Ŀ���� ��ǥ�� �̵���Ű�� �Լ�(x,y)
void gotoxy(short x, short y) {
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

//�̹����� ����ϴ� �Լ�(�����̸��� ����, ���������ġx, ���������ġy, �̹������x, �̹������y)
void printImage(short pictureNum, short start_w, short start_h,short w, short h) {
	char path[101];
	//�̹������� �̸��� picture0, picture1 �̷� �������� ����Ǿ� ����
	sprintf(path, "C:\\resources\\picture%d.bmp", pictureNum);
	consoleWindow = GetConsoleWindow();
	consoleDC = GetDC(consoleWindow);
	imageDC = CreateCompatibleDC(consoleDC);
	imageMap = LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	SelectObject(imageDC, imageMap);
	BitBlt(consoleDC, start_w, start_h, w, h, imageDC, 0, 0, SRCCOPY);
	DeleteObject(imageMap);
	DeleteDC(imageDC);
	ReleaseDC(consoleWindow, consoleDC);
}

//gamemap�迭 ���� ��ǥ ���� ���� ��ġ�� �����(���� ������ ������ ����)
void setEnemyPosition_Gamemap(short enemyloaction_y, short enemyloaction_x) {

	// gamemap�迭 �󿡼� ���� ��ġ�� 1, ���� �������� 2, ���� ������ 3���� �ٲ㼭 �Ѿ˰��� �浹ó���� ����
	gamemap[enemyloaction_y][enemyloaction_x - 1] = 3;
	gamemap[enemyloaction_y][enemyloaction_x] = 1;
	gamemap[enemyloaction_y][enemyloaction_x + 1] = 2;
}

//�۾� ������ �ٲٴ� �Լ�(�Ű������� ���ѹ��� ����(0~15))
void setColor(unsigned short text) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (7 << 4));
}


//���� ���� �� �ε�ȭ���� �׷��ִ� �Լ�
void loading(void) {
	//�ε� ���� ȸ��
	setColor(8);
	gotoxy(50, 17);
	printf("�� �� �� �� �� ");
	for (int i = 1; i <= 8; i++) {

		gotoxy(50, 16);
		printf("�� �� �� �� �� ...");
		Sleep(30);

		if (i == 1) {
			gotoxy(50, 17);
			printf("��");
		}
		else if (i == 3) {
			gotoxy(53, 17);
			printf("��");
		}
		else if (i == 5) {
			gotoxy(56, 17);
			printf("��");
		}

		gotoxy(50, 16);

		printf("�� ");
		if (i == 7)
		{
			Sleep(30);
			gotoxy(59, 17);
			printf("��");
		}
		else if (i == 8)Sleep(150);
		else	Sleep(30);
		gotoxy(53, 16);
		printf("�� ");
		if (i == 7)	Sleep(50);
		else if (i == 8)Sleep(200);
		else	Sleep(30);

		gotoxy(56, 16);
		printf("�� ");
		if (i == 7)Sleep(70);
		else if (i == 8)Sleep(300);
		else	Sleep(30);

		gotoxy(59, 16);
		printf("�� ");
		if (i == 7)Sleep(70);
		else if (i == 8)
		{
			Sleep(450);
			gotoxy(62, 17);
			printf("��");
		}
		else	Sleep(30);

		gotoxy(62, 16);
		printf("�� ");
		if (i == 7)Sleep(120);
		else if (i == 8)Sleep(700);
		else	Sleep(30);
		
		
	}
	Sleep(100);
	//�ε� �Ŀ��� ������
	setColor(0);
	gotoxy(50, 16);
	printf("                    ");
	gotoxy(50, 17);
	printf("�� �� �� �� ��");
	gotoxy(48, 16);
	printf("�� �� ��  �� �� �� !");
	Sleep(200);
	gotoxy(50, 17);
	printf("              ");
	gotoxy(48, 16);
	printf("                    ");
	Sleep(200);
	gotoxy(50, 17);
	printf("�� �� �� �� ��");
	gotoxy(48, 16);
	printf("�� �� ��  �� �� �� !");
	Sleep(200);
	gotoxy(50, 17);
	printf("              ");
	gotoxy(48, 16);
	printf("                    ");
	Sleep(200);
	gotoxy(50, 17);
	printf("�� �� �� �� ��");
	gotoxy(48, 16);
	printf("�� �� ��  �� �� �� !");
	Sleep(200);
	gotoxy(50, 17);
	printf("              ");
	gotoxy(48, 16);
	Sleep(200);
	printf("                    ");
	//�ε� �߿��� �ٸ� Ű �Է� ����
	GetAsyncKeyState(13);
	GetAsyncKeyState(65);
	GetAsyncKeyState(68);
	GetAsyncKeyState(VK_UP);
	GetAsyncKeyState(VK_DOWN);
}

//����ȭ�鿡�� �޴��� �����ϴ� �Լ�(��ȯ ���� 1�̸� ���ӽ���, 2�̸� ��ŷ, 3�̸� ���Ӽ���, 4�� ���� ���� ����)
int selectMainMenu(void) {
	drawMainMenu(mainmenuNumber);
	while (1) {
		//�ѱ��� ���Ѷ� �̹��� ���
		printImage(0, 90, 90, 600, 480);
		if (GetAsyncKeyState(87) & 1 || GetAsyncKeyState(VK_UP) & 1) {
			mainmenuNumber -= 1;
			if (mainmenuNumber <= 1)	mainmenuNumber = 1;
			drawMainMenu(mainmenuNumber);
		}
		if (GetAsyncKeyState(83) & 1 || GetAsyncKeyState(VK_DOWN) & 1) {
			mainmenuNumber += 1;
			if (mainmenuNumber >= 4)mainmenuNumber = 4;
			drawMainMenu(mainmenuNumber);
		}

		if (GetAsyncKeyState(13)) {
			if (mainmenuNumber == 1) {
				system("cls");
				return 1;
			}
			else if (mainmenuNumber == 2) {
				system("cls");
				return 2;
			}
			else if (mainmenuNumber == 3) {
				system("cls");
				return 3;
			}
			else if (mainmenuNumber == 4) {
				go = 2;
				return 0;
			}
		}
		//�ٸ� Ű���� ����
		GetAsyncKeyState(65);
		GetAsyncKeyState(68);
		GetAsyncKeyState(8);
		GetAsyncKeyState(VK_LEFT);
		GetAsyncKeyState(VK_RIGHT);
	}

}

//����ȭ���� number�� ���� ���õ� �׸��� �׷��� ȭ���� �׷��ִ� �Լ�
void drawMainMenu(short number) {
	switch (number){
		case 1:
			setColor(15);
			gotoxy(78, 4);
			printf("����������������\n");
			gotoxy(78, 5);
			printf("��                          ��\n");
			gotoxy(78, 6);
			printf("��      ��  ��  ��  ��      ��\n");
			gotoxy(78, 7);
			printf("��                          ��\n");
			gotoxy(78, 8);
			printf("����������������\n");
			setColor(0);
			gotoxy(78, 12);
			printf("�̨̨̨̨̨̨̨̨̨̨̨̨̨̨�\n");
			gotoxy(78, 13);
			printf("��                          ��\n");
			gotoxy(78, 14);
			printf("��        ��        ŷ      ��\n");
			gotoxy(78, 15);
			printf("��                          ��\n");
			gotoxy(78, 16);
			printf("�̨̨̨̨̨̨̨̨̨̨̨̨̨̨�\n");
			gotoxy(78, 20);
			printf("�̨̨̨̨̨̨̨̨̨̨̨̨̨̨�\n");
			gotoxy(78, 21);
			printf("��                          ��\n");
			gotoxy(78, 22);
			printf("��       ��  ��  ��  ��     ��\n");
			gotoxy(78, 23);
			printf("��                          ��\n");
			gotoxy(78, 24);
			printf("�̨̨̨̨̨̨̨̨̨̨̨̨̨̨�\n");
			gotoxy(106, 26);
			printf("������������");
			gotoxy(106, 27);
			printf("��        ��");
			gotoxy(106, 28);
			printf("�� ������ ��");
			gotoxy(106, 29);
			printf("��        ��");
			gotoxy(106, 30);
			printf("������������");
			break;
		case 2:
			gotoxy(78, 4);
			printf("�̨̨̨̨̨̨̨̨̨̨̨̨̨̨�\n");
			gotoxy(78, 5);
			printf("��                          ��\n");
			gotoxy(78, 6);
			printf("��      ��  ��  ��  ��      ��\n");
			gotoxy(78, 7);
			printf("��                          ��\n");
			gotoxy(78, 8);
			printf("�̨̨̨̨̨̨̨̨̨̨̨̨̨̨�\n");
			setColor(15);
			gotoxy(78, 12);
			printf("����������������\n");
			gotoxy(78, 13);
			printf("��                          ��\n");
			gotoxy(78, 14);
			printf("��        ��        ŷ      ��\n");
			gotoxy(78, 15);
			printf("��                          ��\n");
			gotoxy(78, 16);
			printf("����������������\n");
			setColor(0);
			gotoxy(78, 20);
			printf("�̨̨̨̨̨̨̨̨̨̨̨̨̨̨�\n");
			gotoxy(78, 21);
			printf("��                          ��\n");
			gotoxy(78, 22);
			printf("��       ��  ��  ��  ��     ��\n");
			gotoxy(78, 23);
			printf("��                          ��\n");
			gotoxy(78, 24);
			printf("�̨̨̨̨̨̨̨̨̨̨̨̨̨̨�\n");
			gotoxy(106, 26);
			printf("������������");
			gotoxy(106, 27);
			printf("��        ��");
			gotoxy(106, 28);
			printf("�� ������ ��");
			gotoxy(106, 29);
			printf("��        ��");
			gotoxy(106, 30);
			printf("������������");
			break;
		case 3:
			gotoxy(78, 4);
			printf("�̨̨̨̨̨̨̨̨̨̨̨̨̨̨�\n");
			gotoxy(78, 5);
			printf("��                          ��\n");
			gotoxy(78, 6);
			printf("��      ��  ��  ��  ��      ��\n");
			gotoxy(78, 7);
			printf("��                          ��\n");
			gotoxy(78, 8);
			printf("�̨̨̨̨̨̨̨̨̨̨̨̨̨̨�\n");
			gotoxy(78, 12);
			printf("�̨̨̨̨̨̨̨̨̨̨̨̨̨̨�\n");
			gotoxy(78, 13);
			printf("��                          ��\n");
			gotoxy(78, 14);
			printf("��        ��        ŷ      ��\n");
			gotoxy(78, 15);
			printf("��                          ��\n");
			gotoxy(78, 16);
			printf("�̨̨̨̨̨̨̨̨̨̨̨̨̨̨�\n");
			setColor(15);
			gotoxy(78, 20);
			printf("����������������\n");
			gotoxy(78, 21);
			printf("��                          ��\n");
			gotoxy(78, 22);
			printf("��       ��  ��  ��  ��     ��\n");
			gotoxy(78, 23);
			printf("��                          ��\n");
			gotoxy(78, 24);
			printf("����������������\n");
			setColor(0);
			gotoxy(106, 26);
			printf("������������");
			gotoxy(106, 27);
			printf("��        ��");
			gotoxy(106, 28);
			printf("�� ������ ��");
			gotoxy(106, 29);
			printf("��        ��");
			gotoxy(106, 30);
			printf("������������");
			break;
		case 4:
			gotoxy(78, 4);
			printf("�̨̨̨̨̨̨̨̨̨̨̨̨̨̨�\n");
			gotoxy(78, 5);
			printf("��                          ��\n");
			gotoxy(78, 6);
			printf("��      ��  ��  ��  ��      ��\n");
			gotoxy(78, 7);
			printf("��                          ��\n");
			gotoxy(78, 8);
			printf("�̨̨̨̨̨̨̨̨̨̨̨̨̨̨�\n");
			gotoxy(78, 12);
			printf("�̨̨̨̨̨̨̨̨̨̨̨̨̨̨�\n");
			gotoxy(78, 13);
			printf("��                          ��\n");
			gotoxy(78, 14);
			printf("��        ��        ŷ      ��\n");
			gotoxy(78, 15);
			printf("��                          ��\n");
			gotoxy(78, 16);
			printf("�̨̨̨̨̨̨̨̨̨̨̨̨̨̨�\n");
			gotoxy(78, 20);
			printf("�̨̨̨̨̨̨̨̨̨̨̨̨̨̨�\n");
			gotoxy(78, 21);
			printf("��                          ��\n");
			gotoxy(78, 22);
			printf("��       ��  ��  ��  ��     ��\n");
			gotoxy(78, 23);
			printf("��                          ��\n");
			gotoxy(78, 24);
			printf("�̨̨̨̨̨̨̨̨̨̨̨̨̨̨�\n");
			gotoxy(106, 26);
			printf("�������");
			gotoxy(106, 27);
			printf("��        ��");
			gotoxy(106, 28);
			printf("�� ������ ��");
			gotoxy(106, 29);
			printf("��        ��");
			gotoxy(106, 30);
			printf("�������");
			break;
	}
}


//ĳ���Ͱ� ���õǾ��� �� �ش�ĳ������ ���� �ְ������� �ְ� ���������� ���Ͽ��� �ҷ��� ������ �������ִ� �Լ�
void getPreviousInformation(int myCharacter) {
	switch (myCharacter) {
	case 1:
		fp1 = fopen("�ܱ��հ�.txt", "a+");
		fscanf(fp1, "%d%d", &previousStage, &previousScore);
		fclose(fp1);
		break;
	case 2:
		fp2 = fopen("�̼����屺.txt", "a+");
		fscanf(fp2, "%d%d", &previousStage, &previousScore);
		fclose(fp2);
		break;
	case 3:
		fp3 = fopen("�������.txt", "a+");
		fscanf(fp3, "%d%d", &previousStage, &previousScore);
		fclose(fp3);
		break;
	case 4:
		fp4 = fopen("���߱�.txt", "a+");
		fscanf(fp4, "%d%d", &previousStage, &previousScore);
		fclose(fp4);
		break;
	case 5:
		fp5 = fopen("���ε�.txt", "a+");
		fscanf(fp5, "%d%d", &previousStage, &previousScore);
		fclose(fp5);
		break;
	case 6:
		fp6 = fopen("�����.txt", "a+");
		fscanf(fp6, "%d%d", &previousStage, &previousScore);
		fclose(fp6);
		break;
	case 7:
		system("cls");
		go = 1;
		break;
	}
}

//ó�� ĳ���� ����ȭ���� �׷��ִ� �Լ�
void drawCharacter(void) {
	//0�� ���õ��� ���� ȭ��
	c1(0);
	c2(0);
	c3(0);
	c4(0);
	c5(0);
	c6(0);
}

//ĳ���͸� �����ϴ� �Լ� (��ȯ���� ���� ���õ� ĳ���Ͱ� �޶���(1���� 6����))
int selectCharacter(void) {
	system("cls");
	drawCharacter();
	int number = 1;
	char ch = '\0';
	while (1) {
		//���� �̵�
		if (GetAsyncKeyState(87) & 1 || GetAsyncKeyState(VK_UP) & 1){
			if (number >= 1 && number <= 3)
				number = number;
			else number -= 3;
		}
		//�Ʒ��� �̵�
		if (GetAsyncKeyState(83) & 1 || GetAsyncKeyState(VK_DOWN) & 1){
			if (number >= 4 && number <= 6)
				number = number;
			else number += 3;
		}
		//���� �̵�
		if (GetAsyncKeyState(65) & 1 || GetAsyncKeyState(VK_LEFT) & 1) {
			number -= 1;
			if (number < 1)number = 6;
		}
		//������ �̵�
		if (GetAsyncKeyState(68) & 1 || GetAsyncKeyState(VK_RIGHT) & 1) {
			number += 1;
			if (number > 6)	number = 1;
		}
		//����
		if (GetAsyncKeyState(13))
		{
			switch (number) {
			case 1:
				return 1;
				break;
			case 2:
				return 2;
				break;
			case 3:
				return 3;
				break;
			case 4:
				return 4;
				break;
			case 5:
				return 5;
				break;
			case 6:
				return 6;
				break;
			}
		}
		//����ȭ��
		if (GetAsyncKeyState(8))	return 7;
		Sleep(15);

		switch (number) {
		case 1:
			selectCharacternumber(1);
			break;
		case 2:
			selectCharacternumber(2);
			break;
		case 3:
			selectCharacternumber(3);
			break;
		case 4:
			selectCharacternumber(4);
			break;
		case 5:
			selectCharacternumber(5);
			break;
		case 6:
			selectCharacternumber(6);
			break;
		}
	}
}

//�ش� ĳ���Ͱ� ���õ� ȭ���� �׷��ִ� �Լ�
int selectCharacternumber(short number) {
	short x1 = 12;
	short x2 = 48;
	short x3 = 84;
	int active[6] = { 0 };
	//���õ� ĳ���͸� 1�� Ȱ��ȭ ���� ���õ� ����� �׷���
	active[number-1] = 1;
	c1(active[0]);
	c2(active[1]);
	c3(active[2]);
	c4(active[3]);
	c5(active[4]);
	c6(active[5]);
}

//ĳ���� ���� ���� ȭ�� ǥ�� c1(ù�� ° ĳ����)~c6(���� ��° ĳ����)-(a�� 0�� ���� ���� ����� ȭ��, a�� 1�� ���� ���õ� ����� ȭ��)
void c1(short a) {
	int x1 = 12;
	if (a == 0) {
		gotoxy(x1, 1);
		printf("������������������������\n");
		gotoxy(x1, 2);
		printf("��                    ��\n");
		gotoxy(x1, 3);
		printf("��     �� �� �� ��    ��\n");
		gotoxy(x1, 4);
		printf("��                    ��\n");
		gotoxy(x1, 5);
		printf("��   ���⡲ �� �� ��  ��\n");
		gotoxy(x1, 6);
		printf("��                    ��\n");
		gotoxy(x1, 7);
		printf("��  �Ѿ˼ӵ� :   1    ��\n");
		gotoxy(x1, 8);
		printf("��  �����Ÿ� :   2    ��\n");
		gotoxy(x1, 9);
		printf("��  �Ѿ˰��� :   1    ��\n");
		gotoxy(x1, 10);
		printf("��  �����ð� :  0.1   ��\n");
		gotoxy(x1, 11);
		printf("��  �̵��ӵ� :  0.5   ��\n");
		gotoxy(x1, 12);
		printf("������������������������\n");
	}
	else {
		gotoxy(x1, 1);
		printf("�������������\n");
		gotoxy(x1, 2);
		printf("��                    ��\n");
		gotoxy(x1, 3);
		printf("��     �� �� �� ��    ��\n");
		gotoxy(x1, 4);
		printf("��                    ��\n");
		gotoxy(x1, 5);
		printf("��   ���⡲ �� �� ��  ��\n");
		gotoxy(x1, 6);
		printf("��                    ��\n");
		gotoxy(x1, 7);
		printf("��  �Ѿ˼ӵ� :   1    ��\n");
		gotoxy(x1, 8);
		printf("��  �����Ÿ� :   2    ��\n");
		gotoxy(x1, 9);
		printf("��  �Ѿ˰��� :   1    ��\n");
		gotoxy(x1, 10);
		printf("��  �����ð� :  0.1   ��\n");
		gotoxy(x1, 11);
		printf("��  �̵��ӵ� :  0.5   ��\n");
		gotoxy(x1, 12);
		printf("�������������\n");
	}
}
void c2(short a) {
	int x2 = 48;
	if (a == 0) {
		gotoxy(x2, 1);
		printf("������������������������\n");
		gotoxy(x2, 2);
		printf("��                    ��\n");
		gotoxy(x2, 3);
		printf("��     �̼����屺     ��\n");
		gotoxy(x2, 4);
		printf("��                    ��\n");
		gotoxy(x2, 5);
		printf("��   ���⡲ �� �� ��  ��\n");
		gotoxy(x2, 6);
		printf("��                    ��\n");
		gotoxy(x2, 7);
		printf("��  �Ѿ˼ӵ� :  1.5   ��\n");
		gotoxy(x2, 8);
		printf("��  �����Ÿ� :   5    ��\n");
		gotoxy(x2, 9);
		printf("��  �Ѿ˰��� :   7    ��\n");
		gotoxy(x2, 10);
		printf("��  �����ð� :  1.5   ��\n");
		gotoxy(x2, 11);
		printf("��  �̵��ӵ� :   1    ��\n");
		gotoxy(x2, 12);
		printf("������������������������\n");
	}
	else {
		gotoxy(x2, 1);
		printf("�������������\n");
		gotoxy(x2, 2);
		printf("��                    ��\n");
		gotoxy(x2, 3);
		printf("��     �̼����屺     ��\n");
		gotoxy(x2, 4);
		printf("��                    ��\n");
		gotoxy(x2, 5);
		printf("��   ���⡲ �� �� ��  ��\n");
		gotoxy(x2, 6);
		printf("��                    ��\n");
		gotoxy(x2, 7);
		printf("��  �Ѿ˼ӵ� :  1.5   ��\n");
		gotoxy(x2, 8);
		printf("��  �����Ÿ� :   5    ��\n");
		gotoxy(x2, 9);
		printf("��  �Ѿ˰��� :   7    ��\n");
		gotoxy(x2, 10);
		printf("��  �����ð� :  1.5   ��\n");
		gotoxy(x2, 11);
		printf("��  �̵��ӵ� :   1    ��\n");
		gotoxy(x2, 12);
		printf("�������������\n");
	}
}
void c3(short a) {
	int x3 = 84;
	if (a == 0) {
		gotoxy(x3, 1);
		printf("������������������������\n");
		gotoxy(x3, 2);
		printf("��                    ��\n");
		gotoxy(x3, 3);
		printf("��     �� �� �� ��    ��\n");
		gotoxy(x3, 4);
		printf("��                    ��\n");
		gotoxy(x3, 5);
		printf("��   ���⡲ �� �� ��  ��\n");
		gotoxy(x3, 6);
		printf("��                    ��\n");
		gotoxy(x3, 7);
		printf("��  �Ѿ˼ӵ� :  0.5   ��\n");
		gotoxy(x3, 8);
		printf("��  �����Ÿ� :   6    ��\n");
		gotoxy(x3, 9);
		printf("��  �Ѿ˰��� :   7    ��\n");
		gotoxy(x3, 10);
		printf("��  �����ð� :  0.6   ��\n");
		gotoxy(x3, 11);
		printf("��  �̵��ӵ� :  0.6   ��\n");
		gotoxy(x3, 12);
		printf("������������������������\n");
	}
	else {
		gotoxy(x3, 1);
		printf("�������������\n");
		gotoxy(x3, 2);
		printf("��                    ��\n");
		gotoxy(x3, 3);
		printf("��     �� �� �� ��    ��\n");
		gotoxy(x3, 4);
		printf("��                    ��\n");
		gotoxy(x3, 5);
		printf("��   ���⡲ �� �� ��  ��\n");
		gotoxy(x3, 6);
		printf("��                    ��\n");
		gotoxy(x3, 7);
		printf("��  �Ѿ˼ӵ� :  0.5   ��\n");
		gotoxy(x3, 8);
		printf("��  �����Ÿ� :   6    ��\n");
		gotoxy(x3, 9);
		printf("��  �Ѿ˰��� :   7    ��\n");
		gotoxy(x3, 10);
		printf("��  �����ð� :  0.6   ��\n");
		gotoxy(x3, 11);
		printf("��  �̵��ӵ� :  0.6   ��\n");
		gotoxy(x3, 12);
		printf("�������������\n");
	}
}
void c4(short a) {
	int x1 = 12;
	if (a == 0) {
		gotoxy(x1, 17);
		printf("������������������������\n");
		gotoxy(x1, 18);
		printf("��                    ��\n");
		gotoxy(x1, 19);
		printf("��     ��  ��  ��     ��\n");
		gotoxy(x1, 20);
		printf("��                    ��\n");
		gotoxy(x1, 21);
		printf("��   ���⡲ �� �� ��  ��\n");
		gotoxy(x1, 22);
		printf("��                    ��\n");
		gotoxy(x1, 23);
		printf("��  �Ѿ˼ӵ� :  0.8   ��\n");
		gotoxy(x1, 24);
		printf("��  �����Ÿ� :   10   ��\n");
		gotoxy(x1, 25);
		printf("��  �Ѿ˰��� :   11   ��\n");
		gotoxy(x1, 26);
		printf("��  �����ð� :  0.5   ��\n");
		gotoxy(x1, 27);
		printf("��  �̵��ӵ� :  0.6   ��\n");
		gotoxy(x1, 28);
		printf("������������������������\n");
	}
	else {
		gotoxy(x1, 17);
		printf("�������������\n");
		gotoxy(x1, 18);
		printf("��                    ��\n");
		gotoxy(x1, 19);
		printf("��     ��  ��  ��     ��\n");
		gotoxy(x1, 20);
		printf("��                    ��\n");
		gotoxy(x1, 21);
		printf("��   ���⡲ �� �� ��  ��\n");
		gotoxy(x1, 22);
		printf("��                    ��\n");
		gotoxy(x1, 23);
		printf("��  �Ѿ˼ӵ� :  0.8   ��\n");
		gotoxy(x1, 24);
		printf("��  �����Ÿ� :   10   ��\n");
		gotoxy(x1, 25);
		printf("��  �Ѿ˰��� :   11   ��\n");
		gotoxy(x1, 26);
		printf("��  �����ð� :  0.5   ��\n");
		gotoxy(x1, 27);
		printf("��  �̵��ӵ� :  0.6   ��\n");
		gotoxy(x1, 28);
		printf("�������������\n");
	}
}
void c5(short a) {
	int x2 = 48;

	if (a == 0) {
		gotoxy(x2, 17);
		printf("������������������������\n");
		gotoxy(x2, 18);
		printf("��                    ��\n");
		gotoxy(x2, 19);
		printf("��     ��  ��  ��     ��\n");
		gotoxy(x2, 20);
		printf("��                    ��\n");
		gotoxy(x2, 21);
		printf("��  ���⡲ ������ ��  ��\n");
		gotoxy(x2, 22);
		printf("��                    ��\n");
		gotoxy(x2, 23);
		printf("��  �Ѿ˼ӵ� :   6    ��\n");
		gotoxy(x2, 24);
		printf("��  �����Ÿ� :   15   ��\n");
		gotoxy(x2, 25);
		printf("��  �Ѿ˰��� :   2    ��\n");
		gotoxy(x2, 26);
		printf("��  �����ð� :   2    ��\n");
		gotoxy(x2, 27);
		printf("��  �̵��ӵ� :  0.8   ��\n");
		gotoxy(x2, 28);
		printf("������������������������\n");
	}
	else {
		gotoxy(x2, 17);
		printf("�������������\n");
		gotoxy(x2, 18);
		printf("��                    ��\n");
		gotoxy(x2, 19);
		printf("��     ��  ��  ��     ��\n");
		gotoxy(x2, 20);
		printf("��                    ��\n");
		gotoxy(x2, 21);
		printf("��  ���⡲ ������ ��  ��\n");
		gotoxy(x2, 22);
		printf("��                    ��\n");
		gotoxy(x2, 23);
		printf("��  �Ѿ˼ӵ� :   6    ��\n");
		gotoxy(x2, 24);
		printf("��  �����Ÿ� :   15   ��\n");
		gotoxy(x2, 25);
		printf("��  �Ѿ˰��� :   2    ��\n");
		gotoxy(x2, 26);
		printf("��  �����ð� :   2    ��\n");
		gotoxy(x2, 27);
		printf("��  �̵��ӵ� :  0.8   ��\n");
		gotoxy(x2, 28);
		printf("�������������\n");
	}
}
void c6(short a) {
	int x3 = 84;

	if (a == 0) {
		gotoxy(x3, 17);
		printf("������������������������\n");
		gotoxy(x3, 18);
		printf("��                    ��\n");
		gotoxy(x3, 19);
		printf("��     ��  ��  ��     ��\n");
		gotoxy(x3, 20);
		printf("��                    ��\n");
		gotoxy(x3, 21);
		printf("��  ���⡲ ����� ��  ��\n");
		gotoxy(x3, 22);
		printf("��                    ��\n");
		gotoxy(x3, 23);
		printf("��  �Ѿ˼ӵ� :   6    ��\n");
		gotoxy(x3, 24);
		printf("��  �����Ÿ� :   8    ��\n");
		gotoxy(x3, 25);
		printf("��  �Ѿ˰��� :   30   ��\n");
		gotoxy(x3, 26);
		printf("��  �����ð� :  2.3   ��\n");
		gotoxy(x3, 27);
		printf("��  �̵��ӵ� :   1    ��\n");
		gotoxy(x3, 28);
		printf("������������������������\n");
	}
	else {
		gotoxy(x3, 17);
		printf("�������������\n");
		gotoxy(x3, 18);
		printf("��                    ��\n");
		gotoxy(x3, 19);
		printf("��     ��  ��  ��     ��\n");
		gotoxy(x3, 20);
		printf("��                    ��\n");
		gotoxy(x3, 21);
		printf("��  ���⡲ ����� ��  ��\n");
		gotoxy(x3, 22);
		printf("��                    ��\n");
		gotoxy(x3, 23);
		printf("��  �Ѿ˼ӵ� :   6    ��\n");
		gotoxy(x3, 24);
		printf("��  �����Ÿ� :   8    ��\n");
		gotoxy(x3, 25);
		printf("��  �Ѿ˰��� :   30   ��\n");
		gotoxy(x3, 26);
		printf("��  �����ð� :  2.3   ��\n");
		gotoxy(x3, 27);
		printf("��  �̵��ӵ� :   1    ��\n");
		gotoxy(x3, 28);
		printf("�������������\n");
	}
}

//��ũ ȭ�� �� ������ �͵��� �׷��ִ� �Լ�
void drawRank_Static(void) {
	short x1 = 22, x2 = 54, x3 = 86;
	gotoxy(2, 15);
	printf("�ڷΰ���ڷΰ���!!!!!!");
	gotoxy(4, 14);
	printf("��");
	gotoxy(4, 16);
	printf("��");
	gotoxy(6, 13);
	printf("��");
	gotoxy(6, 17);
	printf("��");
	gotoxy(8, 12);
	printf("��");
	gotoxy(8, 18);
	printf("��");
	gotoxy(x1, 2);
	printf("������������������������\n");
	gotoxy(x1, 3);
	printf("��                    ��\n");
	gotoxy(x1, 4);
	printf("��     �� �� �� ��    ��\n");
	gotoxy(x1, 5);
	printf("��                    ��\n");
	gotoxy(x1, 6);
	printf("��    �ְ� ��������   ��\n");
	gotoxy(x1, 7);
	printf("��      ��     ��     ��\n");
	gotoxy(x1, 8);
	printf("��                    ��\n");
	gotoxy(x1, 9);
	printf("��      �ְ� ����     ��\n");
	gotoxy(x1, 10);
	printf("��     ��       ��    ��\n");
	gotoxy(x1, 11);
	printf("��                    ��\n");
	gotoxy(x1, 12);
	printf("��                    ��\n");
	gotoxy(x1, 13);
	printf("������������������������\n");

	gotoxy(x2, 2);
	printf("������������������������\n");
	gotoxy(x2, 3);
	printf("��                    ��\n");
	gotoxy(x2, 4);
	printf("��     �̼����屺     ��\n");
	gotoxy(x2, 5);
	printf("��                    ��\n");
	gotoxy(x2, 6);
	printf("��    �ְ� ��������   ��\n");
	gotoxy(x2, 7);
	printf("��      ��     ��     ��\n");
	gotoxy(x2, 8);
	printf("��                    ��\n");
	gotoxy(x2, 9);
	printf("��      �ְ� ����     ��\n");
	gotoxy(x2, 10);
	printf("��     ��       ��    ��\n");
	gotoxy(x2, 11);
	printf("��                    ��\n");
	gotoxy(x2, 12);
	printf("��                    ��\n");
	gotoxy(x2, 13);
	printf("������������������������\n");

	gotoxy(x3, 2);
	printf("������������������������\n");
	gotoxy(x3, 3);
	printf("��                    ��\n");
	gotoxy(x3, 4);
	printf("��     �� �� �� ��    ��\n");
	gotoxy(x3, 5);
	printf("��                    ��\n");
	gotoxy(x3, 6);
	printf("��    �ְ� ��������   ��\n");
	gotoxy(x3, 7);
	printf("��      ��     ��     ��\n");
	gotoxy(x3, 8);
	printf("��                    ��\n");
	gotoxy(x3, 9);
	printf("��      �ְ� ����     ��\n");
	gotoxy(x3, 10);
	printf("��     ��       ��    ��\n");
	gotoxy(x3, 11);
	printf("��                    ��\n");
	gotoxy(x3, 12);
	printf("��                    ��\n");
	gotoxy(x3, 13);
	printf("������������������������\n");

	gotoxy(x1, 17);
	printf("������������������������\n");
	gotoxy(x1, 18);
	printf("��                    ��\n");
	gotoxy(x1, 19);
	printf("��     ��  ��  ��     ��\n");
	gotoxy(x1, 20);
	printf("��                    ��\n");
	gotoxy(x1, 21);
	printf("��    �ְ� ��������   ��\n");
	gotoxy(x1, 22);
	printf("��      ��     ��     ��\n");
	gotoxy(x1, 23);
	printf("��                    ��\n");
	gotoxy(x1, 24);
	printf("��      �ְ� ����     ��\n");
	gotoxy(x1, 25);
	printf("��     ��       ��    ��\n");
	gotoxy(x1, 26);
	printf("��                    ��\n");
	gotoxy(x1, 27);
	printf("��                    ��\n");
	gotoxy(x1, 28);
	printf("������������������������\n");

	gotoxy(x2, 17);
	printf("������������������������\n");
	gotoxy(x2, 18);
	printf("��                    ��\n");
	gotoxy(x2, 19);
	printf("��     ��  ��  ��     ��\n");
	gotoxy(x2, 20);
	printf("��                    ��\n");
	gotoxy(x2, 21);
	printf("��    �ְ� ��������   ��\n");
	gotoxy(x2, 22);
	printf("��      ��     ��     ��\n");
	gotoxy(x2, 23);
	printf("��                    ��\n");
	gotoxy(x2, 24);
	printf("��      �ְ� ����     ��\n");
	gotoxy(x2, 25);
	printf("��     ��       ��    ��\n");
	gotoxy(x2, 26);
	printf("��                    ��\n");
	gotoxy(x2, 27);
	printf("��                    ��\n");
	gotoxy(x2, 28);
	printf("������������������������\n");

	gotoxy(x3, 17);
	printf("������������������������\n");
	gotoxy(x3, 18);
	printf("��                    ��\n");
	gotoxy(x3, 19);
	printf("��     ��  ��  ��     ��\n");
	gotoxy(x3, 20);
	printf("��                    ��\n");
	gotoxy(x3, 21);
	printf("��    �ְ� ��������   ��\n");
	gotoxy(x3, 22);
	printf("��      ��     ��     ��\n");
	gotoxy(x3, 23);
	printf("��                    ��\n");
	gotoxy(x3, 24);
	printf("��      �ְ� ����     ��\n");
	gotoxy(x3, 25);
	printf("��     ��       ��    ��\n");
	gotoxy(x3, 26);
	printf("��                    ��\n");
	gotoxy(x3, 27);
	printf("��                    ��\n");
	gotoxy(x3, 28);
	printf("������������������������\n");
}

//��ũ ȭ�� �� ������ �͵��� �׷��ִ� �Լ�
void drawRank_Dynamic(void) {
	fp1 = fopen("�ܱ��հ�.txt", "a+");
	fp2 = fopen("�̼����屺.txt", "a+");
	fp3 = fopen("�������.txt", "a+");
	fp4 = fopen("���߱�.txt", "a+");
	fp5 = fopen("���ε�.txt", "a+");
	fp6 = fopen("�����.txt", "a+");
	fscanf(fp1, "%d%d", &highstage[0], &highscore[0]);
	fscanf(fp2, "%d%d", &highstage[1], &highscore[1]);
	fscanf(fp3, "%d%d", &highstage[2], &highscore[2]);
	fscanf(fp4, "%d%d", &highstage[3], &highscore[3]);
	fscanf(fp5, "%d%d", &highstage[4], &highscore[4]);
	fscanf(fp6, "%d%d", &highstage[5], &highscore[5]);

	//���������� ����
	setColor(4);
	gotoxy(33, 7);
	printf("%2d", highstage[0]);
	gotoxy(32, 10);
	printf("%4d", highscore[0]);

	gotoxy(65, 7);
	printf("%2d", highstage[1]);
	gotoxy(64, 10);
	printf("%4d", highscore[1]);

	gotoxy(97, 7);
	printf("%2d", highstage[2]);
	gotoxy(96, 10);
	printf("%4d", highscore[2]);

	gotoxy(33, 22);
	printf("%2d", highstage[3]);
	gotoxy(32, 25);
	printf("%4d", highscore[3]);

	gotoxy(65, 22);
	printf("%2d", highstage[4]);
	gotoxy(64, 25);
	printf("%4d", highscore[4]);

	gotoxy(97, 22);
	printf("%2d", highstage[5]);
	gotoxy(96, 25);
	printf("%4d", highscore[5]);
	setColor(0);

	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	fclose(fp5);
	fclose(fp6);
}

//���� �� ������ �͵��� �׷��ִ� �Լ�
void drawStore_Static(void) {
	gotoxy(80, 3);
	printf("S T A G E ��       ��");
	gotoxy(70, 5);
	printf("������������������������������������������������������������������������������");
	gotoxy(70, 6);
	printf("��  �աաաազ�           ��            ��");
	gotoxy(70, 7);
	printf("��            ��������������������������            ��");
	gotoxy(70, 8);
	printf("��                                     ��");
	gotoxy(70, 9);
	printf("��  SCORE��       ����    BULLET   [   ]��");
	gotoxy(70, 10);
	printf("��  MONEY��       ���� RELOAD SPEED[   ]��");

	gotoxy(70, 11);
	printf("������������������������������������������������������������������������������");

	gotoxy(67, 12);
	printf("������������������������������������������������������������������������������������������");
	gotoxy(67, 13);
	printf("��  ����  ENEMY [    /    |����    /   ��] ������ �� ");
	gotoxy(67, 14);
	printf("��  ��       a b c d e f g h i j k l m      �� �� ");
	gotoxy(67, 15);
	printf("��  ��       n o p q r s t u v w x y z      �� �� ");
	gotoxy(67, 16);
	printf("��  �������������������������������������������������������������������������������� �� ");
	gotoxy(67, 17);
	printf("��                                           �� ");
	gotoxy(67, 18);
	printf("��         BULLET��400��                     �� ");
	gotoxy(67, 19);
	printf("��                                           �� ");
	gotoxy(67, 20);
	printf("��       DISTANCE��500��                     �� ");
	gotoxy(67, 21);
	printf("��                                           �� ");
	gotoxy(67, 22);
	printf("��   BULLET SPEED��400��                     �� ");
	gotoxy(67, 23);
	printf("��                                           �� ");
	gotoxy(67, 24);
	printf("��     MOVE SPEED��500��                     �� ");
	gotoxy(67, 25);
	printf("��                                           �� ");
	gotoxy(67, 26);
	printf("��                                           �� ");
	gotoxy(67, 27);
	printf("��                                           �� ");
	gotoxy(67, 28);
	printf("������������������������������������������������������������������������������������������");

}

//���� �� ������ �͵��� �׷��ִ� �Լ�(ĳ���� �ѹ��� �Ű������� ����)
void drawStore_Dynamic(short chnum) {
	//�����ð��� �ʴ����� ���
	short speedPerSec = chter[chnum].reloadspeed / 1000;
	gotoxy(104, 10);
	if (speedPerSec == 1 || speedPerSec == 2 || speedPerSec == 3)
		printf("%d.%1d", chter[chnum].reloadspeed / 1000, (chter[chnum].reloadspeed / 100) % 10);
	else printf("0.%1d", chter[chnum].reloadspeed / 100);

	setColor(12);
	gotoxy(101, 13);
	printf("%2d", sstage[stage].enemynum_endstage);
	setColor(0);

	gotoxy(96, 13);
	printf(" 0");
	gotoxy(82, 13);
	printf(" 0");

	setColor(1);
	gotoxy(85, 6);
	printf("%s", chter[chnum].name);
	setColor(0);

	setColor(9);
	gotoxy(97, 6);
	printf("%s", chter[chnum].armorname);
	setColor(0);

	setColor(12);
	gotoxy(95, 3);
	printf("%d", stage);
	setColor(0);

	setColor(12);
	gotoxy(87, 13);
	printf("%2d", sstage[stage].enemynum_clearstage);
	setColor(0);
}

//�������� �� ������ ���� ������ �׷��ִ� �Լ�
void displayStoreTime(void) {
	setColor(1);
	gotoxy(22, 5);
	printf("�� S T O R E  T I M E ��");
	gotoxy(19, 8);
	printf("�� BULLET : �Ѿ� ����");
	gotoxy(19, 10);
	printf("�� DISTANCE : ���� �Ÿ�");
	gotoxy(19, 12);
	printf("�� BULLET SPEED : �Ѿ� �ӵ�");
	gotoxy(19, 14);
	printf("�� MOVE SPEED : ĳ���� �̵� �ӵ�");
	gotoxy(19, 18);
	printf("�� �� : ������ ������ ���� ��");
	gotoxy(19, 20);
	printf("�� w,�� : �׸� ���� �̵�");
	gotoxy(19, 22);
	printf("�� s,�� : �׸� �Ʒ��� �̵�");
	gotoxy(19, 24);
	printf("�� �� : ���׷��̵�");
	gotoxy(19, 26);
	printf("�� �� : �ٿ�׷��̵�");
	setColor(0);
}


//���� ���� ���� �ǽð����� display�ϴ� �Լ�(�Ű������� ���� ���� ���� ����)
void displayhitEnemy(short hitEnemy) {
	Sleep(1);
	gotoxy(82, 13);
	printf("%2d", hitEnemy);
}

//���� �ǽð����� display�ϴ� �Լ�(�Ű������� ���� ����)
void displayMoney(short money) {
	gotoxy(81, 10);
	printf("%5d", money);
}

//������ �ǽð����� display�ϴ� �Լ�(�Ű������� ������ ����)
void displayScore(short score) {
	Sleep(1);
	gotoxy(81, 9);
	printf("%5d", score);
}

//�Ѿ��� ���� �ǽð����� display�ϴ� �Լ�(�Ű������� �Ѿ��� ����)
void displayBulletNum(short bullet){
	Sleep(1);
	setColor(9);
	gotoxy(104, 9);
	printf("%3d", bullet);
	setColor(0);
}

//���� ȭ�� �� ���� �ִ� ���� ���� �ǽð����� display�ϴ� �Լ�(�Ű������� ���� ���� ���� ����)
void displayCurrentEnemy(short currentenemy) {
	if (currentenemy == 1)	current_enemy += 1;
	else if (currentenemy == -1)	current_enemy -= 1;
	Sleep(1);
	gotoxy(96, 13);
	printf("%2d ", current_enemy);
}


//ĳ���Ͱ� �׾��� ���� �޴�ȭ���� �׷���
void drawEndMenu(short num) {
	switch (num) {
	case 1:
		gotoxy(11, 13);
		printf("���ü��ü��ü���");
		gotoxy(11, 14);
		printf("��            ��");
		gotoxy(11, 15);
		printf("��  ��������  ��");
		gotoxy(11, 16);
		printf("��            ��");
		gotoxy(11, 17);
		printf("���ü��ü��ü���");

		gotoxy(42, 13);
		printf("����������������");
		gotoxy(42, 14);
		printf("��            ��");
		gotoxy(42, 15);
		printf("��  �ٽ��ϱ�  ��");
		gotoxy(42, 16);
		printf("��            ��");
		gotoxy(42, 17);
		printf("����������������");
		break;
	case 2:
		gotoxy(11, 13);
		printf("����������������");
		gotoxy(11, 14);
		printf("��            ��");
		gotoxy(11, 15);
		printf("��  ��������  ��");
		gotoxy(11, 16);
		printf("��            ��");
		gotoxy(11, 17);
		printf("����������������");

		gotoxy(42, 13);
		printf("���ü��ü��ü���");
		gotoxy(42, 14);
		printf("��            ��");
		gotoxy(42, 15);
		printf("��  �ٽ��ϱ�  ��");
		gotoxy(42, 16);
		printf("��            ��");
		gotoxy(42, 17);
		printf("���ü��ü��ü���");
	}
}

//ĳ���Ͱ� �׾��� �� ����Ǹ�, ���� �ش� ĳ������ �ְ�������� ������ ���� �����Ѵ�(�Ű������� ĳ������ number�� ����)
void saveHighscore(short pnum) {
	//�ְ����̶�� ���Ͽ� ����
	if (previousStage <= stage) {
		if(previousScore <= score){
			switch (pnum) {
			case 1:
				fp1 = fopen("�ܱ��հ�.txt", "w+");
				fprintf(fp1, "%d %d", stage, score);
				fclose(fp1);
				break;
			case 2:
				fp2 = fopen("�̼����屺.txt", "w+");
				fprintf(fp2, "%d %d", stage, score);
				fclose(fp2);
				break;
			case 3:
				fp3 = fopen("�������.txt", "w+");
				fprintf(fp3, "%d %d", stage, score);
				fclose(fp3);
				break;
			case 4:
				fp4 = fopen("���߱�.txt", "w+");
				fprintf(fp4, "%d %d", stage, score);
				fclose(fp4);
				break;
			case 5:
				fp5 = fopen("���ε�.txt", "w+");
				fprintf(fp5, "%d %d", stage, score);
				fclose(fp5);
				break;
			case 6:
				fp6 = fopen("�����.txt", "w+");
				fprintf(fp6, "%d %d", stage, score);
				fclose(fp6);
				break;
			}

		}
	}
	go=selectEndmenu();
}

//ĳ���Ͱ� �׾��� �� �ٽ��� ���� ������ ���� �����ϴ� �޴��� �����ϴ� �Լ�
int selectEndmenu(void) {
	short selectnum = 1;
	while (1) {
		if (GetAsyncKeyState(65) & 1 || GetAsyncKeyState(VK_LEFT) & 1)
		{
			selectnum -= 1;
			if (selectnum <= 1)	selectnum = 1;
		}
		if (GetAsyncKeyState(68) & 1 || GetAsyncKeyState(VK_RIGHT) & 1) {
			selectnum += 1;
			if (selectnum >= 2)selectnum = 2;
		}

		if (selectnum == 1 && GetAsyncKeyState(13))
		{
			system("cls");
			return 2;
		}
		else if (selectnum == 2 && GetAsyncKeyState(13)) {
			system("cls");
			return 1;
		}
		GetAsyncKeyState(8);
		GetAsyncKeyState(83);
		GetAsyncKeyState(87);

		switch (selectnum) {
		case 1:
			drawEndMenu(1);
			break;
		case 2:
			drawEndMenu(2);
			break;
		}
	}
}


//�������� ���� ����, 3�� ī���͸� �� ��, �������� ������ �̵�Ű�� �߻�Ű�� ������ �׷��ִ� �Լ�
void loadingStage(void) {
	short enemyspeed = sstage[stage].displayenemyspeed;
	setColor(12);
	gotoxy(28, 10);
	printf("STAGE �� %d  ��", stage);
	setColor(9);
	gotoxy(21, 12);
	printf("ENEMY�� ");
	if (enemyspeed / 1000 == 1)	printf("%d.%1d��", enemyspeed / 1000, (enemyspeed / 100) % 10);
	else {
		if (enemyspeed % 100 != 0){
			if (enemyspeed % 10 != 0)	printf("0.%1d%1d%1d��", enemyspeed / 100, (enemyspeed % 100) / 10, enemyspeed % 10);
			else printf("0.%1d%1d��", enemyspeed / 100, (enemyspeed % 100) / 10);
		}
		else 	printf("0.%1d��", enemyspeed / 100);
	}

	printf(" ���ʸ��� ����");
	setColor(12);
	gotoxy(17, 19);
	printf("           W                 ��");
	gotoxy(17, 20);
	printf("�߻� :   A   S    �̵� :   ��  ��");
	gotoxy(17, 21);
	printf("           D                 ��");
	gotoxy(30, 15);
	setColor(0);
	printf("��    ��");
	for (int i = 3; i >= 1; i--) {
		gotoxy(33, 15);
		switch (i) {
		case 3: printf("��"); break;
		case 2: printf("��"); break;
		case 1: printf("��"); break;
		}
		Sleep(1000);
	}
}

//���������� Ŭ���� ���� �� STAGE CLEAR�� �׷��ִ� �Լ�
void drawStageClear(void) {
	setColor(15);
	gotoxy(7, 3);
	printf("�� �� �� ��  Ŭ �� ��  �� �� �� ��  Ŭ �� ��  ��  ��");
	gotoxy(7, 5);
	printf(" �� ��  Ŭ �� ��  �� �� �� ��  Ŭ �� ��  �� �� �� ��");
	gotoxy(7, 7);
	printf("Ŭ �� ��  �� �� �� ��  Ŭ �� ��  �� �� �� ��  Ŭ �� ��");
	gotoxy(7, 9);
	printf("�� �� �� ��  Ŭ �� ��  �� �� �� ��  Ŭ �� ��  ��  ��");
	gotoxy(7, 11);
	printf(" �� ��  Ŭ �� ��  �� �� �� ��  Ŭ �� ��  �� �� �� ��");
	gotoxy(7, 13);
	printf("Ŭ �� ��  �� �� �� ��  Ŭ �� ��  �� �� �� ��  Ŭ �� ��");
	gotoxy(7, 15);
	printf("�� �� �� ��  Ŭ �� ��  �� �� �� ��  Ŭ �� ��  ��  ��");
	gotoxy(7, 17);
	printf(" �� ��  Ŭ �� ��  �� �� �� ��  Ŭ �� ��  �� �� �� ��");
	gotoxy(7, 19);
	printf("Ŭ �� ��  �� �� �� ��  Ŭ �� ��  �� �� �� ��  Ŭ �� ��");
	gotoxy(7, 21);
	printf("�� �� �� ��  Ŭ �� ��  �� �� �� ��  Ŭ �� ��  ��  ��");
	gotoxy(7, 23);
	printf(" �� ��  Ŭ �� ��  �� �� �� ��  Ŭ �� ��  �� �� �� ��");
	gotoxy(7, 25);
	printf("Ŭ �� ��  �� �� �� ��  Ŭ �� ��  �� �� �� ��  Ŭ �� ��");
	gotoxy(7, 27);
	printf("�� �� �� ��  Ŭ �� ��  �� �� �� ��  Ŭ �� ��  ��  ��");
	setColor(0);
	//�ٸ� Ű���� ����
	GetAsyncKeyState(13);
	GetAsyncKeyState(83);
	GetAsyncKeyState(87);
	GetAsyncKeyState(65);
	GetAsyncKeyState(68);
}

//���������� Ŭ���� ���� �� ���� ���������� �Ѿ�� �Լ�
void goNextStage(void) {
	clearBattleGround();
	PlaySound(NULL, 0, 0);
	PlaySound(TEXT("clearMusic2.wav"), NULL, SND_FILENAME | SND_ASYNC);
	for (int y = 0; y < 32; y++)
		for (int x = 0; x < 120; x++)	gamemap[y][x] = 0;
	//���������� Ŭ���������� ������ �ʱ�ȭ
	current_enemy = 0;
	stage += 1;
	hitEnemy = 0;
	isstart = 1;
	if (stage >= 14)	money += 7000;
	else if (stage >= 12)	money += 5500;
	else if (stage >= 10)	money += 4000;
	else if (stage >= 8)	money += 3000;
	else if (stage >= 6)	money += 2000;
	else if (stage >= 4)	money += 1500;
	else if (stage >= 2) money += 1000;
	else money += 600;

	Sleep(700);
	drawStageClear();
	Sleep(500);
	clearBattleGround();
	Sleep(500);
	drawStageClear();
	Sleep(500);
	clearBattleGround();
	Sleep(500);
	drawStageClear();
	Sleep(1600);
	clearBattleGround();
	Sleep(400);

	GetAsyncKeyState(VK_UP);
	GetAsyncKeyState(VK_DOWN);
	GetAsyncKeyState(VK_LEFT);
	GetAsyncKeyState(VK_RIGHT);
	GetAsyncKeyState(65);
	GetAsyncKeyState(68);
	GetAsyncKeyState(87);
	GetAsyncKeyState(83);

	startGame();
}


//������� �׵θ��� �׷��ִ� �Լ�
void drawSide(void) {
	system("cls");
	short w = 0, h = 0;
	for (int y = 0; y < HEIGHT - (2 * MARGIN_Y); y++) {
		for (int x = 0; x < (WIDTH / 2); x += 2)
		{
			if ((WIDTH / 2) % 2 == 0)	w = WIDTH / 2 - 2;
			else w = WIDTH / 2 - 1;

			gotoxy(x + MARGIN_X, y + MARGIN_Y);
			if (x == 0 || y == 0 || x == w || y == HEIGHT - (MARGIN_Y * 2) - 1)
				printf("��");
		}
	}
	for (int y = MARGIN_Y - 1; y < HEIGHT - MARGIN_Y + 1; y++) {
		for (int x = (WIDTH / 2) + 4; x < WIDTH - MARGIN_X; x += 2) {
			gotoxy(x, y);
			printf("��");
		}
	}
	for (int y = MARGIN_Y; y < HEIGHT - MARGIN_Y; y++) {
		for (int x = (WIDTH / 2) + 6; x < WIDTH - MARGIN_X - 2; x += 2) {
			gotoxy(x, y);
			printf("  ");
		}
	}
}

//����� ���� �������� ä�� ����ϰ� �����ִ� �Լ�
void clearBattleGround(void) {
	for (int y = 3; y < 29; y++) {
		for (int x = 7; x < 61; x += 2) {
			gotoxy(x, y);
			printf("  ");
		}
	}
}