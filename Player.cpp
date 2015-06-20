#include <iostream>
#include <time.h>
#include "vtx.h"
#include "Player.h"
#include "2Player.h"
#include "Ball.h"
using namespace vtx;

Player::Player()
{
	pos = D3DXVECTOR3(0, 0, 0);
	vy = 0;
	angleY = 0;
	mesh = new Mesh[4];
	mesh[0].Load(_T("Mesh/Ball.x"));
	mesh[1].Load(_T("Mesh/Shadow.x"));
	mesh[2].Load(_T("Mesh/cube.x"));
	mesh[3].Load(_T("Mesh/ocutan.x"));
	texture = new Texture[2];
	_PT = キューブ;
}

Player::Player(D3DXVECTOR3 &pos, float angleY)
{
	Player::pos = pos;
	Player::vy = 0;
	Player::angleY = angleY;
	mesh = new Mesh[4];
	mesh[0].Load(_T("Mesh/Ball.x"));
	mesh[1].Load(_T("Mesh/Shadow.x"));
	mesh[2].Load(_T("Mesh/cube.x"));
	mesh[3].Load(_T("Mesh/ocutan.x"));
	texture = new Texture[2];
	_PT = キューブ;

}

Player::~Player()
{
	delete[] texture;
	delete[] mesh;
}

