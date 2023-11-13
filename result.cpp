#include"main.h"
#include"renderer.h"
#include"manager.h"
#include"title.h"
//#include"polygon2D.h"
#include"input.h"
#include"scene.h"
#include"result.h"
#include"resultLogo.h"
void Result::Init()
{
	//AddGameObject<Polygon2D>(2);
	AddGameObject<ResultLogo>(2);
}


void Result::Update()
{
	Scene::Update();

	//�L�[���͂ŃQ�[����ʂɑJ��
	if (Input::GetKeyTrigger(VK_SPACE))//Enter�L�[
	{
		Manager::SetScene<Title>();
	}
}


