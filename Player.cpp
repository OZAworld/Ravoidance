#include <iostream>
#include "vtx.h"
#include "Player.h"
#include "Ball.h"
using namespace vtx;

Player::Player()
{
	pos = D3DXVECTOR3(0, 0, 0);
	vy = 0;
	angleY = 0;
	mesh = new Mesh[2];
	mesh[0].Load(_T("Mesh/Ball.x"));
	mesh[1].Load(_T("Mesh/Shadow.x"));
	texture = new Texture[2];
}

Player::Player(D3DXVECTOR3 &pos, float angleY)
{
	Player::pos = pos;
	Player::vy = 0;
	Player::angleY = angleY;
	mesh = new Mesh[2];
	mesh[0].Load(_T("Mesh/Ball.x"));
	mesh[1].Load(_T("Mesh/Shadow.x"));
	texture = new Texture[2];
}

Player::~Player()
{
	delete[] texture;
	delete[] mesh;
}

void Player::Draw(BallAdmin *ball)
{
	if (input->gamepad->Enable(1))
	{
		pos.x += floor(input->gamepad->LS().x * 2) * 0.1f;
		pos.z += floor(input->gamepad->LS().y * 2) * 0.1f;

		std::cout << floor(input->gamepad->LS().x * 2) * 0.1f << std::endl;
		std::cout << floor(input->gamepad->LS().y * 2) * 0.1f << std::endl;

		if (input->gamepad->LT() > 0.5f)
			vy = 0.1f;

		//angleY = atan2(-input->gamepad->RS().y, input->gamepad->RS().x);
		angleY += floor(input->gamepad->RS().x * 2) * 0.01f;

		if (input->gamepad->RT() > 0.5f)
		{
			ball->Set(pos + D3DXVECTOR3(cos(-angleY), 0, sin(-angleY)) * 1.0f, D3DXVECTOR3(cos(-angleY), 0, sin(-angleY)) * 0.5f);
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

		if ((input->mouse->GetButton(0)))
		{
			ball->Set(pos + D3DXVECTOR3(cos(-angleY), 0, sin(-angleY)) * 1.0f, D3DXVECTOR3(cos(-angleY), 0, sin(-angleY)) * 0.5f);
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

	mesh[0].Draw(&pos, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), texture[0].Get());
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
