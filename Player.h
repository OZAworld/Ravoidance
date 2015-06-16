#pragma once

extern class BallAdmin;

enum PlayerType
{
	キューブ,
	オクタン,
	スフィア,
};

class Player
{
public:

	D3DXVECTOR3 pos;
	D3DXVECTOR3 accel;
	float vy;
	float angleY;
	vtx::Mesh *mesh;
	vtx::Texture *texture;
	PlayerType _PT;


	Player();

	Player(D3DXVECTOR3 &pos, float angleY);

	~Player();

	void Draw(BallAdmin *ball);

};
