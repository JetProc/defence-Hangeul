#include "util.h"
#include "player.h"
#include "resource.h"

current_enemy = 0;
mainmenuNumber = 1;

//커서를 숨겨주는 함수
void hideCursor(void)
{
	CONSOLE_CURSOR_INFO consoleCursor;
	consoleCursor.bVisible = 0;
	consoleCursor.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursor);
}

//콘솔크기를 정하는 함수(가로 길이, 세로 길이)
void resizeConsole(short console_w, short console_h) {
	char chTemp[100];
	sprintf(chTemp, "mode con cols=%d lines=%d", console_w, console_h);
	system(chTemp);
}

//커서의 좌표를 이동시키는 함수(x,y)
void gotoxy(short x, short y) {
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

//이미지를 출력하는 함수(파일이름의 숫자, 시작출력위치x, 시작출력위치y, 이미지출력x, 이미지출력y)
void printImage(short pictureNum, short start_w, short start_h,short w, short h) {
	char path[101];
	//이미지파일 이름이 picture0, picture1 이런 형식으로 저장되어 있음
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

//gamemap배열 상의 좌표 위에 적의 위치를 찍어줌(적이 생성될 때마다 실행)
void setEnemyPosition_Gamemap(short enemyloaction_y, short enemyloaction_x) {

	// gamemap배열 상에서 적의 위치는 1, 적의 오른쪽은 2, 적의 왼쪽은 3으로 바꿔서 총알과의 충돌처리를 위함
	gamemap[enemyloaction_y][enemyloaction_x - 1] = 3;
	gamemap[enemyloaction_y][enemyloaction_x] = 1;
	gamemap[enemyloaction_y][enemyloaction_x + 1] = 2;
}

//글씨 색깔을 바꾸는 함수(매개변수로 색넘버를 받음(0~15))
void setColor(unsigned short text) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (7 << 4));
}


//게임 시작 전 로딩화면을 그려주는 함수
void loading(void) {
	//로딩 전은 회색
	setColor(8);
	gotoxy(50, 17);
	printf("□ □ □ □ □ ");
	for (int i = 1; i <= 8; i++) {

		gotoxy(50, 16);
		printf("ㄱ ㅇ ㄹ ㄷ ㅈ ...");
		Sleep(30);

		if (i == 1) {
			gotoxy(50, 17);
			printf("■");
		}
		else if (i == 3) {
			gotoxy(53, 17);
			printf("■");
		}
		else if (i == 5) {
			gotoxy(56, 17);
			printf("■");
		}

		gotoxy(50, 16);

		printf("게 ");
		if (i == 7)
		{
			Sleep(30);
			gotoxy(59, 17);
			printf("■");
		}
		else if (i == 8)Sleep(150);
		else	Sleep(30);
		gotoxy(53, 16);
		printf("임 ");
		if (i == 7)	Sleep(50);
		else if (i == 8)Sleep(200);
		else	Sleep(30);

		gotoxy(56, 16);
		printf("로 ");
		if (i == 7)Sleep(70);
		else if (i == 8)Sleep(300);
		else	Sleep(30);

		gotoxy(59, 16);
		printf("딩 ");
		if (i == 7)Sleep(70);
		else if (i == 8)
		{
			Sleep(450);
			gotoxy(62, 17);
			printf("■");
		}
		else	Sleep(30);

		gotoxy(62, 16);
		printf("중 ");
		if (i == 7)Sleep(120);
		else if (i == 8)Sleep(700);
		else	Sleep(30);
		
		
	}
	Sleep(100);
	//로딩 후에는 검은색
	setColor(0);
	gotoxy(50, 16);
	printf("                    ");
	gotoxy(50, 17);
	printf("■ ■ ■ ■ ■");
	gotoxy(48, 16);
	printf("한 글 을  지 켜 라 !");
	Sleep(200);
	gotoxy(50, 17);
	printf("              ");
	gotoxy(48, 16);
	printf("                    ");
	Sleep(200);
	gotoxy(50, 17);
	printf("■ ■ ■ ■ ■");
	gotoxy(48, 16);
	printf("한 글 을  지 켜 라 !");
	Sleep(200);
	gotoxy(50, 17);
	printf("              ");
	gotoxy(48, 16);
	printf("                    ");
	Sleep(200);
	gotoxy(50, 17);
	printf("■ ■ ■ ■ ■");
	gotoxy(48, 16);
	printf("한 글 을  지 켜 라 !");
	Sleep(200);
	gotoxy(50, 17);
	printf("              ");
	gotoxy(48, 16);
	Sleep(200);
	printf("                    ");
	//로딩 중에는 다른 키 입력 무시
	GetAsyncKeyState(13);
	GetAsyncKeyState(65);
	GetAsyncKeyState(68);
	GetAsyncKeyState(VK_UP);
	GetAsyncKeyState(VK_DOWN);
}

//메인화면에서 메뉴를 선택하는 함수(반환 값이 1이면 게임시작, 2이면 랭킹, 3이면 게임설명, 4면 게임 종료 실행)
int selectMainMenu(void) {
	drawMainMenu(mainmenuNumber);
	while (1) {
		//한글을 지켜라 이미지 출력
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
		//다른 키들은 무시
		GetAsyncKeyState(65);
		GetAsyncKeyState(68);
		GetAsyncKeyState(8);
		GetAsyncKeyState(VK_LEFT);
		GetAsyncKeyState(VK_RIGHT);
	}

}

