#pragma once

class vtx::Mesh;
class vtx::Texture;
class Player;

class Ball
{
private:

	D3DXVECTOR3 pos;
	D3DXVECTOR3 vec;

public:

	Ball();

	Ball(D3DXVECTOR3 pos, D3DXVECTOR3 vec);

	~Ball();

	void Update(Player &player, std::vector<Ball> ball, int index);

	void Draw(vtx::Mesh *ballMesh, vtx::Texture *ballTexture, vtx::Mesh *shadowMesh, vtx::Texture *shadowTexture);

};

class BallAdmin
{
private:

	vtx::Mesh *mesh;
	vtx::Texture *texture;
	std::vector<Ball> ball;

public:

	BallAdmin();

	~BallAdmin();

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 vec, int Num);

	void Draw(Player &player);

};
