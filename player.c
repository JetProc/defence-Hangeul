#include "player.h"
#include "util.h"

cntBullet = 0;
ability1 = 1, ability2 = 1, ability3 = 1, ability4 = 1;
a1 = 0, a2 = 0, a3 = 0, a4 = 0;

//�����尡 �����ų �Լ� (ĳ������ �̵��� �߻縦 �۵���Ŵ)-(�Ű������� �ڽ��� ĳ���� number(1~6)�� ����)
unsigned _stdcall KeyControl(int* myp) {
	short pnum = myp;
	cntBullet = 0;
	while (isstart == 1) {
		//���� �̵�
		if (GetAsyncKeyState(VK_UP) & 0x8000){
			if (myPlayer.y >= 5 && gamemap[myPlayer.y - 1][myPlayer.x] == 0) {
				gotoxy(myPlayer.x, myPlayer.y);
				printf("  ");
				myPlayer.y--;
				gotoxy(myPlayer.x, myPlayer.y);

				if (myp == 1)	printf("��");
				else if (myp == 2)	printf("��");
				else if (myp == 3)	printf("��");
				else if (myp == 4)	printf("��");
				else if (myp == 5)	printf("��");
				else if (myp == 6)	printf("��");
				Sleep(chter[pnum].playerspeed * 2);
			}
		}
		//�Ʒ��� �̵�
		if (GetAsyncKeyState(VK_DOWN) & 0x8000){
			if (myPlayer.y <= 26 && gamemap[myPlayer.y + 1][myPlayer.x] == 0) {
				gotoxy(myPlayer.x, myPlayer.y);
				printf("  ");
				myPlayer.y++;
				gotoxy(myPlayer.x, myPlayer.y);

				if (myp == 1)	printf("��");
				else if (myp == 2)	printf("��");
				else if (myp == 3)	printf("��");
				else if (myp == 4)	printf("��");
				else if (myp == 5)	printf("��");
				else if (myp == 6)	printf("��");
				Sleep(chter[pnum].playerspeed * 2);
			}
		}
		//���� �̵�
		if (GetAsyncKeyState(VK_LEFT) & 0x8000){
			if (myPlayer.x > 8 && gamemap[myPlayer.y][myPlayer.x - 1] == 0) {

				gotoxy(myPlayer.x, myPlayer.y);
				printf(" ");
				myPlayer.x--;
				gotoxy(myPlayer.x, myPlayer.y);

				if (myp == 1)	printf("��");
				else if (myp == 2)	printf("��");
				else if (myp == 3)	printf("��");
				else if (myp == 4)	printf("��");
				else if (myp == 5)	printf("��");
				else if (myp == 6)	printf("��");
				Sleep(chter[pnum].playerspeed);
			}

		}
		//������ �̵�
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000){
			if (myPlayer.x < 58 && gamemap[myPlayer.y][myPlayer.x + 1] == 0) {
				gotoxy(myPlayer.x, myPlayer.y);
				printf("  ");
				myPlayer.x++;
				gotoxy(myPlayer.x, myPlayer.y);

				if (myp == 1)	printf("��");
				else if (myp == 2)	printf("��");
				else if (myp == 3)	printf("��");
				else if (myp == 4)	printf("��");
				else if (myp == 5)	printf("��");
				else if (myp == 6)	printf("��");
				Sleep(chter[pnum].playerspeed);
			}
		}
		//D(������ �߻�)
		if (GetAsyncKeyState(68)){
			if (cntBullet >= chter[pnum].max_bullet){
				gotoxy(106, 9);
				printf("R");
				Sleep(chter[pnum].reloadspeed);
				cntBullet = 0;
				for (int i = 0; i < chter[pnum].max_bullet; i++)	bullet[i].exist = false;
				displayBulletNum(chter[pnum].max_bullet - cntBullet);
			}
			else {
				displayBulletNum(chter[pnum].max_bullet - cntBullet - 1);
				bullet[cntBullet].x = myPlayer.x;
				bullet[cntBullet].y = myPlayer.y;

				for (int distance = 0; distance < chter[pnum].maxdistance_bullet; distance++) {
					if (bullet[cntBullet].exist == false) {
						Sleep(chter[pnum].bulletspeed);
						if (bullet[cntBullet].x > 58)	break;
						if (distance > 0) {
							gotoxy((bullet[cntBullet].x), bullet[cntBullet].y);
							printf("  ");
						}
						gotoxy((bullet[cntBullet].x) += 2, bullet[cntBullet].y);
						bulletShape(pnum, 2);

						if (gamemap[bullet[cntBullet].y][bullet[cntBullet].x] == 1) {
							gotoxy(bullet[cntBullet].x, bullet[cntBullet].y);
							printf("  ");

							hitEnemy += 1;
							score += 10 * stage;
							displayScore(score);
							displayhitEnemy(hitEnemy);
							displayCurrentEnemy(-1);

							gamemap[bullet[cntBullet].y][bullet[cntBullet].x - 1] = 0;
							gamemap[bullet[cntBullet].y][bullet[cntBullet].x] = 0;
							gamemap[bullet[cntBullet].y][bullet[cntBullet].x + 1] = 0;
						}
						else if (gamemap[bullet[cntBullet].y][bullet[cntBullet].x] == 3) {
							gotoxy(bullet[cntBullet].x, bullet[cntBullet].y);
							printf("  ");

							hitEnemy += 1;
							score += 10 * stage;
							displayScore(score);
							displayhitEnemy(hitEnemy);
							displayCurrentEnemy(-1);

							gamemap[bullet[cntBullet].y][bullet[cntBullet].x - 1] = 0;
							gamemap[bullet[cntBullet].y][bullet[cntBullet].x] = 0;
							gamemap[bullet[cntBullet].y][bullet[cntBullet].x + 1] = 0;
						}
						else if (gamemap[bullet[cntBullet].y][bullet[cntBullet].x] == 2) {
							gotoxy(bullet[cntBullet].x, bullet[cntBullet].y);
							printf("  ");
							gamemap[bullet[cntBullet].y][bullet[cntBullet].x - 1] = 0;
							gamemap[bullet[cntBullet].y][bullet[cntBullet].x] = 0;
							gamemap[bullet[cntBullet].y][bullet[cntBullet].x + 1] = 0;
						}
					}
				}
				gotoxy((bullet[cntBullet].x), bullet[cntBullet].y);
				printf("  ");
				bullet[cntBullet].exist = true;
				cntBullet += 1;
			}
		}
		//A(���� �߻�)
		if (GetAsyncKeyState(65)){
			if (cntBullet >= chter[pnum].max_bullet){
				gotoxy(106, 9);
				printf("R");
				Sleep(chter[pnum].reloadspeed);
				cntBullet = 0;
				for (int i = 0; i < chter[pnum].max_bullet; i++)	bullet[i].exist = false;
				displayBulletNum(chter[pnum].max_bullet - cntBullet);

			}
			else {
				displayBulletNum(chter[pnum].max_bullet - cntBullet - 1);
				bullet[cntBullet].x = myPlayer.x;
				bullet[cntBullet].y = myPlayer.y;
				for (int distance = 0; distance < chter[pnum].maxdistance_bullet; distance++) {
					if (bullet[cntBullet].exist == false) {

						Sleep(chter[pnum].bulletspeed);

						if (bullet[cntBullet].x < 8)	break;
						if (distance > 0) {
							gotoxy((bullet[cntBullet].x), bullet[cntBullet].y);
							printf("  ");
						}

						gotoxy((bullet[cntBullet].x) -= 2, bullet[cntBullet].y);
						bulletShape(pnum, 4);

						if (gamemap[bullet[cntBullet].y][bullet[cntBullet].x] == 2) {
							gotoxy(bullet[cntBullet].x - 2, bullet[cntBullet].y);
							printf("  ");

							score += 10 * stage;
							hitEnemy += 1;
							displayScore(score);
							displayhitEnemy(hitEnemy);
							displayCurrentEnemy(-1);

							gamemap[bullet[cntBullet].y][bullet[cntBullet].x] = 0;
							gamemap[bullet[cntBullet].y][bullet[cntBullet].x - 1] = 0;
							gamemap[bullet[cntBullet].y][bullet[cntBullet].x - 2] = 0;

						}
						else if (gamemap[bullet[cntBullet].y][bullet[cntBullet].x] == 1) {
							gotoxy(bullet[cntBullet].x - 1, bullet[cntBullet].y);
							printf("  ");

							hitEnemy += 1;
							score += 10 * stage;
							displayScore(score);
							displayhitEnemy(hitEnemy);
							displayCurrentEnemy(-1);

							gamemap[bullet[cntBullet].y][bullet[cntBullet].x] = 0;
							gamemap[bullet[cntBullet].y][bullet[cntBullet].x + 1] = 0;
							gamemap[bullet[cntBullet].y][bullet[cntBullet].x - 1] = 0;
						}
					}
				}
				gotoxy((bullet[cntBullet].x), bullet[cntBullet].y);
				printf("  ");
				bullet[cntBullet].exist = true;
				cntBullet += 1;
			}
		}
		//W(���� �߻�)
		if (GetAsyncKeyState(87)){
			if (cntBullet >= chter[pnum].max_bullet){
				gotoxy(106, 9);
				printf("R");
				Sleep(chter[pnum].reloadspeed);
				cntBullet = 0;
				for (int i = 0; i < chter[pnum].max_bullet; i++)	bullet[i].exist = false;
				displayBulletNum(chter[pnum].max_bullet - cntBullet);

			}
			else {
				displayBulletNum(chter[pnum].max_bullet - cntBullet - 1);
				bullet[cntBullet].x = myPlayer.x;
				bullet[cntBullet].y = myPlayer.y;
				for (int distance = 0; distance < chter[pnum].maxdistance_bullet; distance++) {
					if (bullet[cntBullet].exist == false) {

						Sleep(chter[pnum].bulletspeed);

						if (bullet[cntBullet].y < 4)	break;
						if (distance > 0) {
							gotoxy((bullet[cntBullet].x), bullet[cntBullet].y);
							printf("  ");
						}
						gotoxy((bullet[cntBullet].x), bullet[cntBullet].y -= 1);
						bulletShape(pnum, 1);

						if (gamemap[bullet[cntBullet].y][bullet[cntBullet].x] == 3) {
							gotoxy(bullet[cntBullet].x, bullet[cntBullet].y);
							printf("  ");

							hitEnemy += 1;
							score += 10 * stage;
							displayScore(score);
							displayhitEnemy(hitEnemy);
							displayCurrentEnemy(-1);

							gamemap[bullet[cntBullet].y][bullet[cntBullet].x + 1] = 0;
							gamemap[bullet[cntBullet].y][bullet[cntBullet].x] = 0;
							gamemap[bullet[cntBullet].y][bullet[cntBullet].x + 2] = 0;

						}

						else if (gamemap[bullet[cntBullet].y][bullet[cntBullet].x] == 1) {
							gotoxy(bullet[cntBullet].x, bullet[cntBullet].y);
							printf("  ");

							hitEnemy += 1;
							score += 10 * stage;
							displayScore(score);
							displayhitEnemy(hitEnemy);
							displayCurrentEnemy(-1);

							gamemap[bullet[cntBullet].y][bullet[cntBullet].x - 2] = 0;
							gamemap[bullet[cntBullet].y][bullet[cntBullet].x - 1] = 0;
							gamemap[bullet[cntBullet].y][bullet[cntBullet].x] = 0;
						}

						else if (gamemap[bullet[cntBullet].y][bullet[cntBullet].x] == 2) {
							gotoxy(bullet[cntBullet].x - 2, bullet[cntBullet].y);
							printf("  ");

							hitEnemy += 1;
							score += 10 * stage;
							displayScore(score);
							displayhitEnemy(hitEnemy);
							displayCurrentEnemy(-1);

							gamemap[bullet[cntBullet].y][bullet[cntBullet].x - 2] = 0;
							gamemap[bullet[cntBullet].y][bullet[cntBullet].x] = 0;
							gamemap[bullet[cntBullet].y][bullet[cntBullet].x - 1] = 0;
						}

					}
				}
				gotoxy((bullet[cntBullet].x), bullet[cntBullet].y);
				printf("  ");
				bullet[cntBullet].exist = true;
				cntBullet += 1;
			}
		}
		//S(�Ʒ��� �߻�)
		if (GetAsyncKeyState(83)){
			if (cntBullet >= chter[pnum].max_bullet){
				gotoxy(106, 9);
				printf("R");
				Sleep(chter[pnum].reloadspeed);
				cntBullet = 0;
				for (int i = 0; i < chter[pnum].max_bullet; i++)	bullet[i].exist = false;
				displayBulletNum(chter[pnum].max_bullet - cntBullet);
			}
			else {
				displayBulletNum(chter[pnum].max_bullet - cntBullet - 1);
				bullet[cntBullet].x = myPlayer.x;
				bullet[cntBullet].y = myPlayer.y;
				for (int distance = 0; distance < chter[pnum].maxdistance_bullet; distance++) {
					if (bullet[cntBullet].exist == false) {

						Sleep(chter[pnum].bulletspeed);

						if (bullet[cntBullet].y > 27)	break;
						if (distance > 0) {
							gotoxy((bullet[cntBullet].x), bullet[cntBullet].y);
							printf(" ");
						}
						gotoxy((bullet[cntBullet].x), bullet[cntBullet].y += 1);
						bulletShape(pnum, 3);

						if (gamemap[bullet[cntBullet].y][bullet[cntBullet].x] == 3) {
							gotoxy(bullet[cntBullet].x, bullet[cntBullet].y);
							printf("  ");

							hitEnemy += 1;
							score += 10 * stage;
							displayScore(score);
							displayhitEnemy(hitEnemy);
							displayCurrentEnemy(-1);

							gamemap[bullet[cntBullet].y][bullet[cntBullet].x - 1] = 0;
							gamemap[bullet[cntBullet].y][bullet[cntBullet].x] = 0;
							gamemap[bullet[cntBullet].y][bullet[cntBullet].x + 1] = 0;
							gamemap[bullet[cntBullet].y][bullet[cntBullet].x + 2] = 0;
						}

						else if (gamemap[bullet[cntBullet].y][bullet[cntBullet].x] == 1) {
							gotoxy(bullet[cntBullet].x, bullet[cntBullet].y);
							printf("  ");

							hitEnemy += 1;
							score += 10 * stage;
							displayScore(score);
							displayhitEnemy(hitEnemy);
							displayCurrentEnemy(-1);

							gamemap[bullet[cntBullet].y][bullet[cntBullet].x - 1] = 0;
							gamemap[bullet[cntBullet].y][bullet[cntBullet].x] = 0;
							gamemap[bullet[cntBullet].y][bullet[cntBullet].x + 1] = 0;
						}

						else if (gamemap[bullet[cntBullet].y][bullet[cntBullet].x] == 2) {
							gotoxy(bullet[cntBullet].x - 2, bullet[cntBullet].y);
							printf("  ");

							hitEnemy += 1;
							score += 10 * stage;
							displayScore(score);
							displayhitEnemy(hitEnemy);
							displayCurrentEnemy(-1);

							gamemap[bullet[cntBullet].y][bullet[cntBullet].x] = 0;
							gamemap[bullet[cntBullet].y][bullet[cntBullet].x - 1] = 0;
							gamemap[bullet[cntBullet].y][bullet[cntBullet].x - 2] = 0;
						}
					}
				}
				gotoxy((bullet[cntBullet].x), bullet[cntBullet].y);
				printf("  ");
				bullet[cntBullet].exist = true;
				cntBullet += 1;
			}
		}
		//n�� �̻� ���� �� ���� ��������
		if (hitEnemy >= sstage[stage].enemynum_clearstage)	isstart = 2;
	}
}

