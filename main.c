#include "main.h"
#include "util.h"
#include "player.h"

//���� ������ ����
#pragma comment(lib,"winmm.lib")

//���� �Լ� ����
int main(void)
{
	//�ܼ� ����, ũ�� ���� ����
	beforeStart();
	//���� ���� ����
	while (go!=2) {	
		system("cls");
		//sm�� selectMainmenu, �� ����ȭ�鿡�� ������ �޴���(1:���ӽ���, 2:��ŷ, 3:���ӹ��, 4:����), �⺻��=1
		int sm = 1;

		//����ȭ������ ���
		PlaySound(NULL, 0, 0);
		PlaySound(TEXT("mainMusic.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
		Sleep(200);

		//������ �ٽ� ���۵Ǹ� �ʱ�ȭ�Ǿ�� �� ���� ������ �ʱ�ȭ
		Init();

		//�޴�ȭ�鿡�� ������ �޴��� sm�� ����(1~4)
		sm = selectMainMenu();

		//���� ��� ȭ��(3)
		if (sm == 3){
			//go�� 3�� ������ ����ȭ���� �ƴ� �ٸ� ȭ����
			go = 3;
			Sleep(200);
			int i = 1;
			while (1) {
				//����
				if (GetAsyncKeyState(68) & 1 || GetAsyncKeyState(VK_RIGHT) & 1)	i++;
				//����
				if (GetAsyncKeyState(65) & 1 || GetAsyncKeyState(VK_LEFT) & 1)	i--;

				//�ٸ� Ű���� ����
				GetAsyncKeyState(VK_UP);
				GetAsyncKeyState(VK_DOWN);
				GetAsyncKeyState(83);
				GetAsyncKeyState(87);

				//ù��° �������� �����ΰ��ų�, ������ �������� �ڷ� ���ų� BACKSPACE�� ������ ����ȭ������ ���ƿ�
				if (i == 0 || i == 10 || GetAsyncKeyState(8))	break;
				//�׷��� �ʴٸ� i���� ������ ���� ���� �����̳� ���� ������ ���
				else {
					Sleep(40);
					printImage(i, 0, 0, 1200, 640);
				}
			}
		}

		//��ŷ ȭ��(2)
		if (sm == 2){
			//go�� 3�� ������ ����ȭ���� �ƴ� �ٸ� ȭ����
			go = 3;
			Sleep(200);

			//��ũ ȭ�� �� ������ �͵��� �׷���
			drawRank_Static();
			//��ũ ȭ�� �� ������ �͵��� �׷���
			drawRank_Dynamic();

			while (1) {
				//BACKSPACE �Է� �� ����ȭ������ ���ƿ�
				if (GetAsyncKeyState(8)) {
					go = 1;
					system("cls");
					break;
				}

				//�ٸ� Ű���� ����
				GetAsyncKeyState(13);
				GetAsyncKeyState(VK_UP);
				GetAsyncKeyState(VK_DOWN);
				GetAsyncKeyState(83);
				GetAsyncKeyState(87);
			}
		}
		//���� ���� ȭ��(1)
		if (sm == 1) {
			//���� ����ȭ���� ����ȭ���̶��
			if (go == 1) {
				//go�� 3�� ������ ����ȭ���� �ƴ� �ٸ� ȭ����
				go = 3;

				Sleep(200);
				//ĳ���� ����(mycharacter�� 1~6 �� ���õ� ĳ������ ��ȣ�� �����)
				myCharacter = selectCharacter();
				//mycharacter�� �ش�Ǵ� ĳ���� ������ ���� ����� ���� �ְ� ������ ���� �ְ� ���������� ������
				getPreviousInformation(myCharacter);

				//����ȭ���� �ƴ϶��
				if (go != 1) {
					//ĳ������ �ʱⰪ���� original�����鿡 ����(�������� �ɷ�ġ�� �ٿ�׷��̵� �� �� ���� ������ ������ �ȵǾ �ɷ�ġ�� �ּڰ��� �˾ƾ��ϱ� ����)
					originalmaxbullet = chter[myCharacter].max_bullet;
					originalmaxbulletdistance = chter[myCharacter].maxdistance_bullet;
					originalbulletspeed = chter[myCharacter].bulletspeed;
					originalplayerspeed = chter[myCharacter].playerspeed;

					//������ ������ �׵θ��� �׷���
					drawSide();
					//������ ȭ�� �� �������� �ʴ�, ������ �͵��� �׷���
					drawStore_Static();
					//������ �ִ� �ɷ�ġ���� �׷���
					for (int i = 1; i <= 8; i += 2)	displayChangeAbility(i, 11);
					//���� ����
					startGame();
				}
			}	
		}
	}
	system("cls");
	return 0;
}

void beforeStart(void){
	//�ܼ� ũ�� ����
	resizeConsole(WIDTH, HEIGHT);
	//Ŀ������� 
	hideCursor();
	//�� ����
	system("color 70");
	//ĳ���Ϳ� �������� ���� �ʱ�ȭ
	setInformation();
	//���� �ε�ȭ�� ���
	loading();
	setColor(0);
}
//������ �ٽ� ���۵Ǹ� �ʱ�ȭ�Ǿ�� �� ���� ������
void Init(void) {
	//gamemap�迭�� 0���� �ʱ�ȭ
	for (int y = 0; y < 32; y++)
		for (int x = 0; x < 120; x++) gamemap[y][x] = 0;
	//��
	money = 1000;
	//����
	score = 0;
	//�� ĳ����
	myCharacter = 0;
	//��������
	stage = 1;
	//����ȭ��
	go = 1;
	//���� �����ִ� ��
	current_enemy = 0;
	//�Ѿ�
	cntBullet = 0;
	//���� ��
	hitEnemy = 0;
	//�����ְ�����
	previousScore = 0;
	//�����ְ�������
	previousStage = 0;
	//4���� �ɷ�ġ�� ��������
	ability1 = 1, ability2 = 1, ability3 = 1, ability4 = 1;
	//4���� �ɷ�ġ�� ������ ������ �����ϴ� ����(1~7)
	a1 = 0, a2 = 0, a3 = 0, a4 = 0;
}
//���� ����
void startStore(void) {
	//�������� ����
	PlaySound(TEXT("gameMusic.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	Sleep(200);
	//������ ���� ������� ���Ӱ���忡 �׷���
	displayStoreTime();
	//�Ѿ˰����� ǥ��
	displayBulletNum(chter[myCharacter].max_bullet);
	//���� ǥ��
	displayMoney(money);
	//������ ǥ��
	displayScore(score);
	//���� ����
	gameGameStart(myCharacter, originalmaxbullet, originalmaxbulletdistance, originalbulletspeed, originalplayerspeed);
}
//���� ����
void startGame(void) {
	Sleep(200);
	//���� �ð� ����
	startStore();
	//Ű �Է� ���� ��, ����
	if (isstart == 1) {
		//�̵��� �߻�� ������� ����(�Ű������� ĳ���͸� �ѱ�)
		_beginthreadex(NULL, 0, KeyControl, (void*)myCharacter, 0, NULL);
		//�÷��̾��� ��ġ�� �ʱ�ȭ �ϰ� �Ѿ��� exist���� false�� �ʱ�ȭ
		reset(myCharacter);
		//��������(�Ű�����)�� ���� �� ���� ����
		createEnemy(stage);
		//isstart�� 2�� �Ǹ� ���� ��������
		if (isstart == 2)	goNextStage();
	}
}