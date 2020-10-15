#include "main.h"

/*����ü ����*/

//�÷��̾� ����ü ����(x,y)
typedef struct player {
	int x, y;
}Player;

//�� ����ü ����(x,y)
typedef struct enemy {
	int x, y;
}Enemy;

//�Ѿ� ����ü ����(x,y,exist)
typedef struct bullet
{
	int x, y;
	bool exist;
} Bullet;

//ĳ������ �Ӽ��� ��� ����ü ����(�̸�, ���� �̸�, �ִ� �Ѿ� ����, �ִ� �Ѿ� �����Ÿ�, �Ѿ� �ӵ�, ������ �ӵ�, ���� �ӵ�)
typedef struct player_attribute {
	char * name;
	char * armorname;
	int max_bullet;
	int maxdistance_bullet;
	int bulletspeed;
	int playerspeed;
	int reloadspeed;
}MyPlayer;

//���������� �Ӽ��� ��� ����ü ����(�� ���� �ӵ�, �� ���� ��, ���������� ������ ���� ��, ���������� Ŭ�����ϴ� ���� ��)
typedef struct stage {
	int displayenemyspeed;
	int enemynum;
	int enemynum_endstage;
	int enemynum_clearstage;
}Stage;



/*����ü ���� ����*/

//��(�ִ� 100)
Enemy enemy[100];
//�� �÷��̾�
Player myPlayer;
//�Ѿ�(�ִ� 100)
Bullet bullet[100];
//������ ĳ���͸� ���� �迭(1~6)
MyPlayer chter[7];
//��������(�ִ� 30��������)
Stage sstage[30];



/*���� ����*/

//������ �������� ���� 1, ���� ���������� �Ѿ ���� 2, ����� ���� 3�� ��ȯ
int isstart;
//�������� ��
int hitEnemy;
//�Ѿ��� ��(countBullet)
int cntBullet;
//4���� �ɷ�ġ�� ��������
int ability1, ability2, ability3, ability4;
//4���� �ɷ�ġ�� ������ ������ �����ϴ� ����(1~7)
int a1, a2, a3, a4;

//�������� �ɷ�ġ ���׷��̵�/�ٿ�׷��̵�� �ּҰ��� �����ϱ� ���� ������ (ĳ��ó�� ó�� ���� ������ ���� ����)
int originalmaxbullet;
int originalmaxbulletdistance;
int originalbulletspeed;
int originalplayerspeed;


/*�Լ�*/

/*�÷��̾� ���� �Լ�*/

//�����尡 �����ų �Լ� (ĳ������ �̵��� �߻縦 �۵���Ŵ)-(�Ű������� �ڽ��� ĳ���� number(1~6)�� ����)
unsigned _stdcall KeyControl (int *myp);
//�÷��̾��� ��ġ�� �ʱ�ȭ �ϰ� �Ѿ��� exist���� false�� �ʱ�ȭ�ϴ� �Լ�(�Ű������� �ڽ��� ĳ���� number(1~6)�� ����)
void reset(short myplayer);
//�÷��̾��� ������, ���������� ������ �ʱ�ȭ�ϴ� �Լ�
void setInformation(void);
//ĳ������ �ɷ�ġ�� ��ȭ��Ű�� �Լ�
void changeAbility(short num);
//ĳ������ �ɷ�ġ ��ȭ�� �׷��ִ� �Լ�
void displayChangeAbility(short num, short s);
//ĳ���Ϳ� ���� �ٸ� ����� �Ѿ��� �����ϴ� �Լ�(�Ű������� �ڽ��� ĳ���Ϳ� �Ѿ��� ������ ����)
void bulletShape(short myplayer, short dir);


/*��Ÿ �Լ�*/

//��(���ĺ�)�� ����Ǿ��ִ� �Լ�
void alphabet(short a);
//���� �����ϴ� �Լ�(�Ű������� stage�� ����)
void createEnemy(short stage);
//������ �������� �� ����Ǵ� �Լ�
int gameGameStart(short playernum, short originalmaxbullet, short originalmaxbulletdistance, short originalbulletspeed, short originalplayerspeed);