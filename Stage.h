#pragma once

class Stage
{
private:

	vtx::Mesh *mesh;
	vtx::Texture *texture;

public:

	Stage();

	~Stage();

	void Draw();

};
