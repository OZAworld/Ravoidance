#include <iostream>
#include <stdio.h>
#include <time.h>
#include "vtx.h"
#include "Ball.h"
#include "Bar.h"
using namespace vtx;

bool GameStart;			//	ゲームが始まったかどうか
bool GameSet;			//	ゲームが終わったかどうか

Bar::Bar()
{
	mesh = new Mesh[3];
	mesh[0].Load(_T("Mesh/HpBar.x"));
	mesh[1].Load(_T("Mesh/timeBar.x"));
	mesh[2].Load(_T("Mesh/barFrame.x"));
	texture = new Texture[3];
	texture[0].Load(_T("Texture/Red.png"));
	texture[1].Load(_T("Texture/Blue.png"));
	texture[2].Load(_T("Texture/Green.png"));

	sec = new Mesh[11];
	sec[0].Load(_T("Mesh/10sec.x"));
	sec[1].Load(_T("Mesh/20sec.x"));
	sec[2].Load(_T("Mesh/30sec.x"));
	sec[3].Load(_T("Mesh/GameSet.x"));
	sec[4].Load(_T("Mesh/1sec.x"));
	sec[5].Load(_T("Mesh/2sec.x"));
	sec[6].Load(_T("Mesh/3sec.x"));
	sec[7].Load(_T("Mesh/4sec.x"));
	sec[8].Load(_T("Mesh/5sec.x"));
	sec[9].Load(_T("Mesh/Ready.x"));
	sec[10].Load(_T("Mesh/Go.x"));
	secTex = new Texture[5];
	secTex[0].Load(_T("Texture/Green.png"));
	secTex[1].Load(_T("Texture/Yellow.png"));
	secTex[2].Load(_T("Texture/Red.png"));
	secTex[3].Load(_T("Texture/Blue.png"));
	secTex[4].Load(_T("Texture/Shadow.png"));

	pos_1 = D3DXVECTOR3(-7.5, -3, -9);
	scale_1 = D3DXVECTOR3(0.8, 8, 1);

	pos_2 = D3DXVECTOR3(7.5, -3, -9);
	scale_2 = D3DXVECTOR3(0.8, 8, 1);

	pos_3 = D3DXVECTOR3(0, 6.5, -11);
	scale_3 = D3DXVECTOR3(8, 0.5, 0.5);

	secPos = D3DXVECTOR3(0, 6.3, -12);
	secScale = D3DXVECTOR3(0.8, 0.8, 0.8);
	secRot = D3DXVECTOR3(D3DXToRadian(0), D3DXToRadian(180), 0);

	GameStart = false;
	GameSet = false;
	startCount = 0;
}

Bar::~Bar()
{
	delete[] mesh;
	delete[] texture;
	delete[] sec;
	delete[] secTex;
}

