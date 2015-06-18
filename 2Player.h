#pragma once

extern class BallAdmin;
class Player;

class Player2
{
public:

	D3DXVECTOR3 pos;
	D3DXVECTOR3 accel;
	D3DXVECTOR3 vec;
	float vy;
	float angleY;
	vtx::Mesh *mesh;
	vtx::Texture *texture;

	Player2();

	Player2(D3DXVECTOR3 &pos, float angleY);

	~Player2();

	void Draw(BallAdmin *ball_2);

	void Hit(Player &player);
};
