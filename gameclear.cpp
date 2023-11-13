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

	//�L�[���͂ŃQ�[����ʂɑJ��
	if (Input::GetKeyTrigger(VK_SPACE))//Enter�L�[
	{
		Manager::SetScene<Title>();
	}
}


