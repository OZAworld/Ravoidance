#pragma once

extern class BallAdmin;

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
	float vy;
	float angleY;
	vtx::Mesh *mesh;
	vtx::Texture *texture;

	Player();

	Player(D3DXVECTOR3 &pos, float angleY);

	~Player();

	void Draw(BallAdmin *ball);

};
