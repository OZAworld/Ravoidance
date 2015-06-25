#include <iostream>
#include "vtx.h"
#include "Player.h"
#include "2Player.h"
#include "Ball.h"
using namespace vtx;

int playerCount = 0;
int playerCount2 = 0;
bool playerFlag = false;
bool playerFlag2 = false;

Ball::Ball()
{
	pos = D3DXVECTOR3(0, 0, 0);
	vec = D3DXVECTOR3(0, 0, 0);
}

Ball::Ball(D3DXVECTOR3 pos, D3DXVECTOR3 vec)
{
	Ball::pos = pos;
	Ball::vec = vec;
}

Ball::~Ball()
{

}

void Ball::Update(Player &player, std::vector<Ball> ball, int index, Player2 &player2)
{
	vec *= 0.995f;
	vec.y -= 0.0003f;

	pos += vec;

	if (pos.x < -7.35f)
	{
		vec.x = -vec.x;
		pos.x = -7.35f;
	}
	if (pos.x > 7.35f)
	{
		vec.x = -vec.x;
		pos.x = 7.35f;
	}
	if (pos.y < -4.85f)
	{
		vec.y = -vec.y;
		pos.y = -4.85f;
	}
	if (pos.y > 4.85f)
	{
		vec.y = -vec.y;
		pos.y = 4.85f;
	}
	if (pos.z < -7.35f)
	{
		vec.z = -vec.z;
		pos.z = -7.35f;
	}
	if (pos.z > 7.35f)
	{
		vec.z = -vec.z;
		pos.z = 7.35f;
	}

	if (pow(pos.x - player.pos.x, 2) + pow(pos.z - player.pos.z, 2) <= pow(0.5 + 0.15, 2)
		&& pow(pos.x - player.pos.x, 2) + pow(pos.y - player.pos.y, 2) <= pow(0.5 + 0.15, 2))
	{
		float hitAngle = atan2(pos.z - player.pos.z, pos.x - player.pos.x);
		vec = D3DXVECTOR3(cos(hitAngle), 0, sin(hitAngle)) * 0.05f;
	}

	for (int i = 0; i < ball.size(); i++)
	{
		if (index == i)
			continue;

		float x1, x2, y1, y2, z1, z2;

		if ((x1 = floor(ball[i].pos.x * 3)) == (x2 = floor(pos.x * 3))
			&& (y1 = floor(ball[i].pos.y * 3)) == (y2 = floor(pos.y * 3))
			&& (z1 = floor(ball[i].pos.z * 3)) == (z2 = floor(pos.z * 3)))
		{
			float hitAngle = atan2(pos.z - ball[i].pos.z, pos.x - ball[i].pos.x);
			vec += D3DXVECTOR3(cos(hitAngle), 0, sin(hitAngle)) * (ball[i].vec.x + ball[i].vec.y + ball[i].vec.z) * 0.3f;
		}
	}

	//----------------------------------------------------------
	//	相手プレイヤーへの当たり判定
	//----------------------------------------------------------
	//	球と相手プレイヤー
	if (pow(pos.x - player2.pos.x, 2) + pow(pos.z - player2.pos.z, 2) <= pow(0.5 + 0.15, 2)
		&& pow(pos.x - player2.pos.x, 2) + pow(pos.y - player2.pos.y, 2) <= pow(0.5 + 0.15, 2))
	{
		float hitAngle = atan2(pos.z - player2.pos.z, pos.x - player2.pos.x);
		vec = D3DXVECTOR3(cos(hitAngle), 0, sin(hitAngle)) * 0.05f;
		playerCount2 += 1;
		playerFlag2 = true;
	}
}