//�÷��̾��� ��ġ�� �ʱ�ȭ �ϰ� �Ѿ��� exist���� false�� �ʱ�ȭ�ϴ� �Լ�(�Ű������� �ڽ��� ĳ���� number(1~6)�� ����)
void reset(short myplayer) {
	//�÷��̾��� ��ġ �ʱ�ȭ
	myPlayer.x = (WIDTH/2)/2;	
	myPlayer.y = HEIGHT/2;

	//�ʱ�ȭ�� ��ġ�� �̵�
	gotoxy(myPlayer.x, myPlayer.y);

	//myplayer(�ڽ��� �� ĳ����) ���� �ٸ� ĳ���� ���
	if (myplayer == 1)	printf("��");
	else if (myplayer == 2)	printf("��");
	else if (myplayer == 3)	printf("��");
	else if (myplayer == 4)	printf("��");
	else if (myplayer == 5)	printf("��");
	else if (myplayer == 6)	printf("��");

	//��� �Ѿ� �ʱ�ȭ(exist(������)�� false�� ����)
	for (int i = 0; i < chter[myCharacter].max_bullet; i++)	bullet[i].exist = false;
}

//�÷��̾��� ������, ���������� ������ �ʱ�ȭ�ϴ� �Լ�
void setInformation(void){
	chter[1].name = " �ܱ��հ�";
	chter[1].armorname = "�ܰ�";
	chter[1].bulletspeed = 60;	//�ּ� 30
	chter[1].maxdistance_bullet = 2;
	chter[1].max_bullet =1;
	chter[1].playerspeed = 40;	//�ּ� 50
	chter[1].reloadspeed = 100;

	chter[2].name = "�̼����屺";
	chter[2].armorname = "����";
	chter[2].bulletspeed = 90;
	chter[2].maxdistance_bullet = 5;
	chter[2].max_bullet = 7;
	chter[2].playerspeed = 50;	
	chter[2].reloadspeed = 1500;

	chter[3].name = " �������";
	chter[3].armorname = "�ѱ�";
	chter[3].bulletspeed = 45;
	chter[3].maxdistance_bullet =6;
	chter[3].max_bullet = 7;
	chter[3].playerspeed = 35;
	chter[3].reloadspeed = 600;

	chter[4].name = "  ���߱�";
	chter[4].armorname = "����";
	chter[4].bulletspeed = 55;	
	chter[4].maxdistance_bullet = 10;
	chter[4].max_bullet = 11;
	chter[4].playerspeed = 35;
	chter[4].reloadspeed = 500;

	chter[5].name = "  ���ε�";
	chter[5].armorname = "������";
	chter[5].bulletspeed = 30;	
	chter[5].maxdistance_bullet = 15;
	chter[5].max_bullet = 2;
	chter[5].playerspeed = 45;
	chter[5].reloadspeed = 2000;

	chter[6].name = "  �����";
	chter[6].armorname = "�����";
	chter[6].bulletspeed = 39;	
	chter[6].maxdistance_bullet = 8;
	chter[6].max_bullet = 30;
	chter[6].playerspeed = 60;
	chter[6].reloadspeed = 2300;

	sstage[1].enemynum = 24;
	sstage[1].enemynum_clearstage = 8;
	sstage[1].enemynum_endstage = 17;
	sstage[1].displayenemyspeed = 1500;

	sstage[2].enemynum = 28;
	sstage[2].enemynum_clearstage = 9;
	sstage[2].enemynum_endstage = 17;
	sstage[2].displayenemyspeed = 1400;

	sstage[3].enemynum = 32;
	sstage[3].enemynum_clearstage = 11;
	sstage[3].enemynum_endstage = 16;
	sstage[3].displayenemyspeed = 1200;

	sstage[4].enemynum = 36;
	sstage[4].enemynum_clearstage = 13;
	sstage[4].enemynum_endstage = 16;
	sstage[4].displayenemyspeed = 1100;

	sstage[5].enemynum = 40;
	sstage[5].enemynum_clearstage = 15;
	sstage[5].enemynum_endstage = 15;
	sstage[5].displayenemyspeed = 1000;

	sstage[6].enemynum = 44;
	sstage[6].enemynum_clearstage = 16;
	sstage[6].enemynum_endstage = 15;
	sstage[6].displayenemyspeed = 900;

	sstage[7].enemynum = 48;
	sstage[7].enemynum_clearstage = 17;
	sstage[7].enemynum_endstage = 14;
	sstage[7].displayenemyspeed = 800;

	sstage[8].enemynum = 50;
	sstage[8].enemynum_clearstage = 18;
	sstage[8].enemynum_endstage = 14;
	sstage[8].displayenemyspeed = 700;

	sstage[9].enemynum = 50;
	sstage[9].enemynum_clearstage = 19;
	sstage[9].enemynum_endstage = 13;
	sstage[9].displayenemyspeed = 600;

	sstage[10].enemynum = 50;
	sstage[10].enemynum_clearstage = 20;
	sstage[10].enemynum_endstage = 13;
	sstage[10].displayenemyspeed = 550;

	sstage[11].enemynum = 50;
	sstage[11].enemynum_clearstage = 21;
	sstage[11].enemynum_endstage = 12;
	sstage[11].displayenemyspeed = 500;

	sstage[12].enemynum = 50;
	sstage[12].enemynum_clearstage = 22;
	sstage[12].enemynum_endstage = 12;
	sstage[12].displayenemyspeed = 450;

	sstage[13].enemynum = 50;
	sstage[13].enemynum_clearstage = 23;
	sstage[13].enemynum_endstage = 11;
	sstage[13].displayenemyspeed = 400;

	sstage[14].enemynum = 50;
	sstage[14].enemynum_clearstage = 24;
	sstage[14].enemynum_endstage = 11;
	sstage[14].displayenemyspeed = 350;

	sstage[15].enemynum = 50;
	sstage[15].enemynum_clearstage = 25;
	sstage[15].enemynum_endstage = 10;
	sstage[15].displayenemyspeed = 300;

	sstage[16].enemynum = 50;
	sstage[16].enemynum_clearstage = 26;
	sstage[16].enemynum_endstage = 10;
	sstage[16].displayenemyspeed = 250;

	sstage[17].enemynum = 50;
	sstage[17].enemynum_clearstage = 27;
	sstage[17].enemynum_endstage = 9;
	sstage[17].displayenemyspeed = 200;

	sstage[18].enemynum = 50;
	sstage[18].enemynum_clearstage = 28;
	sstage[18].enemynum_endstage = 9;
	sstage[18].displayenemyspeed = 200;

	sstage[19].enemynum = 50;
	sstage[19].enemynum_clearstage = 29;
	sstage[19].enemynum_endstage = 8;
	sstage[19].displayenemyspeed = 200;

	sstage[20].enemynum = 50;
	sstage[20].enemynum_clearstage = 30;
	sstage[20].enemynum_endstage = 7;
	sstage[20].displayenemyspeed = 200;

	sstage[21].enemynum = 50;
	sstage[21].enemynum_clearstage = 31;
	sstage[21].enemynum_endstage = 6;
	sstage[21].displayenemyspeed = 200;
 }	

 //ĳ������ �ɷ�ġ�� ��ȭ��Ű�� �Լ�
 void changeAbility(short num) {
	 switch (num) {
	 case 1:
		 ability1++;
		 displayChangeAbility(num, ability1);
		 break;
	 case 2:
		 ability1--;
		 displayChangeAbility(num, ability1);
		 break;
	 case 3:
		 ability2++;
		 displayChangeAbility(num, ability2);
		 break;
	 case 4:
		 ability2--;
		 displayChangeAbility(num, ability2);
		 break;
	 case 5:
		 ability3++;
		 displayChangeAbility(num, ability3);
		 break;
	 case 6:
		 ability3--;
		 displayChangeAbility(num, ability3);
		 break;
	 case 7:
		 ability4++;
		 displayChangeAbility(num, ability4);
		 break;
	 case 8:
		 ability4--;
		 displayChangeAbility(num, ability4);
		 break;
	 }
 }


 //ĳ������ �ɷ�ġ ��ȭ�� �׷��ִ� �Լ�
 void displayChangeAbility(short num, short s)
 {
	 if (num == 1) {
		 setColor(4);
		 gotoxy(90, 18);
		 switch (s){
		 case 1:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 2:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 3:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 4:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 5:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 6:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 7:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 8:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 default:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 }
		 setColor(0);
	 }
	 else if (num == 2) {
		 gotoxy(90, 18);
		 setColor(4);
		 switch (s){
		 case 1:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 2:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 3:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 4:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 5:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 6:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 7:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 8:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 default:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 }
		 setColor(0);
	 }
	 else if (num == 3)
	 {
		 gotoxy(90, 20);
		 setColor(4);
		 switch (s){
		 case 1:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 2:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 3:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 4:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 5:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 6:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 7:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 8:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 default:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 }
		 setColor(0);
	 }
	 else if (num == 4)
	 {
		 gotoxy(90, 20);
		 setColor(4);
		 switch (s){
		 case 1:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 2:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 3:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 4:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 5:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 6:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 7:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 8:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 default:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 }
		 setColor(0);
	 }
	 else if (num == 5) {
		 gotoxy(90, 22);
		 setColor(4);
		 switch (s) {
		 case 1:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 2:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 3:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 4:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 5:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 6:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 7:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 8:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 default:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 }
		 setColor(0);
	 }
	 else if (num == 6) {
		 gotoxy(90, 22);
		 setColor(4);
		 switch (s) {
		 case 1:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 2:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 3:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 4:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 5:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 6:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 7:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 8:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 default:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 }
		 setColor(0);
	 }
	 else if (num == 7) {
		 gotoxy(90, 24);
		 setColor(4);
		 switch (s) {
		 case 1:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 2:
			 printf("�� �� �� �� �� �� �� ");
			 break;
		 case 3:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 4:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 5:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 6:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 7:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 8:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 default:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 }
		 setColor(0);
	 }
	 else if (num == 8) {
		 gotoxy(90, 24);
		 setColor(4);
		 switch (s) {
		 case 1:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 2:
			 printf("�� �� �� �� �� �� �� ");
			 break;
		 case 3:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 4:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 5:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 6:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 7:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 case 8:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 default:
			 printf("�� �� �� �� �� �� ��");
			 break;
		 }
		 setColor(0);
	 }
 }

 //ĳ���Ϳ� ���� �ٸ� ����� �Ѿ��� �����ϴ� �Լ�(�Ű������� �ڽ��� ĳ���Ϳ� �Ѿ��� ������ ����)
