#include "main.h"

//WIDTH = 콘솔창의 가로 길이(120) | HEIGHT = 콘솔창의 세로 길이(32)
#define WIDTH 120
#define HEIGHT 32

//MARGIN = 경기장과 콘솔창 사이의 간격
#define MARGIN_X 4
#define MARGIN_Y 2


/*변수 선언*/

//메인메뉴에서의 메뉴 선택할 때의 숫자(1:시작화면, 2:랭킹화면, 3:설명화면, 4:게임종료)
int mainmenuNumber;

//경기장의 크기가 담긴 2차원 배열 선언 , gamemap[y][x]
int gamemap[HEIGHT][WIDTH];

//현재 화면에 남아있는 적의 수
int current_enemy;

//최고 점수와 최고 스테이지를 저장하는 배열(각 캐릭터마다 저장하므로 6개의 공간 필요)
int highstage[6];
int highscore[6];



/*기능적인 함수들*/

//커서를 숨겨주는 함수
void hideCursor(void);

//콘솔크기를 정하는 함수(가로 길이, 세로 길이)
void resizeConsole(short console_w, short console_h);

//커서의 좌표를 이동시키는 함수(x,y)
void gotoxy(short x, short y);

//이미지를 출력하는 함수(파일이름의 숫자, 시작출력위치x, 시작출력위치y, 이미지출력x, 이미지출력y)
void printImage(short pictureNum, short start_w, short start_h,short w, short h);

//gamemap배열 상의 좌표 위에 적의 위치를 찍어줌 - 적의 왼쪽의 값은 3, 적의 위치는 1, 적의 오른쪽의 값은 2로 바꿔서 총알과의 충돌처리를 위함 (이 함수는 적이 생성될 때마다 실행됨)
void setEnemyPosition_Gamemap(short enemyloaction_x, short enemyloaction_y);

//글씨 색깔을 바꾸는 함수(매개변수로 색넘버를 받음(0~15))
void setColor(unsigned short text);



/*메인화면 관련 함수들*/

//게임 시작 전 로딩화면을 그려주는 함수
void loading(void);

//메인화면에서 메뉴를 선택하는 함수(반환 값이 1이면 게임시작, 2이면 랭킹, 3이면 게임설명, 4면 게임 종료 실행)
int selectMainMenu(void);

//메인화면의 number에 따라서 선택된 항목이 그려진 화면을 그려주는 함수
void drawMainMenu(short number);



/*캐릭터화면 관련 함수들*/

//캐릭터가 선택되었을 때 해당캐릭터의 이전 최고점수와 최고 스테이지를 파일에서 불러와 변수에 저장해주는 함수
void getPreviousInformation(int myCharacter);

//처음 캐릭터 선택화면을 그려주는 함수
void drawCharacter(void);

//캐릭터를 선택하는 함수 (반환값에 따라서 선택된 캐릭터가 달라짐(1부터 6까지))
int selectCharacter(void);

//해당 캐릭터가 선택된 화면을 그려주는 함수
int selectCharacternumber(short number);

//캐릭터 선택 시의 화면 표시 c1(첫번 째 캐릭터)~c6(여섯 번째 캐릭터)-(a가 0일 때는 원래 모양의 화면, a가 1일 때는 선택된 모양의 화면)
void c1(short a);
void c2(short a);
void c3(short a);
void c4(short a);
void c5(short a);
void c6(short a);



/*랭크화면 관련 함수들*/

//랭크 화면 중 정적인 것들을 그려주는 함수
void drawRank_Static(void);

//랭크 화면 중 동적인 것들을 그려주는 함수
void drawRank_Dynamic(void);



/*상점관련 함수들*/

//상점 중 정적인 것들을 그려주는 함수
void drawStore_Static(void);

//상점 중 동적인 것들을 그려주는 함수(캐릭터 넘버를 매개변수로 받음)
void drawStore_Dynamic(short chnum);

//상점시작 시 상점에 대한 설명을 그려주는 함수
void displayStoreTime(void);


/*실시간 값 변경 함수들*/

//맞춘 적의 수를 실시간으로 display하는 함수(매개변수로 맞춘 적의 수를 받음)
void displayhitEnemy(short hitEnemy);

//돈을 실시간으로 display하는 함수(매개변수로 돈을 받음)
void displayMoney(short money);

//점수를 실시간으로 display하는 함수(매개변수로 점수를 받음)
void displayScore(short score);

//총알의 수를 실시간으로 display하는 함수(매개변수로 총알을 받음)
void displayBulletNum(short bullet);

//현재 화면 상에 남아 있는 적의 수를 실시간으로 display하는 함수(매개변수로 현재 적의 수를 받음)
void displayCurrentEnemy(short currentenemy);



/*캐릭터가 죽은 뒤 실행되는 함수들*/

//캐릭터가 죽었을 때의 메뉴화면을 그려줌
void drawEndMenu(short num);

//캐릭터가 죽었을 때 실행되며, 만약 해당 캐릭터의 최고점수라면 파일을 열어 저장한다(매개변수로 캐릭터의 number을 받음)
void saveHighscore(short pnum);

//캐릭터가 죽었을 때 다시할 건지 종료할 건지 선택하는 메뉴를 선택하는 함수
int selectEndmenu(void);



/*스테이지 관련 함수들*/

//스테이지 시작 직전, 3초 카운터를 할 때, 스테이지 정보와 이동키와 발사키의 설명을 그려주는 함수
void loadingStage(void);

//스테이지를 클리어 했을 때 STAGE CLEAR을 그려주는 함수
void drawStageClear(void);

//스테이지를 클리어 했을 때 다음 스테이지로 넘어가는 함수
void goNextStage(void);



/*게임 경기장 관련 함수들*/

//경기장의 테두리를 그려주는 함수
void drawSide(void);

//경기장 안을 공백으로 채워 깔끔하게 지워주는 함수
void clearBattleGround(void);