void Bar::Draw()
{
	extern int playerCount;
	extern int playerCount2;

	float totalPer;
	float playerPer1;
	float playerPer2;

	totalPer = playerCount + playerCount2;
	playerPer1 = (playerCount / totalPer) * 100;
	playerPer2 = (playerCount2 / totalPer) * 100;
	scale_1.y = playerPer1 * 0.08;
	scale_2.y = playerPer2 * 0.08;

	mesh[0].Draw(&pos_1, &D3DXVECTOR3(0, D3DXToRadian(-15), 0), &scale_1, texture[0].Get());
	mesh[0].Draw(&pos_2, &D3DXVECTOR3(0, D3DXToRadian(15), 0), &scale_2, texture[1].Get());
	startCount++;
	if (GameStart == false && startCount < 100)
	{
		sec[9].Draw(&D3DXVECTOR3(0, 6.2, -19.6), &D3DXVECTOR3(D3DXToRadian(-35), D3DXToRadian(180), 0), &D3DXVECTOR3(0.2, 0.2, 0.2), secTex[3].Get());
	}

	if (startCount > 100 && startCount < 130)
	{
		sec[10].Draw(&D3DXVECTOR3(0, 6.2, -19.6), &D3DXVECTOR3(D3DXToRadian(-35), D3DXToRadian(180), 0), &D3DXVECTOR3(0.2, 0.2, 0.2), secTex[3].Get());
	}
	if (startCount > 130)
	{
		startCount = 130;
		GameStart = true;
	}

	if (GameStart == true)
	{
		timer += 0.00000375f;
		scale_3.x -= timer;
		secRot.y -= 0.09f;
	}
	if (scale_3.x > 0)
	{
		mesh[1].Draw(&pos_3, &D3DXVECTOR3(D3DXToRadian(-40), 0, 0), &scale_3, texture[2].Get());
	}
	mesh[2].Draw(&D3DXVECTOR3(0, 6.5, -10), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(440, 39, 2), secTex[4].Get());
	mesh[2].Draw(&D3DXVECTOR3(0, 6.5, -10), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(450, 45, 1), nullptr);

	//	30
	if (scale_3.x > 7.2)
		sec[2].Draw(&secPos, &secRot, &secScale, secTex[0].Get());

	//	20
	if (scale_3.x > 4.8 && scale_3.x < 7.2)
		sec[1].Draw(&secPos, &secRot, &secScale, secTex[1].Get());

	//	10
	if (scale_3.x > 2.4 && scale_3.x < 4.8)
		sec[0].Draw(&secPos, &secRot, &D3DXVECTOR3(secScale.x*1.25, secScale.y*1.25, secScale.z*1.25), secTex[2].Get());

	//	5
	if (scale_3.x > 1.9 && scale_3.x < 2.4)
	{
		secScale.x += 0.002f;
		secScale.y += 0.002f;
		secScale.z += 0.002f;
		sec[8].Draw(&secPos, &D3DXVECTOR3(0, D3DXToRadian(180), 0), &D3DXVECTOR3(secScale.x*1.25, secScale.y*1.25, secScale.z*1.25), secTex[2].Get());
	}
	//	4
	if (scale_3.x > 1.4 && scale_3.x < 1.9)
	{
		secScale.x += 0.002f;
		secScale.y += 0.002f;
		secScale.z += 0.002f;
		sec[7].Draw(&secPos, &D3DXVECTOR3(0, D3DXToRadian(180), 0), &D3DXVECTOR3(secScale.x*1.25, secScale.y*1.25, secScale.z*1.25), secTex[2].Get());
	}
	//	3
	if (scale_3.x > 0.9 && scale_3.x < 1.4)
	{
		secScale.x += 0.002f;
		secScale.y += 0.002f;
		secScale.z += 0.002f;
		sec[6].Draw(&secPos, &D3DXVECTOR3(0, D3DXToRadian(180), 0), &D3DXVECTOR3(secScale.x*1.25, secScale.y*1.25, secScale.z*1.25), secTex[2].Get());
	}
	//	2
	if (scale_3.x > 0.4 && scale_3.x < 0.9)
	{
		secScale.x += 0.002f;
		secScale.y += 0.002f;
		secScale.z += 0.002f;
		sec[5].Draw(&secPos, &D3DXVECTOR3(0, D3DXToRadian(180), 0), &D3DXVECTOR3(secScale.x*1.25, secScale.y*1.25, secScale.z*1.25), secTex[2].Get());
	}
	//	1
	if (scale_3.x > 0 && scale_3.x < 0.4)
	{
		secScale.x += 0.002f;
		secScale.y += 0.002f;
		secScale.z += 0.002f;
		sec[4].Draw(&secPos, &D3DXVECTOR3(0, D3DXToRadian(180), 0), &D3DXVECTOR3(secScale.x*1.25, secScale.y*1.25, secScale.z*1.25), secTex[2].Get());
	}

	//	GameSet
	if (scale_3.x <= 0)
		sec[3].Draw(&D3DXVECTOR3(0, 6.2, -19.6), &D3DXVECTOR3(D3DXToRadian(-35), D3DXToRadian(180), 0), &D3DXVECTOR3(0.2, 0.2, 0.2), secTex[3].Get());


	//	終了
	if (scale_3.x < 0)
	{
		scale_3.x = 0;
		GameSet = true;
	}

}