void bulletShape(short myplayer, short dir) {
	 setColor(12);
	 switch (myplayer) {
	 case 1:
		 switch (dir) {
		 case 1:
			 printf("��");
			 break;
		 case 2:
			 printf("��");
			 break;
		 case 3:
			 printf("��");
			 break;
		 case 4:
			 printf("��");
			 break;
		 }
		 break;
	 case 2:
		 printf("��");
		 break;
	 case 3:
		 switch (dir) {
		 case 1:
			 printf("��");
			 break;
		 case 2:
			 printf("��");
			 break;
		 case 3:
			 printf("��");
			 break;
		 case 4:
			 printf("��");
			 break;
		 }
		 break;
	 case 4:
	 case 5:
	 case 6:
		 printf("��");
		 break;
	 }
	 setColor(0);
}


//��(���ĺ�)�� ����Ǿ��ִ� �Լ�
void alphabet(short a) {
	setColor(3);
	switch (a) {
	case 0:
		printf("��");
		break;
	case 1:
		printf("��");
		break;
	case 2:
		printf("��");
		break;
	case 3:
		printf("��");
		break;
	case 4:
		printf("��");
		break;
	case 5:
		printf("��");
		break;
	case 6:
		printf("��");
		break;
	case 7:
		printf("��");
		break;
	case 8:
		printf("��");
		break;
	case 9:
		printf("��");
		break;
	case 10:
		printf("��");
		break;
	case 11:
		printf("��");
		break;
	case 12:
		printf("��");
		break;
	case 13:
		printf("��");
		break;
	case 14:
		printf("��");
		break;
	case 15:
		printf("��");
		break;
	case 16:
		printf("��");
		break;
	case 17:
		printf("��");
		break;
	case 18:
		printf("��");
		break;
	case 19:
		printf("��");
		break;
	case 20:
		printf("��");
		break;
	case 21:
		printf("��");
		break;
	case 22:
		printf("��");
		break;
	case 23:
		printf("��");
		break;
	case 24:
		printf("��");
		break;
	case 25:
		printf("��");
		break;
	}
	setColor(0);
}

