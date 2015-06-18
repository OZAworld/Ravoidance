#pragma once

class vtx::Mesh;
class vtx::Texture;

class Bar
{
	D3DXVECTOR3 pos_1;
	D3DXVECTOR3 scale_1;
	D3DXVECTOR3 pos_2;
	D3DXVECTOR3 scale_2;


private:
	vtx::Mesh *mesh;
	vtx::Texture *texture;

public:
	Bar();

	~Bar();

	void Draw();
};