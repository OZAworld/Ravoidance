#pragma once

extern class BallAdmin;
class Player2;

enum PlayerType
{
	�L���[�u,
	�I�N�^��,
	�X�t�B�A,
};

class Player
{
public:

	D3DXVECTOR3 pos;
	D3DXVECTOR3 accel;
	D3DXVECTOR3 vec;
	float vy;
	float angleY;
	vtx::Mesh *mesh;
	vtx::Texture *texture;
	PlayerType _PT;


	Player();

	Player(D3DXVECTOR3 &pos, float angleY);

	~Player();

	void Draw(BallAdmin *ball_1);

	void Hit(Player2 &player2);
};