//���� �����ϴ� �Լ�(�Ű������� stage�� ����)
void createEnemy(short stage) {
	srand(time(NULL));
	short rand_x = 0;
	short rand_y = 0;
	short num = 0;
	for (int i = 1; i <= sstage[stage].enemynum; i++) {
		GetAsyncKeyState(13);
		if (isstart == 2||isstart==0) return 0;
		rand_x = rand() % 26 + 4;
		rand_y = rand() % 24 + 4;
		if (rand_x * 2 != myPlayer.x && rand_y != myPlayer.y) {
			if (rand_x * 2 - 2 != 0 && rand_x * 2 + 2 != 0) {
				gotoxy(rand_x * 2, rand_y);
				alphabet(i % 26 - 1);
				setEnemyPosition_Gamemap(rand_y, rand_x * 2);
				displayCurrentEnemy(1);
				num += 1;
			}
			//ȭ�鿡 ���� n�� �̻��� �� ���� ����
			if (num - hitEnemy > sstage[stage].enemynum_endstage){
				isstart = 0;
				Sleep(500);
				for (int y = 3; y < 29; y++) {
					for (int x = 7; x < 61; x += 2) {
						gotoxy(x, y);
						printf("  ");
					}
				}
				PlaySound(TEXT("endMusic.wav"), NULL, SND_FILENAME | SND_ASYNC);
				Sleep(500);
				gotoxy(18, 12);
				printf("GAME OVER  GAME OVER  GAME OVER");
				gotoxy(18, 13);
				printf("GAME OVER  GAME OVER  GAME OVER");
				gotoxy(18, 14);
				printf("GAME OVER  GAME OVER  GAME OVER");
				gotoxy(18, 15);
				printf("GAME OVER  GAME OVER  GAME OVER");
				gotoxy(18, 16);
				printf("GAME OVER  GAME OVER  GAME OVER");
				gotoxy(18, 17);
				printf("GAME OVER  GAME OVER  GAME OVER");
				gotoxy(18, 18);
				printf("GAME OVER  GAME OVER  GAME OVER");
				gotoxy(18, 19);
				printf("GAME OVER  GAME OVER  GAME OVER");
				Sleep(2000);
				clearBattleGround();
				saveHighscore(myCharacter);
				break;
			}
			Sleep(sstage[stage].displayenemyspeed);
		}
	}
}

