#include"main.h"
#include"renderer.h"
#include"manager.h"
#include"title.h"
#include"clearLogo.h"
#include"input.h"
#include"scene.h"
#include"gameclear.h"
#include"titlebutton.h"

void GameClear::Init()
{
	AddGameObject<ClearLogo>(2);
	AddGameObject<TitleButton>(2);
}


void GameClear::Update()
{
	Scene::Update();

	//キー入力でゲーム画面に遷移
	if (Input::GetKeyTrigger(VK_SPACE))//Enterキー
	{
		Manager::SetScene<Title>();
	}
}


