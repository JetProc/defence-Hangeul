#include "main.h"
#include "util.h"
#include "player.h"

//음악 삽입을 위함
#pragma comment(lib,"winmm.lib")

//메인 함수 시작
int main(void)
{
	//콘솔 색깔, 크기 등을 조정
	beforeStart();
	//게임 루프 시작
	while (go!=2) {	
		system("cls");
		//sm은 selectMainmenu, 즉 메인화면에서 선택한 메뉴임(1:게임시작, 2:랭킹, 3:게임방법, 4:종료), 기본값=1
		int sm = 1;

		//메인화면음악 재생
		PlaySound(NULL, 0, 0);
		PlaySound(TEXT("mainMusic.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
		Sleep(200);

		//게임이 다시 시작되면 초기화되어야 할 각종 변수들 초기화
		Init();

		//메뉴화면에서 선택한 메뉴를 sm에 저장(1~4)
		sm = selectMainMenu();

		//게임 방법 화면(3)
		if (sm == 3){
			//go가 3일 때에는 메인화면이 아닌 다른 화면임
			go = 3;
			Sleep(200);
			int i = 1;
			while (1) {
				//다음
				if (GetAsyncKeyState(68) & 1 || GetAsyncKeyState(VK_RIGHT) & 1)	i++;
				//이전
				if (GetAsyncKeyState(65) & 1 || GetAsyncKeyState(VK_LEFT) & 1)	i--;

				//다른 키들은 무시
				GetAsyncKeyState(VK_UP);
				GetAsyncKeyState(VK_DOWN);
				GetAsyncKeyState(83);
				GetAsyncKeyState(87);

				//첫번째 사진에서 앞으로가거나, 마지막 사진에서 뒤로 가거나 BACKSPACE를 받으면 메인화면으로 돌아옴
				if (i == 0 || i == 10 || GetAsyncKeyState(8))	break;
				//그렇지 않다면 i값의 증감에 따라 이전 사진이나 다음 사진을 출력
				else {
					Sleep(40);
					printImage(i, 0, 0, 1200, 640);
				}
			}
		}

		//랭킹 화면(2)
		if (sm == 2){
			//go가 3일 때에는 메인화면이 아닌 다른 화면임
			go = 3;
			Sleep(200);

			//랭크 화면 중 정적인 것들을 그려줌
			drawRank_Static();
			//랭크 화면 중 동적인 것들을 그려줌
			drawRank_Dynamic();

			while (1) {
				//BACKSPACE 입력 시 메인화면으로 돌아옴
				if (GetAsyncKeyState(8)) {
					go = 1;
					system("cls");
					break;
				}

				//다른 키들은 무시
				GetAsyncKeyState(13);
				GetAsyncKeyState(VK_UP);
				GetAsyncKeyState(VK_DOWN);
				GetAsyncKeyState(83);
				GetAsyncKeyState(87);
			}
		}
		//게임 시작 화면(1)
		if (sm == 1) {
			//만약 지금화면이 메인화면이라면
			if (go == 1) {
				//go가 3일 때에는 메인화면이 아닌 다른 화면임
				go = 3;

				Sleep(200);
				//캐릭터 선택(mycharacter에 1~6 중 선택된 캐릭터의 번호가 저장됨)
				myCharacter = selectCharacter();
				//mycharacter에 해당되는 캐릭터 파일을 열어 저장된 이전 최고 점수와 이전 최고 스테이지를 저장함
				getPreviousInformation(myCharacter);

				//메인화면이 아니라면
				if (go != 1) {
					//캐릭터의 초기값들을 original변수들에 저장(상점에서 능력치를 다운그레이드 할 때 원래 값보다 낮으면 안되어서 능력치의 최솟값을 알아야하기 때문)
					originalmaxbullet = chter[myCharacter].max_bullet;
					originalmaxbulletdistance = chter[myCharacter].maxdistance_bullet;
					originalbulletspeed = chter[myCharacter].bulletspeed;
					originalplayerspeed = chter[myCharacter].playerspeed;

					//경기장과 상점의 테두리를 그려줌
					drawSide();
					//상점의 화면 중 움직이지 않는, 정적인 것들을 그려줌
					drawStore_Static();
					//상점에 있는 능력치들을 그려줌
					for (int i = 1; i <= 8; i += 2)	displayChangeAbility(i, 11);
					//게임 시작
					startGame();
				}
			}	
		}
	}
	system("cls");
	return 0;
}

void beforeStart(void){
	//콘솔 크기 변경
	resizeConsole(WIDTH, HEIGHT);
	//커서숨기기 
	hideCursor();
	//색 변경
	system("color 70");
	//캐릭터와 스테이지 정보 초기화
	setInformation();
	//게임 로딩화면 출력
	loading();
	setColor(0);
}
//게임이 다시 시작되면 초기화되어야 할 각종 변수들
void Init(void) {
	//gamemap배열을 0으로 초기화
	for (int y = 0; y < 32; y++)
		for (int x = 0; x < 120; x++) gamemap[y][x] = 0;
	//돈
	money = 1000;
	//점수
	score = 0;
	//내 캐릭터
	myCharacter = 0;
	//스테이지
	stage = 1;
	//현재화면
	go = 1;
	//현재 남아있는 적
	current_enemy = 0;
	//총알
	cntBullet = 0;
	//맞춘 적
	hitEnemy = 0;
	//이전최고점수
	previousScore = 0;
	//이전최고스테이지
	previousStage = 0;
	//4개의 능력치의 증감변수
	ability1 = 1, ability2 = 1, ability3 = 1, ability4 = 1;
	//4개의 능력치의 증감의 갯수를 저장하는 변수(1~7)
	a1 = 0, a2 = 0, a3 = 0, a4 = 0;
}
//상점 시작
void startStore(void) {
	//게임음악 시작
	PlaySound(TEXT("gameMusic.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	Sleep(200);
	//상점에 대한 설명들을 게임경기장에 그려줌
	displayStoreTime();
	//총알갯수를 표시
	displayBulletNum(chter[myCharacter].max_bullet);
	//돈을 표시
	displayMoney(money);
	//점수를 표시
	displayScore(score);
	//게임 시작
	gameGameStart(myCharacter, originalmaxbullet, originalmaxbulletdistance, originalbulletspeed, originalplayerspeed);
}
//게임 시작
void startGame(void) {
	Sleep(200);
	//상점 시간 시작
	startStore();
	//키 입력 받을 시, 시작
	if (isstart == 1) {
		//이동과 발사는 쓰레드로 실행(매개변수로 캐릭터를 넘김)
		_beginthreadex(NULL, 0, KeyControl, (void*)myCharacter, 0, NULL);
		//플레이어의 위치를 초기화 하고 총알의 exist값을 false로 초기화
		reset(myCharacter);
		//스테이지(매개변수)에 따른 적 생성 시작
		createEnemy(stage);
		//isstart가 2가 되면 다음 스테이지
		if (isstart == 2)	goNextStage();
	}
}