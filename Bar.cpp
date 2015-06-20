#include <iostream>
#include <stdio.h>
#include <time.h>
#include "vtx.h"
#include "Ball.h"
#include "Bar.h"
using namespace vtx;


Bar::Bar()
{
	mesh = new Mesh[2];
	mesh[0].Load(_T("Mesh/HpBar.x"));
	mesh[1].Load(_T("Mesh/timeBar.x"));
	texture = new Texture[3];
	texture[0].Load(_T("Texture/Red.png"));
	texture[1].Load(_T("Texture/Blue.png"));
	texture[2].Load(_T("Texture/Green.png"));

	pos_1 = D3DXVECTOR3(-7.5, -3, -9);
	scale_1 = D3DXVECTOR3(0.8, 8, 1);

	pos_2 = D3DXVECTOR3(7.5, -3, -9);
	scale_2 = D3DXVECTOR3(0.8, 8, 1);

	pos_3 = D3DXVECTOR3(0, 5.7, -11);
	scale_3 = D3DXVECTOR3(8, 0.5, 0.5);
}

Bar::~Bar()
{
	delete[] mesh;
	delete[] texture;
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

	timer += 0.00000375f;
	scale_3.x -= timer;
	std::cout << "sec." << scale_3.x << std::endl;
	mesh[1].Draw(&pos_3, &D3DXVECTOR3(D3DXToRadian(-40), 0, 0), &scale_3, texture[2].Get());

	if (scale_3.x < 0)
	{
		scale_3.x = 0;
	}
}

