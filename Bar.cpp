#include <iostream>
#include "vtx.h"
#include "Ball.h"
#include "Bar.h"
using namespace vtx;

Bar::Bar()
{
	mesh = new Mesh(_T("Mesh/HpBar.x"));
	texture = new Texture[2];
	texture[0].Load(_T("Texture/Red.png"));
	texture[1].Load(_T("Texture/Blue.png"));

	pos_1 = D3DXVECTOR3(-7.5, -3, -9);
	scale_1 = D3DXVECTOR3(0.8, 8, 1);

	pos_2 = D3DXVECTOR3(7.5, -3, -9);
	scale_2 = D3DXVECTOR3(0.8, 8, 1);
}

Bar::~Bar()
{
	delete mesh;
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

	mesh->Draw(&pos_1, &D3DXVECTOR3(0, D3DXToRadian(-15), 0), &scale_1, texture[0].Get());
	mesh->Draw(&pos_2, &D3DXVECTOR3(0, D3DXToRadian(15), 0), &scale_2, texture[1].Get());
}