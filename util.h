#include "main.h"

//WIDTH = �ܼ�â�� ���� ����(120) | HEIGHT = �ܼ�â�� ���� ����(32)
#define WIDTH 120
#define HEIGHT 32

//MARGIN = ������ �ܼ�â ������ ����
#define MARGIN_X 4
#define MARGIN_Y 2


/*���� ����*/

//���θ޴������� �޴� ������ ���� ����(1:����ȭ��, 2:��ŷȭ��, 3:����ȭ��, 4:��������)
int mainmenuNumber;

//������� ũ�Ⱑ ��� 2���� �迭 ���� , gamemap[y][x]
int gamemap[HEIGHT][WIDTH];

//���� ȭ�鿡 �����ִ� ���� ��
int current_enemy;

//�ְ� ������ �ְ� ���������� �����ϴ� �迭(�� ĳ���͸��� �����ϹǷ� 6���� ���� �ʿ�)
int highstage[6];
int highscore[6];



/*������� �Լ���*/

//Ŀ���� �����ִ� �Լ�
void hideCursor(void);

//�ܼ�ũ�⸦ ���ϴ� �Լ�(���� ����, ���� ����)
void resizeConsole(short console_w, short console_h);

//Ŀ���� ��ǥ�� �̵���Ű�� �Լ�(x,y)
void gotoxy(short x, short y);

//�̹����� ����ϴ� �Լ�(�����̸��� ����, ���������ġx, ���������ġy, �̹������x, �̹������y)
void printImage(short pictureNum, short start_w, short start_h,short w, short h);

//gamemap�迭 ���� ��ǥ ���� ���� ��ġ�� ����� - ���� ������ ���� 3, ���� ��ġ�� 1, ���� �������� ���� 2�� �ٲ㼭 �Ѿ˰��� �浹ó���� ���� (�� �Լ��� ���� ������ ������ �����)
void setEnemyPosition_Gamemap(short enemyloaction_x, short enemyloaction_y);

//�۾� ������ �ٲٴ� �Լ�(�Ű������� ���ѹ��� ����(0~15))
void setColor(unsigned short text);



/*����ȭ�� ���� �Լ���*/

//���� ���� �� �ε�ȭ���� �׷��ִ� �Լ�
void loading(void);

//����ȭ�鿡�� �޴��� �����ϴ� �Լ�(��ȯ ���� 1�̸� ���ӽ���, 2�̸� ��ŷ, 3�̸� ���Ӽ���, 4�� ���� ���� ����)
int selectMainMenu(void);

//����ȭ���� number�� ���� ���õ� �׸��� �׷��� ȭ���� �׷��ִ� �Լ�
void drawMainMenu(short number);



/*ĳ����ȭ�� ���� �Լ���*/

//ĳ���Ͱ� ���õǾ��� �� �ش�ĳ������ ���� �ְ������� �ְ� ���������� ���Ͽ��� �ҷ��� ������ �������ִ� �Լ�
void getPreviousInformation(int myCharacter);

//ó�� ĳ���� ����ȭ���� �׷��ִ� �Լ�
void drawCharacter(void);

//ĳ���͸� �����ϴ� �Լ� (��ȯ���� ���� ���õ� ĳ���Ͱ� �޶���(1���� 6����))
int selectCharacter(void);

//�ش� ĳ���Ͱ� ���õ� ȭ���� �׷��ִ� �Լ�
int selectCharacternumber(short number);

//ĳ���� ���� ���� ȭ�� ǥ�� c1(ù�� ° ĳ����)~c6(���� ��° ĳ����)-(a�� 0�� ���� ���� ����� ȭ��, a�� 1�� ���� ���õ� ����� ȭ��)
void c1(short a);
void c2(short a);
void c3(short a);
void c4(short a);
void c5(short a);
void c6(short a);



/*��ũȭ�� ���� �Լ���*/

//��ũ ȭ�� �� ������ �͵��� �׷��ִ� �Լ�
void drawRank_Static(void);

//��ũ ȭ�� �� ������ �͵��� �׷��ִ� �Լ�
void drawRank_Dynamic(void);



/*�������� �Լ���*/

//���� �� ������ �͵��� �׷��ִ� �Լ�
void drawStore_Static(void);

//���� �� ������ �͵��� �׷��ִ� �Լ�(ĳ���� �ѹ��� �Ű������� ����)
void drawStore_Dynamic(short chnum);

//�������� �� ������ ���� ������ �׷��ִ� �Լ�
void displayStoreTime(void);


/*�ǽð� �� ���� �Լ���*/

//���� ���� ���� �ǽð����� display�ϴ� �Լ�(�Ű������� ���� ���� ���� ����)
void displayhitEnemy(short hitEnemy);

//���� �ǽð����� display�ϴ� �Լ�(�Ű������� ���� ����)
void displayMoney(short money);

//������ �ǽð����� display�ϴ� �Լ�(�Ű������� ������ ����)
void displayScore(short score);

//�Ѿ��� ���� �ǽð����� display�ϴ� �Լ�(�Ű������� �Ѿ��� ����)
void displayBulletNum(short bullet);

//���� ȭ�� �� ���� �ִ� ���� ���� �ǽð����� display�ϴ� �Լ�(�Ű������� ���� ���� ���� ����)
void displayCurrentEnemy(short currentenemy);



/*ĳ���Ͱ� ���� �� ����Ǵ� �Լ���*/

//ĳ���Ͱ� �׾��� ���� �޴�ȭ���� �׷���
void drawEndMenu(short num);

//ĳ���Ͱ� �׾��� �� ����Ǹ�, ���� �ش� ĳ������ �ְ�������� ������ ���� �����Ѵ�(�Ű������� ĳ������ number�� ����)
void saveHighscore(short pnum);

//ĳ���Ͱ� �׾��� �� �ٽ��� ���� ������ ���� �����ϴ� �޴��� �����ϴ� �Լ�
int selectEndmenu(void);



/*�������� ���� �Լ���*/

//�������� ���� ����, 3�� ī���͸� �� ��, �������� ������ �̵�Ű�� �߻�Ű�� ������ �׷��ִ� �Լ�
void loadingStage(void);

//���������� Ŭ���� ���� �� STAGE CLEAR�� �׷��ִ� �Լ�
void drawStageClear(void);

//���������� Ŭ���� ���� �� ���� ���������� �Ѿ�� �Լ�
void goNextStage(void);



/*���� ����� ���� �Լ���*/

//������� �׵θ��� �׷��ִ� �Լ�
void drawSide(void);

//����� ���� �������� ä�� ����ϰ� �����ִ� �Լ�
void clearBattleGround(void);