//������ �������� �� ����Ǵ� �Լ�
int gameGameStart(short playernum, short originalmaxbullet, short originalmaxbulletdistance, short originalbulletspeed, short originalplayerspeed) {
	int select = 1;
	//�����Ǳ� �� ���� originalmoney�� ����
	int originalmoney = money;

	drawStore_Dynamic(playernum);

	//Ŀ���� �߸��� �̵����� ���� storestatic�� �������� �� ����ؼ� ���������� ���� ������ �ٽ� �׷���
	gotoxy(99, 13);
	printf("/");

	while (1) {
		//enter�Է½�(���� �ð��� ��ġ�� ������ �����Ϸ� �� ��)
		if (GetAsyncKeyState(13)) {
			//����� ���� ������
			clearBattleGround();
			Sleep(500);
			//�������� ���� ����, �̵�Ű�� �߻�Ű�� ������ �׷��ִ� �Լ�
			loadingStage();
			//����� ���� ������
			clearBattleGround();
			Sleep(100);
			//������ ���۵Ǿ��ٴ� ��ȣ�� ����
			isstart = 1;

			//��� Ű�� ����
			GetAsyncKeyState(65);
			GetAsyncKeyState(68);
			GetAsyncKeyState(83);
			GetAsyncKeyState(87);
			break;
		}

		//���� �̵�(W)
		if (GetAsyncKeyState(87) & 1 || GetAsyncKeyState(VK_UP) & 1) {
			select -= 1;
			if (select <= 1)	select = 1;
		}
		//�Ʒ��� �̵�(S)
		if (GetAsyncKeyState(83) & 1 || GetAsyncKeyState(VK_DOWN) & 1) {
			select += 1;
			if (select >= 4) select = 4;
		}

		//��� Ű�� ����
		GetAsyncKeyState(8);
		GetAsyncKeyState(65);
		GetAsyncKeyState(68);
		GetAsyncKeyState(83);
		GetAsyncKeyState(87);
		//BULLET�׸� ����
		if (select == 1) {
			//�Ѿ� ����
			if (GetAsyncKeyState(VK_RIGHT) & 1 || GetAsyncKeyState(68) & 1) {
				//���Ÿ� �õ����� �� ���� 0���� ���� && �ɷ�ġ ���� Ƚ���� 7������ ���� ��
				if (money - 400 >= 0 && a1 < 7) {
					money -= 400;
					chter[playernum].max_bullet += 6;
					displayMoney(money);
					displayBulletNum(chter[playernum].max_bullet);
					changeAbility(1);
					a1 += 1;
				}

			}
			//�Ѿ� �Ǹ�
			if (GetAsyncKeyState(VK_LEFT) & 1 || GetAsyncKeyState(65) & 1) {
				// ������ �Ѿ˰����� ���� �ִ��Ѿ˰������� Ŭ ����
				if (chter[playernum].max_bullet - 6 >= originalmaxbullet) {
					money += 400;
					chter[playernum].max_bullet -= 6;
					displayMoney(money);
					displayBulletNum(chter[playernum].max_bullet);
					changeAbility(2);
					a1 -= 1;
				}
			}
		}
		//DISTANCE ���� ��
		if (select == 2) {
			//�Ѿ˰Ÿ� �ø���
			if (GetAsyncKeyState(VK_RIGHT) & 1 || GetAsyncKeyState(68) & 1) {
				if (money - 500 >= 0 && a2 < 7) {
					money -= 500;
					chter[playernum].maxdistance_bullet += 1;
					displayMoney(money);
					changeAbility(3);
					a2 += 1;
				}
			}
			//�Ѿ˰Ÿ� ���̱�
			if (GetAsyncKeyState(VK_LEFT) & 1 || GetAsyncKeyState(65) & 1) {
				if (chter[playernum].maxdistance_bullet - 1 >= originalmaxbulletdistance) {
					money += 500;
					chter[playernum].maxdistance_bullet -= 1;
					displayMoney(money);
					changeAbility(4);
					a2 -= 1;
				}
			}
		}
		//BULLETSPEED ���� ��
		if (select == 3) {
			//�ӵ� ����
			if (GetAsyncKeyState(VK_RIGHT) & 1 || GetAsyncKeyState(68) & 1) {
				if (money - 400 >= 0 && a3 < 7) {
					money -= 400;
					chter[playernum].bulletspeed -= 3;
					displayMoney(money);
					changeAbility(5);
					a3 += 1;
				}
			}
			//�ӵ� ����
			if (GetAsyncKeyState(VK_LEFT) & 1 || GetAsyncKeyState(65) & 1) {
				if (chter[playernum].bulletspeed + 3 <= originalbulletspeed) {
					money += 400;
					chter[playernum].bulletspeed += 3;
					displayMoney(money);
					changeAbility(6);
					a3 -= 1;
				}
			}
		}
		//PLAYERSPEED ���� ��
		if (select == 4) {
			//�ӵ� ����
			if (GetAsyncKeyState(VK_RIGHT) & 1 || GetAsyncKeyState(68) & 1) {
				if (money - 500 >= 0 && a4 < 7) {
					money -= 500;
					chter[playernum].playerspeed -= 5;
					displayMoney(money);
					changeAbility(7);
					a4 += 1;
				}
			}
			//�ӵ� ����
			if (GetAsyncKeyState(VK_LEFT) & 1 || GetAsyncKeyState(65) & 1) {
				if (chter[playernum].playerspeed + 5 <= originalplayerspeed) {
					money += 500;
					chter[playernum].playerspeed += 5;
					displayMoney(money);
					changeAbility(8);
					a4 -= 1;
				}
			}
		}
		//select�� ���� ���� ȭ��ǥ �׸���
		switch (select) {
		case 1:
			gotoxy(69, 20);
			printf("  ");
			gotoxy(69, 22);
			printf("  ");
			gotoxy(69, 24);
			printf("  ");
			gotoxy(69, 18);
			printf("��");
			break;
		case 2:
			gotoxy(69, 18);
			printf("  ");
			gotoxy(69, 22);
			printf("  ");
			gotoxy(69, 24);
			printf("  ");
			gotoxy(69, 20);
			printf("��");
			break;
		case 3:
			gotoxy(69, 18);
			printf("  ");
			gotoxy(69, 20);
			printf("  ");
			gotoxy(69, 24);
			printf("  ");
			gotoxy(69, 22);
			printf("��");
			break;
		case 4:
			gotoxy(69, 18);
			printf("  ");
			gotoxy(69, 20);
			printf("  ");
			gotoxy(69, 22);
			printf("  ");
			gotoxy(69, 24);
			printf("��");
			break;
		}
	}
}