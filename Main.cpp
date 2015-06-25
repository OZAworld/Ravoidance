#include "vtx.h"
#include "Player.h"
#include "2Player.h"
#include "Ball.h"
#include "Bar.h"
#include "Stage.h"
using std::unique_ptr;
using namespace vtx;

enum _GameState
{
	GAME_MAIN,
	GAME_RESULT,
};
_GameState gs;

//int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
int main()
{
	unique_ptr<Lib> lib(new Lib(_T("Ravoidance"), 1280, 720, false));
	float angle = -70;
	unique_ptr<Camera> camera(new Camera(D3DXVECTOR3(0, cos(D3DXToRadian(angle)) * 22 - 1, sin(D3DXToRadian(angle)) * 22), D3DXVECTOR3(D3DXToRadian(angle + 90), 0, 0)));
	unique_ptr<Stage> stage(new Stage());
	unique_ptr<Player> player(new Player(D3DXVECTOR3(-5, -4.5, 0), 0));
	player->texture[0].Load(_T("Texture/Red.png"));
	player->texture[1].Load(_T("Texture/Shadow.png"));
	unique_ptr<Player2> player2(new Player2(D3DXVECTOR3(0, -4.5, 5), 0));
	player2->texture[0].Load(_T("Texture/Blue.png"));
	player2->texture[1].Load(_T("Texture/Shadow.png"));
	unique_ptr<BallAdmin> ball_1(new BallAdmin());
	unique_ptr<BallAdmin> ball_2(new BallAdmin());
	unique_ptr<Bar> bar(new Bar());

	gs = GAME_MAIN;
	int c = 0;

	while (app->wnd->MessageLoop())
	{
		switch (gs)
		{
			case GAME_MAIN:
				render->Start();
				render->Clear(0xff000000);

				extern bool GameSet;
				if (GameSet == true)
				{
					c++;
					if (c > 100)
						gs = GAME_RESULT;
				}

				stage->Draw();

				player->Draw(ball_1.get());

				player2->Draw(ball_2.get());
				player->Hit(*player2);
				player2->Hit(*player);

				ball_1->Draw(*player, *player2);

				ball_2->Draw_B(*player2, *player);

				bar->Draw();

				render->End();

				break;
				
			case GAME_RESULT:
				render->Start();

				extern int playerCount;
				extern int playerCount2;
				
				if (playerCount > playerCount2)
				{
					render->Clear(0xff7fffd4);
				}
				else
				{
					render->Clear(0xffff6347);
				}

				render->End();
				break;
		}
	}

	return 0;
}