void Ball::Update_B(Player2 &player2, std::vector<Ball> ball, int index, Player &player)
{
	vec *= 0.995f;
	vec.y -= 0.0003f;

	pos += vec;

	if (pos.x < -7.35f)
	{
		vec.x = -vec.x;
		pos.x = -7.35f;
	}
	if (pos.x > 7.35f)
	{
		vec.x = -vec.x;
		pos.x = 7.35f;
	}
	if (pos.y < -4.85f)
	{
		vec.y = -vec.y;
		pos.y = -4.85f;
	}
	if (pos.y > 4.85f)
	{
		vec.y = -vec.y;
		pos.y = 4.85f;
	}
	if (pos.z < -7.35f)
	{
		vec.z = -vec.z;
		pos.z = -7.35f;
	}
	if (pos.z > 7.35f)
	{
		vec.z = -vec.z;
		pos.z = 7.35f;
	}

	if (pow(pos.x - player2.pos.x, 2) + pow(pos.z - player2.pos.z, 2) <= pow(0.5 + 0.15, 2)
		&& pow(pos.x - player2.pos.x, 2) + pow(pos.y - player2.pos.y, 2) <= pow(0.5 + 0.15, 2))
	{
		float hitAngle = atan2(pos.z - player2.pos.z, pos.x - player2.pos.x);
		vec = D3DXVECTOR3(cos(hitAngle), 0, sin(hitAngle)) * 0.05f;
	}

	for (int i = 0; i < ball.size(); i++)
	{
		if (index == i)
			continue;

		float x1, x2, y1, y2, z1, z2;

		if ((x1 = floor(ball[i].pos.x * 3)) == (x2 = floor(pos.x * 3))
			&& (y1 = floor(ball[i].pos.y * 3)) == (y2 = floor(pos.y * 3))
			&& (z1 = floor(ball[i].pos.z * 3)) == (z2 = floor(pos.z * 3)))
		{
			float hitAngle = atan2(pos.z - ball[i].pos.z, pos.x - ball[i].pos.x);
			vec += D3DXVECTOR3(cos(hitAngle), 0, sin(hitAngle)) * (ball[i].vec.x + ball[i].vec.y + ball[i].vec.z) * 0.3f;
		}
	}
	
	//----------------------------------------------------------
	//	相手プレイヤーへの当たり判定
	//----------------------------------------------------------
	//	球と相手プレイヤー
	if (pow(pos.x - player.pos.x, 2) + pow(pos.z - player.pos.z, 2) <= pow(0.5 + 0.15, 2)
		&& pow(pos.x - player.pos.x, 2) + pow(pos.y - player.pos.y, 2) <= pow(0.5 + 0.15, 2))
	{
		float hitAngle = atan2(pos.z - player.pos.z, pos.x - player.pos.x);
		vec = D3DXVECTOR3(cos(hitAngle), 0, sin(hitAngle)) * 0.05f;
		playerCount += 1;
		playerFlag = true;
	}

}

void Ball::Draw(Mesh *ballMesh, Texture *ballTexture, Mesh *shadowMesh, Texture *shadowTexture)
{
	ballMesh->Draw(&pos, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0.3f, 0.3f, 0.3f), ballTexture->Get());
	shadowMesh->Draw(&D3DXVECTOR3(pos.x, -5, pos.z), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0.2f, 1.0f, 0.2f), shadowTexture->Get());
}

BallAdmin::BallAdmin()
{
	mesh = new Mesh[2];
	mesh[0].Load(_T("Mesh/Ball.x"));
	mesh[1].Load(_T("Mesh/Shadow.x"));
	texture = new Texture[3];
	texture[0].Load(_T("Texture/Ball.jpg"));
	texture[1].Load(_T("Texture/Shadow.png"));
	texture[2].Load(_T("Texture/Ball_2.jpg"));
	ball_1.clear();
	ball_2.clear();
}

BallAdmin::~BallAdmin()
{
	delete[] texture;
	delete[] mesh;
}

void BallAdmin::Set(D3DXVECTOR3 pos, D3DXVECTOR3 vec, int Num)
{
	ball_1.push_back(Ball(pos, vec));
	if (ball_1.size() > Num)
		ball_1.erase(ball_1.begin() + 0);

	ball_2.push_back(Ball(pos, vec));
	if (ball_2.size() > Num)
		ball_2.erase(ball_2.begin() + 0);

}

void BallAdmin::Draw(Player &player, Player2 &player2)
{
	for (int i = 0; i < ball_1.size(); i++)
	{
		ball_1[i].Update(player, ball_1, i, player2);
		ball_1[i].Draw(&mesh[0], &texture[0], &mesh[1], &texture[1]);
	}
}

void BallAdmin::Draw_B(Player2 &player2, Player &player)
{
	for (int i = 0; i < ball_2.size(); i++)
	{
		ball_2[i].Update_B(player2, ball_2, i, player);
		ball_2[i].Draw(&mesh[0], &texture[2], &mesh[1], &texture[1]);
	}
}