//메인화면의 number에 따라서 선택된 항목이 그려진 화면을 그려주는 함수
void drawMainMenu(short number) {
	switch (number){
		case 1:
			setColor(15);
			gotoxy(78, 4);
			printf("■■■■■■■■■■■■■■■\n");
			gotoxy(78, 5);
			printf("■                          ■\n");
			gotoxy(78, 6);
			printf("■      게  임  시  작      ■\n");
			gotoxy(78, 7);
			printf("■                          ■\n");
			gotoxy(78, 8);
			printf("■■■■■■■■■■■■■■■\n");
			setColor(0);
			gotoxy(78, 12);
			printf("㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻\n");
			gotoxy(78, 13);
			printf("㉻                          ㉻\n");
			gotoxy(78, 14);
			printf("㉻        랭        킹      ㉻\n");
			gotoxy(78, 15);
			printf("㉻                          ㉻\n");
			gotoxy(78, 16);
			printf("㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻\n");
			gotoxy(78, 20);
			printf("㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻\n");
			gotoxy(78, 21);
			printf("㉻                          ㉻\n");
			gotoxy(78, 22);
			printf("㉻       게  임  설  명     ㉻\n");
			gotoxy(78, 23);
			printf("㉻                          ㉻\n");
			gotoxy(78, 24);
			printf("㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻\n");
			gotoxy(106, 26);
			printf("㉯㉮㉯㉮㉯㉮");
			gotoxy(106, 27);
			printf("㉯        ㉮");
			gotoxy(106, 28);
			printf("㉯ 끝내기 ㉮");
			gotoxy(106, 29);
			printf("㉯        ㉮");
			gotoxy(106, 30);
			printf("㉯㉮㉯㉮㉯㉮");
			break;
		case 2:
			gotoxy(78, 4);
			printf("㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻\n");
			gotoxy(78, 5);
			printf("㉻                          ㉻\n");
			gotoxy(78, 6);
			printf("㉻      게  임  시  작      ㉻\n");
			gotoxy(78, 7);
			printf("㉻                          ㉻\n");
			gotoxy(78, 8);
			printf("㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻\n");
			setColor(15);
			gotoxy(78, 12);
			printf("■■■■■■■■■■■■■■■\n");
			gotoxy(78, 13);
			printf("■                          ■\n");
			gotoxy(78, 14);
			printf("■        랭        킹      ■\n");
			gotoxy(78, 15);
			printf("■                          ■\n");
			gotoxy(78, 16);
			printf("■■■■■■■■■■■■■■■\n");
			setColor(0);
			gotoxy(78, 20);
			printf("㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻\n");
			gotoxy(78, 21);
			printf("㉻                          ㉻\n");
			gotoxy(78, 22);
			printf("㉻       게  임  설  명     ㉻\n");
			gotoxy(78, 23);
			printf("㉻                          ㉻\n");
			gotoxy(78, 24);
			printf("㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻\n");
			gotoxy(106, 26);
			printf("㉯㉮㉯㉮㉯㉮");
			gotoxy(106, 27);
			printf("㉯        ㉮");
			gotoxy(106, 28);
			printf("㉯ 끝내기 ㉮");
			gotoxy(106, 29);
			printf("㉯        ㉮");
			gotoxy(106, 30);
			printf("㉯㉮㉯㉮㉯㉮");
			break;
		case 3:
			gotoxy(78, 4);
			printf("㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻\n");
			gotoxy(78, 5);
			printf("㉻                          ㉻\n");
			gotoxy(78, 6);
			printf("㉻      게  임  시  작      ㉻\n");
			gotoxy(78, 7);
			printf("㉻                          ㉻\n");
			gotoxy(78, 8);
			printf("㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻\n");
			gotoxy(78, 12);
			printf("㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻\n");
			gotoxy(78, 13);
			printf("㉻                          ㉻\n");
			gotoxy(78, 14);
			printf("㉻        랭        킹      ㉻\n");
			gotoxy(78, 15);
			printf("㉻                          ㉻\n");
			gotoxy(78, 16);
			printf("㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻\n");
			setColor(15);
			gotoxy(78, 20);
			printf("■■■■■■■■■■■■■■■\n");
			gotoxy(78, 21);
			printf("■                          ■\n");
			gotoxy(78, 22);
			printf("■       게  임  설  명     ■\n");
			gotoxy(78, 23);
			printf("■                          ■\n");
			gotoxy(78, 24);
			printf("■■■■■■■■■■■■■■■\n");
			setColor(0);
			gotoxy(106, 26);
			printf("㉯㉮㉯㉮㉯㉮");
			gotoxy(106, 27);
			printf("㉯        ㉮");
			gotoxy(106, 28);
			printf("㉯ 끝내기 ㉮");
			gotoxy(106, 29);
			printf("㉯        ㉮");
			gotoxy(106, 30);
			printf("㉯㉮㉯㉮㉯㉮");
			break;
		case 4:
			gotoxy(78, 4);
			printf("㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻\n");
			gotoxy(78, 5);
			printf("㉻                          ㉻\n");
			gotoxy(78, 6);
			printf("㉻      게  임  시  작      ㉻\n");
			gotoxy(78, 7);
			printf("㉻                          ㉻\n");
			gotoxy(78, 8);
			printf("㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻\n");
			gotoxy(78, 12);
			printf("㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻\n");
			gotoxy(78, 13);
			printf("㉻                          ㉻\n");
			gotoxy(78, 14);
			printf("㉻        랭        킹      ㉻\n");
			gotoxy(78, 15);
			printf("㉻                          ㉻\n");
			gotoxy(78, 16);
			printf("㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻\n");
			gotoxy(78, 20);
			printf("㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻\n");
			gotoxy(78, 21);
			printf("㉻                          ㉻\n");
			gotoxy(78, 22);
			printf("㉻       게  임  설  명     ㉻\n");
			gotoxy(78, 23);
			printf("㉻                          ㉻\n");
			gotoxy(78, 24);
			printf("㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻㉻\n");
			gotoxy(106, 26);
			printf("□□□□□□");
			gotoxy(106, 27);
			printf("□        □");
			gotoxy(106, 28);
			printf("□ 끝내기 □");
			gotoxy(106, 29);
			printf("□        □");
			gotoxy(106, 30);
			printf("□□□□□□");
			break;
	}
}


