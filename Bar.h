#pragma once

class vtx::Mesh;
class vtx::Texture;



class Bar
{
	//----------------------------------------------
	//	バーの表示
	//----------------------------------------------
	D3DXVECTOR3 pos_1;
	D3DXVECTOR3 scale_1;
	D3DXVECTOR3 pos_2;
	D3DXVECTOR3 scale_2;
	D3DXVECTOR3 pos_3;
	D3DXVECTOR3 scale_3;
	float timer;
	int startCount;

	//----------------------------------------------
	//	時間の表示
	//----------------------------------------------
	D3DXVECTOR3 secPos;
	D3DXVECTOR3 secScale;
	D3DXVECTOR3 secRot;
private:
	vtx::Mesh *mesh;
	vtx::Texture *texture;
	vtx::Mesh *sec;
	vtx::Texture *secTex;

public:
	Bar();

	~Bar();

	void Draw();
};