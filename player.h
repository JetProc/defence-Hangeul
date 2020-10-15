#include "main.h"

/*구조체 선언*/

//플레이어 구조체 선언(x,y)
typedef struct player {
	int x, y;
}Player;

//적 구조체 선언(x,y)
typedef struct enemy {
	int x, y;
}Enemy;

//총알 구조체 선언(x,y,exist)
typedef struct bullet
{
	int x, y;
	bool exist;
} Bullet;

//캐릭터의 속성이 담긴 구조체 선언(이름, 무기 이름, 최대 총알 갯수, 최대 총알 사정거리, 총알 속도, 움직임 속도, 장전 속도)
typedef struct player_attribute {
	char * name;
	char * armorname;
	int max_bullet;
	int maxdistance_bullet;
	int bulletspeed;
	int playerspeed;
	int reloadspeed;
}MyPlayer;

//스테이지의 속성이 담긴 구조체 선언(적 출현 속도, 총 적의 수, 스테이지가 끝나는 적의 수, 스테이지를 클리어하는 적의 수)
typedef struct stage {
	int displayenemyspeed;
	int enemynum;
	int enemynum_endstage;
	int enemynum_clearstage;
}Stage;



/*구조체 변수 선언*/

//적(최대 100)
Enemy enemy[100];
//내 플레이어
Player myPlayer;
//총알(최대 100)
Bullet bullet[100];
//각각의 캐릭터를 담을 배열(1~6)
MyPlayer chter[7];
//스테이지(최대 30스테이지)
Stage sstage[30];



/*변수 선언*/

//게임이 진행중일 때는 1, 다음 스테이지로 넘어갈 때는 2, 종료될 때는 3을 반환
int isstart;
//맞춘적의 수
int hitEnemy;
//총알의 수(countBullet)
int cntBullet;
//4개의 능력치의 증감변수
int ability1, ability2, ability3, ability4;
//4개의 능력치의 증감의 갯수를 저장하는 변수(1~7)
int a1, a2, a3, a4;

//상점에서 능력치 업그레이드/다운그레이드시 최소값을 저장하기 위한 변수들 (캐릭처가 처음 가진 고유의 값을 저장)
int originalmaxbullet;
int originalmaxbulletdistance;
int originalbulletspeed;
int originalplayerspeed;


/*함수*/

/*플레이어 관련 함수*/

//쓰레드가 실행시킬 함수 (캐릭터의 이동과 발사를 작동시킴)-(매개변수로 자신의 캐릭터 number(1~6)을 받음)
unsigned _stdcall KeyControl (int *myp);
//플레이어의 위치를 초기화 하고 총알의 exist값을 false로 초기화하는 함수(매개변수로 자신의 캐릭터 number(1~6)을 받음)
void reset(short myplayer);
//플레이어의 정보와, 스테이지의 값들을 초기화하는 함수
void setInformation(void);
//캐릭터의 능력치를 변화시키는 함수
void changeAbility(short num);
//캐릭터의 능력치 변화를 그려주는 함수
void displayChangeAbility(short num, short s);
//캐릭터에 따라 다른 모양의 총알을 저장하는 함수(매개변수로 자신의 캐릭터와 총알의 방향을 받음)
void bulletShape(short myplayer, short dir);


/*기타 함수*/

//적(알파벳)이 저장되어있는 함수
void alphabet(short a);
//적을 생성하는 함수(매개변수로 stage를 받음)
void createEnemy(short stage);
//게임이 시작했을 때 실행되는 함수
int gameGameStart(short playernum, short originalmaxbullet, short originalmaxbulletdistance, short originalbulletspeed, short originalplayerspeed);