//캐릭터가 선택되었을 때 해당캐릭터의 이전 최고점수와 최고 스테이지를 파일에서 불러와 변수에 저장해주는 함수
void getPreviousInformation(int myCharacter) {
	switch (myCharacter) {
	case 1:
		fp1 = fopen("단군왕검.txt", "a+");
		fscanf(fp1, "%d%d", &previousStage, &previousScore);
		fclose(fp1);
		break;
	case 2:
		fp2 = fopen("이순신장군.txt", "a+");
		fscanf(fp2, "%d%d", &previousStage, &previousScore);
		fclose(fp2);
		break;
	case 3:
		fp3 = fopen("세종대왕.txt", "a+");
		fscanf(fp3, "%d%d", &previousStage, &previousScore);
		fclose(fp3);
		break;
	case 4:
		fp4 = fopen("안중근.txt", "a+");
		fscanf(fp4, "%d%d", &previousStage, &previousScore);
		fclose(fp4);
		break;
	case 5:
		fp5 = fopen("국민들.txt", "a+");
		fscanf(fp5, "%d%d", &previousStage, &previousScore);
		fclose(fp5);
		break;
	case 6:
		fp6 = fopen("대통령.txt", "a+");
		fscanf(fp6, "%d%d", &previousStage, &previousScore);
		fclose(fp6);
		break;
	case 7:
		system("cls");
		go = 1;
		break;
	}
}

//처음 캐릭터 선택화면을 그려주는 함수
void drawCharacter(void) {
	//0은 선택되지 않은 화면
	c1(0);
	c2(0);
	c3(0);
	c4(0);
	c5(0);
	c6(0);
}

