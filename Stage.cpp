#include "vtx.h"
#include "Stage.h"
using namespace vtx;

Stage::Stage()
{
	mesh = new Mesh(_T("Mesh/Stage.x"));
	texture = new Texture(_T("Texture/Wood.png"));
}

Stage::~Stage()
{
	delete texture;
	delete mesh;
}

void Stage::Draw()
{
	mesh->Draw(&D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(1, 1, 1), texture->Get());
}
