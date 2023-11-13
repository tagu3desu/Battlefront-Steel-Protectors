#include"main.h"
#include"renderer.h"
#include"manager.h"
#include"title.h"
#include"polygon2D.h"
#include"input.h"
#include"scene.h"
#include"gameover.h"
#include"titlebutton.h"

void GameOver::Init()
{
	AddGameObject<Polygon2D>(2);
	AddGameObject<TitleButton>(2);
}


void GameOver::Update()
{
	Scene::Update();

	//キー入力でゲーム画面に遷移
	if (Input::GetKeyTrigger(VK_SPACE))//Enterキー
	{
		Manager::SetScene<Title>();
	}
}