//캐릭터를 선택하는 함수 (반환값에 따라서 선택된 캐릭터가 달라짐(1부터 6까지))
int selectCharacter(void) {
	system("cls");
	drawCharacter();
	int number = 1;
	char ch = '\0';
	while (1) {
		//위로 이동
		if (GetAsyncKeyState(87) & 1 || GetAsyncKeyState(VK_UP) & 1){
			if (number >= 1 && number <= 3)
				number = number;
			else number -= 3;
		}
		//아래로 이동
		if (GetAsyncKeyState(83) & 1 || GetAsyncKeyState(VK_DOWN) & 1){
			if (number >= 4 && number <= 6)
				number = number;
			else number += 3;
		}
		//왼쪽 이동
		if (GetAsyncKeyState(65) & 1 || GetAsyncKeyState(VK_LEFT) & 1) {
			number -= 1;
			if (number < 1)number = 6;
		}
		//오른쪽 이동
		if (GetAsyncKeyState(68) & 1 || GetAsyncKeyState(VK_RIGHT) & 1) {
			number += 1;
			if (number > 6)	number = 1;
		}
		//선택
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
		//메인화면
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

//해당 캐릭터가 선택된 화면을 그려주는 함수
int selectCharacternumber(short number) {
	short x1 = 12;
	short x2 = 48;
	short x3 = 84;
	int active[6] = { 0 };
	//선택된 캐릭터만 1로 활성화 시켜 선택된 모습을 그려줌
	active[number-1] = 1;
	c1(active[0]);
	c2(active[1]);
	c3(active[2]);
	c4(active[3]);
	c5(active[4]);
	c6(active[5]);
}

//캐릭터 선택 시의 화면 표시 c1(첫번 째 캐릭터)~c6(여섯 번째 캐릭터)-(a가 0일 때는 원래 모양의 화면, a가 1일 때는 선택된 모양의 화면)
void c1(short a) {
	int x1 = 12;
	if (a == 0) {
		gotoxy(x1, 1);
		printf("㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮\n");
		gotoxy(x1, 2);
		printf("㉮                    ㉮\n");
		gotoxy(x1, 3);
		printf("㉮     단 군 왕 검    ㉮\n");
		gotoxy(x1, 4);
		printf("㉮                    ㉮\n");
		gotoxy(x1, 5);
		printf("㉮   무기〔 단 검 〕  ㉮\n");
		gotoxy(x1, 6);
		printf("㉮                    ㉮\n");
		gotoxy(x1, 7);
		printf("㉮  총알속도 :   1    ㉮\n");
		gotoxy(x1, 8);
		printf("㉮  사정거리 :   2    ㉮\n");
		gotoxy(x1, 9);
		printf("㉮  총알개수 :   1    ㉮\n");
		gotoxy(x1, 10);
		printf("㉮  장전시간 :  0.1   ㉮\n");
		gotoxy(x1, 11);
		printf("㉮  이동속도 :  0.5   ㉮\n");
		gotoxy(x1, 12);
		printf("㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮\n");
	}
	else {
		gotoxy(x1, 1);
		printf("■■■■■■■■■■■■\n");
		gotoxy(x1, 2);
		printf("■                    ■\n");
		gotoxy(x1, 3);
		printf("■     단 군 왕 검    ■\n");
		gotoxy(x1, 4);
		printf("■                    ■\n");
		gotoxy(x1, 5);
		printf("■   무기〔 단 검 〕  ■\n");
		gotoxy(x1, 6);
		printf("■                    ■\n");
		gotoxy(x1, 7);
		printf("■  총알속도 :   1    ■\n");
		gotoxy(x1, 8);
		printf("■  사정거리 :   2    ■\n");
		gotoxy(x1, 9);
		printf("■  총알개수 :   1    ■\n");
		gotoxy(x1, 10);
		printf("■  장전시간 :  0.1   ■\n");
		gotoxy(x1, 11);
		printf("■  이동속도 :  0.5   ■\n");
		gotoxy(x1, 12);
		printf("■■■■■■■■■■■■\n");
	}
}
void c2(short a) {
	int x2 = 48;
	if (a == 0) {
		gotoxy(x2, 1);
		printf("㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮\n");
		gotoxy(x2, 2);
		printf("㉮                    ㉮\n");
		gotoxy(x2, 3);
		printf("㉮     이순신장군     ㉮\n");
		gotoxy(x2, 4);
		printf("㉮                    ㉮\n");
		gotoxy(x2, 5);
		printf("㉮   무기〔 대 포 〕  ㉮\n");
		gotoxy(x2, 6);
		printf("㉮                    ㉮\n");
		gotoxy(x2, 7);
		printf("㉮  총알속도 :  1.5   ㉮\n");
		gotoxy(x2, 8);
		printf("㉮  사정거리 :   5    ㉮\n");
		gotoxy(x2, 9);
		printf("㉮  총알개수 :   7    ㉮\n");
		gotoxy(x2, 10);
		printf("㉮  장전시간 :  1.5   ㉮\n");
		gotoxy(x2, 11);
		printf("㉮  이동속도 :   1    ㉮\n");
		gotoxy(x2, 12);
		printf("㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮\n");
	}
	else {
		gotoxy(x2, 1);
		printf("■■■■■■■■■■■■\n");
		gotoxy(x2, 2);
		printf("■                    ■\n");
		gotoxy(x2, 3);
		printf("■     이순신장군     ■\n");
		gotoxy(x2, 4);
		printf("■                    ■\n");
		gotoxy(x2, 5);
		printf("■   무기〔 대 포 〕  ■\n");
		gotoxy(x2, 6);
		printf("■                    ■\n");
		gotoxy(x2, 7);
		printf("■  총알속도 :  1.5   ■\n");
		gotoxy(x2, 8);
		printf("■  사정거리 :   5    ■\n");
		gotoxy(x2, 9);
		printf("■  총알개수 :   7    ■\n");
		gotoxy(x2, 10);
		printf("■  장전시간 :  1.5   ■\n");
		gotoxy(x2, 11);
		printf("■  이동속도 :   1    ■\n");
		gotoxy(x2, 12);
		printf("■■■■■■■■■■■■\n");
	}
}
void c3(short a) {
	int x3 = 84;
	if (a == 0) {
		gotoxy(x3, 1);
		printf("㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮\n");
		gotoxy(x3, 2);
		printf("㉮                    ㉮\n");
		gotoxy(x3, 3);
		printf("㉮     세 종 대 왕    ㉮\n");
		gotoxy(x3, 4);
		printf("㉮                    ㉮\n");
		gotoxy(x3, 5);
		printf("㉮   무기〔 한 글 〕  ㉮\n");
		gotoxy(x3, 6);
		printf("㉮                    ㉮\n");
		gotoxy(x3, 7);
		printf("㉮  총알속도 :  0.5   ㉮\n");
		gotoxy(x3, 8);
		printf("㉮  사정거리 :   6    ㉮\n");
		gotoxy(x3, 9);
		printf("㉮  총알개수 :   7    ㉮\n");
		gotoxy(x3, 10);
		printf("㉮  장전시간 :  0.6   ㉮\n");
		gotoxy(x3, 11);
		printf("㉮  이동속도 :  0.6   ㉮\n");
		gotoxy(x3, 12);
		printf("㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮\n");
	}
	else {
		gotoxy(x3, 1);
		printf("■■■■■■■■■■■■\n");
		gotoxy(x3, 2);
		printf("■                    ■\n");
		gotoxy(x3, 3);
		printf("■     세 종 대 왕    ■\n");
		gotoxy(x3, 4);
		printf("■                    ■\n");
		gotoxy(x3, 5);
		printf("■   무기〔 한 글 〕  ■\n");
		gotoxy(x3, 6);
		printf("■                    ■\n");
		gotoxy(x3, 7);
		printf("■  총알속도 :  0.5   ■\n");
		gotoxy(x3, 8);
		printf("■  사정거리 :   6    ■\n");
		gotoxy(x3, 9);
		printf("■  총알개수 :   7    ■\n");
		gotoxy(x3, 10);
		printf("■  장전시간 :  0.6   ■\n");
		gotoxy(x3, 11);
		printf("■  이동속도 :  0.6   ■\n");
		gotoxy(x3, 12);
		printf("■■■■■■■■■■■■\n");
	}
}
void c4(short a) {
	int x1 = 12;
	if (a == 0) {
		gotoxy(x1, 17);
		printf("㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮\n");
		gotoxy(x1, 18);
		printf("㉮                    ㉮\n");
		gotoxy(x1, 19);
		printf("㉮     안  중  근     ㉮\n");
		gotoxy(x1, 20);
		printf("㉮                    ㉮\n");
		gotoxy(x1, 21);
		printf("㉮   무기〔 권 총 〕  ㉮\n");
		gotoxy(x1, 22);
		printf("㉮                    ㉮\n");
		gotoxy(x1, 23);
		printf("㉮  총알속도 :  0.8   ㉮\n");
		gotoxy(x1, 24);
		printf("㉮  사정거리 :   10   ㉮\n");
		gotoxy(x1, 25);
		printf("㉮  총알개수 :   11   ㉮\n");
		gotoxy(x1, 26);
		printf("㉮  장전시간 :  0.5   ㉮\n");
		gotoxy(x1, 27);
		printf("㉮  이동속도 :  0.6   ㉮\n");
		gotoxy(x1, 28);
		printf("㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮\n");
	}
	else {
		gotoxy(x1, 17);
		printf("■■■■■■■■■■■■\n");
		gotoxy(x1, 18);
		printf("■                    ■\n");
		gotoxy(x1, 19);
		printf("■     안  중  근     ■\n");
		gotoxy(x1, 20);
		printf("■                    ■\n");
		gotoxy(x1, 21);
		printf("■   무기〔 권 총 〕  ■\n");
		gotoxy(x1, 22);
		printf("■                    ■\n");
		gotoxy(x1, 23);
		printf("■  총알속도 :  0.8   ■\n");
		gotoxy(x1, 24);
		printf("■  사정거리 :   10   ■\n");
		gotoxy(x1, 25);
		printf("■  총알개수 :   11   ■\n");
		gotoxy(x1, 26);
		printf("■  장전시간 :  0.5   ■\n");
		gotoxy(x1, 27);
		printf("■  이동속도 :  0.6   ■\n");
		gotoxy(x1, 28);
		printf("■■■■■■■■■■■■\n");
	}
}
void c5(short a) {
	int x2 = 48;

	if (a == 0) {
		gotoxy(x2, 17);
		printf("㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮\n");
		gotoxy(x2, 18);
		printf("㉮                    ㉮\n");
		gotoxy(x2, 19);
		printf("㉮     국  민  들     ㉮\n");
		gotoxy(x2, 20);
		printf("㉮                    ㉮\n");
		gotoxy(x2, 21);
		printf("㉮  무기〔 저격총 〕  ㉮\n");
		gotoxy(x2, 22);
		printf("㉮                    ㉮\n");
		gotoxy(x2, 23);
		printf("㉮  총알속도 :   6    ㉮\n");
		gotoxy(x2, 24);
		printf("㉮  사정거리 :   15   ㉮\n");
		gotoxy(x2, 25);
		printf("㉮  총알개수 :   2    ㉮\n");
		gotoxy(x2, 26);
		printf("㉮  장전시간 :   2    ㉮\n");
		gotoxy(x2, 27);
		printf("㉮  이동속도 :  0.8   ㉮\n");
		gotoxy(x2, 28);
		printf("㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮\n");
	}
	else {
		gotoxy(x2, 17);
		printf("■■■■■■■■■■■■\n");
		gotoxy(x2, 18);
		printf("■                    ■\n");
		gotoxy(x2, 19);
		printf("■     국  민  들     ■\n");
		gotoxy(x2, 20);
		printf("■                    ■\n");
		gotoxy(x2, 21);
		printf("■  무기〔 저격총 〕  ■\n");
		gotoxy(x2, 22);
		printf("■                    ■\n");
		gotoxy(x2, 23);
		printf("■  총알속도 :   6    ■\n");
		gotoxy(x2, 24);
		printf("■  사정거리 :   15   ■\n");
		gotoxy(x2, 25);
		printf("■  총알개수 :   2    ■\n");
		gotoxy(x2, 26);
		printf("■  장전시간 :   2    ■\n");
		gotoxy(x2, 27);
		printf("■  이동속도 :  0.8   ■\n");
		gotoxy(x2, 28);
		printf("■■■■■■■■■■■■\n");
	}
}
void c6(short a) {
	int x3 = 84;

	if (a == 0) {
		gotoxy(x3, 17);
		printf("㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮\n");
		gotoxy(x3, 18);
		printf("㉮                    ㉮\n");
		gotoxy(x3, 19);
		printf("㉮     대  통  령     ㉮\n");
		gotoxy(x3, 20);
		printf("㉮                    ㉮\n");
		gotoxy(x3, 21);
		printf("㉮  무기〔 기관총 〕  ㉮\n");
		gotoxy(x3, 22);
		printf("㉮                    ㉮\n");
		gotoxy(x3, 23);
		printf("㉮  총알속도 :   6    ㉮\n");
		gotoxy(x3, 24);
		printf("㉮  사정거리 :   8    ㉮\n");
		gotoxy(x3, 25);
		printf("㉮  총알개수 :   30   ㉮\n");
		gotoxy(x3, 26);
		printf("㉮  장전시간 :  2.3   ㉮\n");
		gotoxy(x3, 27);
		printf("㉮  이동속도 :   1    ㉮\n");
		gotoxy(x3, 28);
		printf("㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮\n");
	}
	else {
		gotoxy(x3, 17);
		printf("■■■■■■■■■■■■\n");
		gotoxy(x3, 18);
		printf("■                    ■\n");
		gotoxy(x3, 19);
		printf("■     대  통  령     ■\n");
		gotoxy(x3, 20);
		printf("■                    ■\n");
		gotoxy(x3, 21);
		printf("■  무기〔 기관총 〕  ■\n");
		gotoxy(x3, 22);
		printf("■                    ■\n");
		gotoxy(x3, 23);
		printf("■  총알속도 :   6    ■\n");
		gotoxy(x3, 24);
		printf("■  사정거리 :   8    ■\n");
		gotoxy(x3, 25);
		printf("■  총알개수 :   30   ■\n");
		gotoxy(x3, 26);
		printf("■  장전시간 :  2.3   ■\n");
		gotoxy(x3, 27);
		printf("■  이동속도 :   1    ■\n");
		gotoxy(x3, 28);
		printf("■■■■■■■■■■■■\n");
	}
}

//랭크 화면 중 정적인 것들을 그려주는 함수
void drawRank_Static(void) {
	short x1 = 22, x2 = 54, x3 = 86;
	gotoxy(2, 15);
	printf("뒤로가기뒤로가기!!!!!!");
	gotoxy(4, 14);
	printf("로");
	gotoxy(4, 16);
	printf("로");
	gotoxy(6, 13);
	printf("가");
	gotoxy(6, 17);
	printf("가");
	gotoxy(8, 12);
	printf("기");
	gotoxy(8, 18);
	printf("기");
	gotoxy(x1, 2);
	printf("㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮\n");
	gotoxy(x1, 3);
	printf("㉮                    ㉮\n");
	gotoxy(x1, 4);
	printf("㉮     단 군 왕 검    ㉮\n");
	gotoxy(x1, 5);
	printf("㉮                    ㉮\n");
	gotoxy(x1, 6);
	printf("㉮    최고 스테이지   ㉮\n");
	gotoxy(x1, 7);
	printf("㉮      《     》     ㉮\n");
	gotoxy(x1, 8);
	printf("㉮                    ㉮\n");
	gotoxy(x1, 9);
	printf("㉮      최고 점수     ㉮\n");
	gotoxy(x1, 10);
	printf("㉮     《       》    ㉮\n");
	gotoxy(x1, 11);
	printf("㉮                    ㉮\n");
	gotoxy(x1, 12);
	printf("㉮                    ㉮\n");
	gotoxy(x1, 13);
	printf("㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮\n");

	gotoxy(x2, 2);
	printf("㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮\n");
	gotoxy(x2, 3);
	printf("㉮                    ㉮\n");
	gotoxy(x2, 4);
	printf("㉮     이순신장군     ㉮\n");
	gotoxy(x2, 5);
	printf("㉮                    ㉮\n");
	gotoxy(x2, 6);
	printf("㉮    최고 스테이지   ㉮\n");
	gotoxy(x2, 7);
	printf("㉮      《     》     ㉮\n");
	gotoxy(x2, 8);
	printf("㉮                    ㉮\n");
	gotoxy(x2, 9);
	printf("㉮      최고 점수     ㉮\n");
	gotoxy(x2, 10);
	printf("㉮     《       》    ㉮\n");
	gotoxy(x2, 11);
	printf("㉮                    ㉮\n");
	gotoxy(x2, 12);
	printf("㉮                    ㉮\n");
	gotoxy(x2, 13);
	printf("㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮\n");

	gotoxy(x3, 2);
	printf("㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮\n");
	gotoxy(x3, 3);
	printf("㉮                    ㉮\n");
	gotoxy(x3, 4);
	printf("㉮     세 종 대 왕    ㉮\n");
	gotoxy(x3, 5);
	printf("㉮                    ㉮\n");
	gotoxy(x3, 6);
	printf("㉮    최고 스테이지   ㉮\n");
	gotoxy(x3, 7);
	printf("㉮      《     》     ㉮\n");
	gotoxy(x3, 8);
	printf("㉮                    ㉮\n");
	gotoxy(x3, 9);
	printf("㉮      최고 점수     ㉮\n");
	gotoxy(x3, 10);
	printf("㉮     《       》    ㉮\n");
	gotoxy(x3, 11);
	printf("㉮                    ㉮\n");
	gotoxy(x3, 12);
	printf("㉮                    ㉮\n");
	gotoxy(x3, 13);
	printf("㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮\n");

	gotoxy(x1, 17);
	printf("㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮\n");
	gotoxy(x1, 18);
	printf("㉮                    ㉮\n");
	gotoxy(x1, 19);
	printf("㉮     안  중  근     ㉮\n");
	gotoxy(x1, 20);
	printf("㉮                    ㉮\n");
	gotoxy(x1, 21);
	printf("㉮    최고 스테이지   ㉮\n");
	gotoxy(x1, 22);
	printf("㉮      《     》     ㉮\n");
	gotoxy(x1, 23);
	printf("㉮                    ㉮\n");
	gotoxy(x1, 24);
	printf("㉮      최고 점수     ㉮\n");
	gotoxy(x1, 25);
	printf("㉮     《       》    ㉮\n");
	gotoxy(x1, 26);
	printf("㉮                    ㉮\n");
	gotoxy(x1, 27);
	printf("㉮                    ㉮\n");
	gotoxy(x1, 28);
	printf("㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮\n");

	gotoxy(x2, 17);
	printf("㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮\n");
	gotoxy(x2, 18);
	printf("㉮                    ㉮\n");
	gotoxy(x2, 19);
	printf("㉮     국  민  들     ㉮\n");
	gotoxy(x2, 20);
	printf("㉮                    ㉮\n");
	gotoxy(x2, 21);
	printf("㉮    최고 스테이지   ㉮\n");
	gotoxy(x2, 22);
	printf("㉮      《     》     ㉮\n");
	gotoxy(x2, 23);
	printf("㉮                    ㉮\n");
	gotoxy(x2, 24);
	printf("㉮      최고 점수     ㉮\n");
	gotoxy(x2, 25);
	printf("㉮     《       》    ㉮\n");
	gotoxy(x2, 26);
	printf("㉮                    ㉮\n");
	gotoxy(x2, 27);
	printf("㉮                    ㉮\n");
	gotoxy(x2, 28);
	printf("㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮\n");

	gotoxy(x3, 17);
	printf("㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮\n");
	gotoxy(x3, 18);
	printf("㉮                    ㉮\n");
	gotoxy(x3, 19);
	printf("㉮     대  통  령     ㉮\n");
	gotoxy(x3, 20);
	printf("㉮                    ㉮\n");
	gotoxy(x3, 21);
	printf("㉮    최고 스테이지   ㉮\n");
	gotoxy(x3, 22);
	printf("㉮      《     》     ㉮\n");
	gotoxy(x3, 23);
	printf("㉮                    ㉮\n");
	gotoxy(x3, 24);
	printf("㉮      최고 점수     ㉮\n");
	gotoxy(x3, 25);
	printf("㉮     《       》    ㉮\n");
	gotoxy(x3, 26);
	printf("㉮                    ㉮\n");
	gotoxy(x3, 27);
	printf("㉮                    ㉮\n");
	gotoxy(x3, 28);
	printf("㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮㉮\n");
}

//랭크 화면 중 동적인 것들을 그려주는 함수
void drawRank_Dynamic(void) {
	fp1 = fopen("단군왕검.txt", "a+");
	fp2 = fopen("이순신장군.txt", "a+");
	fp3 = fopen("세종대왕.txt", "a+");
	fp4 = fopen("안중근.txt", "a+");
	fp5 = fopen("국민들.txt", "a+");
	fp6 = fopen("대통령.txt", "a+");
	fscanf(fp1, "%d%d", &highstage[0], &highscore[0]);
	fscanf(fp2, "%d%d", &highstage[1], &highscore[1]);
	fscanf(fp3, "%d%d", &highstage[2], &highscore[2]);
	fscanf(fp4, "%d%d", &highstage[3], &highscore[3]);
	fscanf(fp5, "%d%d", &highstage[4], &highscore[4]);
	fscanf(fp6, "%d%d", &highstage[5], &highscore[5]);

	//빨간색으로 변경
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

//상점 중 정적인 것들을 그려주는 함수
void drawStore_Static(void) {
	gotoxy(80, 3);
	printf("S T A G E 『       』");
	gotoxy(70, 5);
	printf("┌────────────┳───────────┳────────────┐");
	gotoxy(70, 6);
	printf("│  ≡≡≡≡≡┃           ┃            │");
	gotoxy(70, 7);
	printf("│            ┗━━━━━━━━━━━┛            │");
	gotoxy(70, 8);
	printf("│                                     │");
	gotoxy(70, 9);
	printf("│  SCORE【       】│    BULLET   [   ]│");
	gotoxy(70, 10);
	printf("│  MONEY【       】│ RELOAD SPEED[   ]│");

	gotoxy(70, 11);
	printf("└─────────────────────────────────────┘");

	gotoxy(67, 12);
	printf("┌───────────────────────────────────────────┐");
	gotoxy(67, 13);
	printf("│  ┏━  ENEMY [    /    |¤〔    /   〕] ━━┓ │ ");
	gotoxy(67, 14);
	printf("│  ┃       a b c d e f g h i j k l m      ┃ │ ");
	gotoxy(67, 15);
	printf("│  ┃       n o p q r s t u v w x y z      ┃ │ ");
	gotoxy(67, 16);
	printf("│  ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ │ ");
	gotoxy(67, 17);
	printf("│                                           │ ");
	gotoxy(67, 18);
	printf("│         BULLET〔400〕                     │ ");
	gotoxy(67, 19);
	printf("│                                           │ ");
	gotoxy(67, 20);
	printf("│       DISTANCE〔500〕                     │ ");
	gotoxy(67, 21);
	printf("│                                           │ ");
	gotoxy(67, 22);
	printf("│   BULLET SPEED〔400〕                     │ ");
	gotoxy(67, 23);
	printf("│                                           │ ");
	gotoxy(67, 24);
	printf("│     MOVE SPEED〔500〕                     │ ");
	gotoxy(67, 25);
	printf("│                                           │ ");
	gotoxy(67, 26);
	printf("│                                           │ ");
	gotoxy(67, 27);
	printf("│                                           │ ");
	gotoxy(67, 28);
	printf("└───────────────────────────────────────────┘");

}

//상점 중 동적인 것들을 그려주는 함수(캐릭터 넘버를 매개변수로 받음)
void drawStore_Dynamic(short chnum) {
	//장전시간을 초단위로 출력
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

//상점시작 시 상점에 대한 설명을 그려주는 함수
void displayStoreTime(void) {
	setColor(1);
	gotoxy(22, 5);
	printf("『 S T O R E  T I M E 』");
	gotoxy(19, 8);
	printf("Θ BULLET : 총알 개수");
	gotoxy(19, 10);
	printf("Θ DISTANCE : 사정 거리");
	gotoxy(19, 12);
	printf("Θ BULLET SPEED : 총알 속도");
	gotoxy(19, 14);
	printf("Θ MOVE SPEED : 캐릭터 이동 속도");
	gotoxy(19, 18);
	printf("Ο ¤ : 게임이 끝나는 적의 수");
	gotoxy(19, 20);
	printf("Ο w,↑ : 항목 위로 이동");
	gotoxy(19, 22);
	printf("Ο s,↓ : 항목 아래로 이동");
	gotoxy(19, 24);
	printf("Ο → : 업그레이드");
	gotoxy(19, 26);
	printf("Ο ← : 다운그레이드");
	setColor(0);
}


//맞춘 적의 수를 실시간으로 display하는 함수(매개변수로 맞춘 적의 수를 받음)
void displayhitEnemy(short hitEnemy) {
	Sleep(1);
	gotoxy(82, 13);
	printf("%2d", hitEnemy);
}

//돈을 실시간으로 display하는 함수(매개변수로 돈을 받음)
void displayMoney(short money) {
	gotoxy(81, 10);
	printf("%5d", money);
}

//점수를 실시간으로 display하는 함수(매개변수로 점수를 받음)
void displayScore(short score) {
	Sleep(1);
	gotoxy(81, 9);
	printf("%5d", score);
}

//총알의 수를 실시간으로 display하는 함수(매개변수로 총알을 받음)
void displayBulletNum(short bullet){
	Sleep(1);
	setColor(9);
	gotoxy(104, 9);
	printf("%3d", bullet);
	setColor(0);
}

//현재 화면 상에 남아 있는 적의 수를 실시간으로 display하는 함수(매개변수로 현재 적의 수를 받음)
void displayCurrentEnemy(short currentenemy) {
	if (currentenemy == 1)	current_enemy += 1;
	else if (currentenemy == -1)	current_enemy -= 1;
	Sleep(1);
	gotoxy(96, 13);
	printf("%2d ", current_enemy);
}


//캐릭터가 죽었을 때의 메뉴화면을 그려줌
void drawEndMenu(short num) {
	switch (num) {
	case 1:
		gotoxy(11, 13);
		printf("선택선택선택선택");
		gotoxy(11, 14);
		printf("선            택");
		gotoxy(11, 15);
		printf("선  게임종료  택");
		gotoxy(11, 16);
		printf("선            택");
		gotoxy(11, 17);
		printf("선택선택선택선택");

		gotoxy(42, 13);
		printf("ㄱㄷㄴㄹㅁㅂㅅㅇ");
		gotoxy(42, 14);
		printf("ㅈ            ㅊ");
		gotoxy(42, 15);
		printf("ㅋ  다시하기  ㅌ");
		gotoxy(42, 16);
		printf("ㅍ            ㅎ");
		gotoxy(42, 17);
		printf("ㄱㄷㄴㄹㅁㅂㅅㅇ");
		break;
	case 2:
		gotoxy(11, 13);
		printf("ㄱㄷㄴㄹㅁㅂㅅㅇ");
		gotoxy(11, 14);
		printf("ㅈ            ㅊ");
		gotoxy(11, 15);
		printf("ㅋ  게임종료  ㅌ");
		gotoxy(11, 16);
		printf("ㅍ            ㅎ");
		gotoxy(11, 17);
		printf("ㄱㄷㄴㄹㅁㅂㅅㅇ");

		gotoxy(42, 13);
		printf("선택선택선택선택");
		gotoxy(42, 14);
		printf("선            택");
		gotoxy(42, 15);
		printf("선  다시하기  택");
		gotoxy(42, 16);
		printf("선            택");
		gotoxy(42, 17);
		printf("선택선택선택선택");
	}
}

//캐릭터가 죽었을 때 실행되며, 만약 해당 캐릭터의 최고점수라면 파일을 열어 저장한다(매개변수로 캐릭터의 number을 받음)
void saveHighscore(short pnum) {
	//최고기록이라면 파일에 저장
	if (previousStage <= stage) {
		if(previousScore <= score){
			switch (pnum) {
			case 1:
				fp1 = fopen("단군왕검.txt", "w+");
				fprintf(fp1, "%d %d", stage, score);
				fclose(fp1);
				break;
			case 2:
				fp2 = fopen("이순신장군.txt", "w+");
				fprintf(fp2, "%d %d", stage, score);
				fclose(fp2);
				break;
			case 3:
				fp3 = fopen("세종대왕.txt", "w+");
				fprintf(fp3, "%d %d", stage, score);
				fclose(fp3);
				break;
			case 4:
				fp4 = fopen("안중근.txt", "w+");
				fprintf(fp4, "%d %d", stage, score);
				fclose(fp4);
				break;
			case 5:
				fp5 = fopen("국민들.txt", "w+");
				fprintf(fp5, "%d %d", stage, score);
				fclose(fp5);
				break;
			case 6:
				fp6 = fopen("대통령.txt", "w+");
				fprintf(fp6, "%d %d", stage, score);
				fclose(fp6);
				break;
			}

		}
	}
	go=selectEndmenu();
}

//캐릭터가 죽었을 때 다시할 건지 종료할 건지 선택하는 메뉴를 선택하는 함수
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


//스테이지 시작 직전, 3초 카운터를 할 때, 스테이지 정보와 이동키와 발사키의 설명을 그려주는 함수
void loadingStage(void) {
	short enemyspeed = sstage[stage].displayenemyspeed;
	setColor(12);
	gotoxy(28, 10);
	printf("STAGE 『 %d  』", stage);
	setColor(9);
	gotoxy(21, 12);
	printf("ENEMY〔 ");
	if (enemyspeed / 1000 == 1)	printf("%d.%1d초", enemyspeed / 1000, (enemyspeed / 100) % 10);
	else {
		if (enemyspeed % 100 != 0){
			if (enemyspeed % 10 != 0)	printf("0.%1d%1d%1d초", enemyspeed / 100, (enemyspeed % 100) / 10, enemyspeed % 10);
			else printf("0.%1d%1d초", enemyspeed / 100, (enemyspeed % 100) / 10);
		}
		else 	printf("0.%1d초", enemyspeed / 100);
	}

	printf(" 〕초마다 생성");
	setColor(12);
	gotoxy(17, 19);
	printf("           W                 ↑");
	gotoxy(17, 20);
	printf("발사 :   A   S    이동 :   ←  →");
	gotoxy(17, 21);
	printf("           D                 ↓");
	gotoxy(30, 15);
	setColor(0);
	printf("【    】");
	for (int i = 3; i >= 1; i--) {
		gotoxy(33, 15);
		switch (i) {
		case 3: printf("삼"); break;
		case 2: printf("이"); break;
		case 1: printf("일"); break;
		}
		Sleep(1000);
	}
}

//스테이지를 클리어 했을 때 STAGE CLEAR을 그려주는 함수
void drawStageClear(void) {
	setColor(15);
	gotoxy(7, 3);
	printf("스 테 이 지  클 리 어  스 테 이 지  클 리 어  스  테");
	gotoxy(7, 5);
	printf(" 이 지  클 리 어  스 테 이 지  클 리 어  스 테 이 지");
	gotoxy(7, 7);
	printf("클 리 어  스 테 이 지  클 리 어  스 테 이 지  클 리 어");
	gotoxy(7, 9);
	printf("스 테 이 지  클 리 어  스 테 이 지  클 리 어  스  테");
	gotoxy(7, 11);
	printf(" 이 지  클 리 어  스 테 이 지  클 리 어  스 테 이 지");
	gotoxy(7, 13);
	printf("클 리 어  스 테 이 지  클 리 어  스 테 이 지  클 리 어");
	gotoxy(7, 15);
	printf("스 테 이 지  클 리 어  스 테 이 지  클 리 어  스  테");
	gotoxy(7, 17);
	printf(" 이 지  클 리 어  스 테 이 지  클 리 어  스 테 이 지");
	gotoxy(7, 19);
	printf("클 리 어  스 테 이 지  클 리 어  스 테 이 지  클 리 어");
	gotoxy(7, 21);
	printf("스 테 이 지  클 리 어  스 테 이 지  클 리 어  스  테");
	gotoxy(7, 23);
	printf(" 이 지  클 리 어  스 테 이 지  클 리 어  스 테 이 지");
	gotoxy(7, 25);
	printf("클 리 어  스 테 이 지  클 리 어  스 테 이 지  클 리 어");
	gotoxy(7, 27);
	printf("스 테 이 지  클 리 어  스 테 이 지  클 리 어  스  테");
	setColor(0);
	//다른 키들은 무시
	GetAsyncKeyState(13);
	GetAsyncKeyState(83);
	GetAsyncKeyState(87);
	GetAsyncKeyState(65);
	GetAsyncKeyState(68);
}

//스테이지를 클리어 했을 때 다음 스테이지로 넘어가는 함수
void goNextStage(void) {
	clearBattleGround();
	PlaySound(NULL, 0, 0);
	PlaySound(TEXT("clearMusic2.wav"), NULL, SND_FILENAME | SND_ASYNC);
	for (int y = 0; y < 32; y++)
		for (int x = 0; x < 120; x++)	gamemap[y][x] = 0;
	//스테이지를 클리어했으니 변수들 초기화
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


//경기장의 테두리를 그려주는 함수
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
				printf("한");
		}
	}
	for (int y = MARGIN_Y - 1; y < HEIGHT - MARGIN_Y + 1; y++) {
		for (int x = (WIDTH / 2) + 4; x < WIDTH - MARGIN_X; x += 2) {
			gotoxy(x, y);
			printf("글");
		}
	}
	for (int y = MARGIN_Y; y < HEIGHT - MARGIN_Y; y++) {
		for (int x = (WIDTH / 2) + 6; x < WIDTH - MARGIN_X - 2; x += 2) {
			gotoxy(x, y);
			printf("  ");
		}
	}
}

//경기장 안을 공백으로 채워 깔끔하게 지워주는 함수
void clearBattleGround(void) {
	for (int y = 3; y < 29; y++) {
		for (int x = 7; x < 61; x += 2) {
			gotoxy(x, y);
			printf("  ");
		}
	}
}