#define _CRT_SECURE_NO_WARNINGS
//�ߺ� ���� ����
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

/*�� ĳ���͸��� �ְ��������� �ְ� ������ ����Ǿ� �ִ� ����*/
FILE* fp1;
FILE* fp2;
FILE* fp3;
FILE* fp4;
FILE* fp5;
FILE* fp6;

/*���� ����*/

//��
short money;
//����
short score;
//��������
short stage;
//�� ĳ����
int myCharacter;
//������ ������ ���� ���������� ������ �����ϴ� ���� (�ְ� ������ �Ǻ��ϱ� ���� ����)
int previousStage;
int previousScore;
//1�� �� �޴�ȭ��, 2�� �� ����, 3�� ���� �� ���� �ٸ� ȭ��
short go;

// �̹��� ����� ����
HDC consoleDC, imageDC;
HBITMAP imageMap;
HWND consoleWindow;


/*�Լ� ����*/

//���� ���� �� ����Ǵ� �⺻ �������� ���� �Լ�
void beforeStart(void);
//�� �������� �ʱ�ȭ
void Init(void);
//�����ð� ����
void startStore(void);
//���� ����
void startGame(void);