void Player::Draw(BallAdmin *ball_1)
{
	if (input->gamepad->Enable(1))
	{
		pos.x += floor(input->gamepad->LS().x * 2) * 0.1f + vec.x;
		pos.z += floor(input->gamepad->LS().y * 2) * 0.1f + vec.z;

		std::cout << floor(input->gamepad->LS().x * 2) * 0.1f << std::endl;
		std::cout << floor(input->gamepad->LS().y * 2) * 0.1f << std::endl;

		if (input->gamepad->LT() > 0.5f)
			vy = 0.1f;

		//angleY = atan2(-input->gamepad->RS().y, input->gamepad->RS().x);
		angleY += floor(input->gamepad->RS().x * 2) * 0.01f;

		//-----------------------------------------------------------------------------
		//	マシンガンの処理
		//-----------------------------------------------------------------------------
		static bool flag = false;
		static bool exist = false;
		static int c = 0;
		static float d = 0;
		c++;

		if (input->gamepad->RT() > 0.5f && flag == false&& c % 6 == 0)
		{
			exist = true;
			d++;
			std::cout << "%d" << d << std::endl;
		}
		else
		{
			exist = false;
		}
		if (exist == true && d < 21)
		{
			D3DXVec3Normalize(&accel, &D3DXVECTOR3(rand() % 5, rand() % 5, rand() % 5));
			ball_1->Set(pos + D3DXVECTOR3(cos(-angleY), 0, sin(-angleY)) * 1.0f, D3DXVECTOR3(cos(-angleY) + (accel.x * 0.1f), accel.y * 0.1f, sin(-angleY) + (accel.z * 0.1f)) * 0.3f, 40);
		}
		if (d > 21)
		{
			flag = true;
		}
		if (flag == true)
		{
			d -= 0.17f;
		}
		if (d < 0)
		{
			flag = false;
		}

		//-----------------------------------------------------------------------------
		//	ショットガンの処理
		//-----------------------------------------------------------------------------
		static bool flag2 = false;
		static bool exist2 = false;

		if (input->gamepad->GetDown(XINPUT_GAMEPAD_A)) //&& flag2 == false)
		{
			exist2 = true;
		}
		if (exist2 == true)
		{
			static int c = 0;
			c++;
			if (c < 21)
			{
				flag2 = true;
				D3DXVec3Normalize(&accel, &D3DXVECTOR3(rand() % 5 - 2, rand() % 5 - 2, rand() % 5 - 2));
				ball_1->Set(pos + D3DXVECTOR3(cos(-angleY), 0, sin(-angleY)) * 1.0f, D3DXVECTOR3(cos(-angleY) + (accel.x * 0.5f), accel.y * 0.5f, sin(-angleY) + (accel.z * 0.5f)) * 0.3f, 40);
			}
			if (c > 231)
			{
				flag2 = false;
				exist2 = false;
				c = 0;
			}
		}
	}
	else
	{
		if (input->key->Get(DIK_W))
			pos.z += 0.1f;
		if (input->key->Get(DIK_A))
			pos.x -= 0.1f;
		if (input->key->Get(DIK_S))
			pos.z -= 0.1f;
		if (input->key->Get(DIK_D))
			pos.x += 0.1f;
		if (input->key->Get(DIK_SPACE))
			vy = 0.1f;

		angleY = atan2(input->mouse->GetY() - app->wnd->GetRectClient().bottom / 2, input->mouse->GetX() - app->wnd->GetRectClient().right / 2);

		static bool flag = false;
		static bool exist = false;

		if ((input->mouse->GetButton(0)) && flag == false)
		{
			exist = true;
		}
		if (exist == true)
		{
			static int c = 0;
			c++;
			if (c < 126)
			{
				flag = true;
				D3DXVec3Normalize(&accel, &D3DXVECTOR3(rand() % 5, rand() % 5, rand() % 5));
				if (c % 6 == 0)
				{
					ball_1->Set(pos + D3DXVECTOR3(cos(-angleY), 0, sin(-angleY)) * 1.0f, D3DXVECTOR3(cos(-angleY) + (accel.x * 0.1f), accel.y * 0.1f, sin(-angleY) + (accel.z * 0.1f)) * 0.3f, 40);
				}
			}
			if (c > 246)
			{
				flag = false;
				exist = false;
				c = 0;
			}
		}
		static bool flag2 = false;
		static bool exist2 = false;

		if ((input->mouse->GetButton(1)) && flag2 == false)
		{
			exist2 = true;
		}
		if (exist2 == true)
		{
			static int c = 0;
			c++;
			if (c < 21)
			{
				flag2 = true;
				D3DXVec3Normalize(&accel, &D3DXVECTOR3(rand() % 5 - 2, rand() % 5 - 2, rand() % 5 - 2));
				ball_1->Set(pos + D3DXVECTOR3(cos(-angleY), 0, sin(-angleY)) * 1.0f, D3DXVECTOR3(cos(-angleY) + (accel.x * 0.5f), accel.y * 0.5f, sin(-angleY) + (accel.z * 0.5f)) * 0.3f, 40);
			}
			if (c > 231)
			{
				flag2 = false;
				exist2 = false;
				c = 0;
			}
		}

		//-----------------------------------------------------------------------------
		//	スナイパーライフルの処理
		//-----------------------------------------------------------------------------
		static bool flag3 = false;
		static bool exist3 = false;
		static int d = 0;

		if (GetAsyncKeyState(VK_RETURN) && flag3 == false)
		{
			exist3 = true;
			srand((unsigned int)time(NULL));
		}
		if (exist3 == true)
		{
			static int c = 0;
			c++;
			if (c < 180)
			{
				flag3 = true;
				D3DXVec3Normalize(&accel, &D3DXVECTOR3(rand() % 5 - 2, rand() % 5 - 2, rand() % 5 - 2));
				if (c % 30 == 0)
				{
					ball_1->Set(pos + D3DXVECTOR3(cos(-angleY), 0, sin(-angleY)) * 1.0f, D3DXVECTOR3(cos(-angleY), accel.y * 0.1f, sin(-angleY)) * 1.2f, 20);
				}
			}
			if (c > 360)
			{
				flag3 = false;
				exist3 = false;
				c = 0;
			}
		}

	}

	pos.y += vy -= 0.01f;

	if (pos.x > 7.0f)
		pos.x = 7.0f;
	if (pos.x < -7.0f)
		pos.x = -7.0f;
	if (pos.y > 4.5f)
		pos.y = 4.5f;
	if (pos.y < -4.5f)
		pos.y = -4.5f;
	if (pos.z > 7.0f)
		pos.z = 7.0f;
	if (pos.z < -7.0f)
		pos.z = -7.0f;


	if (GetAsyncKeyState(0x31))
		_PT = キューブ;

	if (GetAsyncKeyState(0x32))
		_PT = オクタン;

	if (GetAsyncKeyState(0x33))
		_PT = スフィア;


	switch (_PT)
	{
	case キューブ:
		mesh[0].Draw(&pos, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), texture[0].Get());
		break;
	case オクタン:
		mesh[2].Draw(&pos, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), texture[0].Get());
		break;
	case スフィア:
		mesh[3].Draw(&pos, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), texture[0].Get());
		break;
	}
	mesh[1].Draw(&D3DXVECTOR3(pos.x, -5, pos.z), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0.75f, 0.75f, 0.75f), texture[1].Get());

	D3DXVECTOR3 laserPointer = pos;
	for (float i = 0;; i += 0.1f)
	{
		float tempX = pos.x + cos(-angleY) * i;
		float tempZ = pos.z + sin(-angleY) * i;

		if (tempX < -7.5)
		{
			laserPointer.x = -7.5;
			laserPointer.z = tempZ;
			break;
		}
		if (tempX > 7.5)
		{
			laserPointer.x = 7.5;
			laserPointer.z = tempZ;
			break;
		}

		if (tempZ < -7.5)
		{
			laserPointer.z = -7.5;
			laserPointer.x = tempX;
			break;
		}
		if (tempZ > 7.5)
		{
			laserPointer.z = 7.5;
			laserPointer.x = tempX;
			break;
		}

		mesh[0].Draw(&D3DXVECTOR3(tempX, pos.y, tempZ), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0.05f, 0.05f, 0.05f), texture[0].Get());
	}

	mesh[0].Draw(&laserPointer, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0.5f, 0.5f, 0.5f), texture[0].Get());
}

void Player::Hit(Player2 &player2)
{
	//	自分と相手プレイヤー
	if (pow(player2.pos.x - pos.x, 2) + pow(player2.pos.z - pos.z, 2) <= pow(0.5 + 0.5, 2)
		&& pow(player2.pos.x - pos.x, 2) + pow(player2.pos.y - pos.y, 2) <= pow(0.5 + 0.5, 2))
	{
		float hitAngle = atan2(player2.pos.z - pos.z, player2.pos.x - pos.x);
		player2.vec = D3DXVECTOR3(cos(hitAngle), 0, sin(hitAngle)) * 0.1f;
	}
	else
	{
		player2.vec.x -= 0.01f;
		player2.vec.z -= 0.01f;

		if (player2.vec.x < 0)
		{
			player2.vec.x = 0;
		}
		if (player2.vec.z < 0)
		{
			player2.vec.z = 0;
		}

	}
}