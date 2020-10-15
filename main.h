#define _CRT_SECURE_NO_WARNINGS
//중복 선언 방지
#ifndef __STDIO_H__
#define __STDIO_H__
#include <stdio.h>
#endif
#ifndef __WINDOWS_H__
#define __WINDOWS_H__
#include <windows.h>
#endif 
#ifndef __STDLIB_H__
#define __STDLIB_H__
#include <stdlib.h>
#endif 
#ifndef __CONIO_H__
#define __CONIO_H__
#include <conio.h>
#endif 
#ifndef __STDBOOL_H__
#define __STDBOOL_H__
#include <stdbool.h>
#endif 
#ifndef __TIME_H__
#define __TIME_H__
#include <time.h>
#endif 
#ifndef __PROCESS_H__
#define __PROCESS_H__
#include <process.h>
#endif 

/*각 캐릭터마다 최고스테이지와 최고 점수가 저장되어 있는 파일*/
FILE* fp1;
FILE* fp2;
FILE* fp3;
FILE* fp4;
FILE* fp5;
FILE* fp6;

/*변수 선언*/

//돈
short money;
//점수
short score;
//스테이지
short stage;
//내 캐릭터
int myCharacter;
//게임이 끝났을 때의 스테이지와 점수를 저장하는 변수 (최고 점수를 판별하기 위해 사용됨)
int previousStage;
int previousScore;
//1일 때 메뉴화면, 2일 때 종료, 3일 때는 그 외의 다른 화면
short go;

// 이미지 출력을 위함
HDC consoleDC, imageDC;
HBITMAP imageMap;
HWND consoleWindow;


/*함수 선언*/

//게임 시작 전 실행되는 기본 설정들의 실행 함수
void beforeStart(void);
//각 변수들의 초기화
void Init(void);
//상점시간 시작
void startStore(void);
//게임 시작
void startGame(void);