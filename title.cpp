#include"main.h"
#include"renderer.h"
#include"manager.h"
#include"title.h"
#include"audio.h"
#include"polygon2D.h"
#include"input.h"
#include"scene.h"
#include"game.h"
#include"titleLogo.h"
#include"fade.h"
#include"titlebutton.h"
#include"loading.h"

void Title::Init()
{
	AddGameObject<TitleLogo>(2);
	m_Fade = AddGameObject<Fade>(2);
	m_TitleButton = AddGameObject<TitleButton>(2);
	m_Loading = AddGameObject<Loading>(2);
	m_Loading->m_AlfaColor = 0.0f;
	
	
}


void Title::Update()
{
	Scene::Update();

	//キー入力でゲーム画面に遷移
	if (Input::GetKeyTrigger(VK_SPACE))//Enterキー
	{
		m_Fade->FadeOut();
		
	}
	if (m_Fade->GetHarfFadeFinish())
	{
		m_Loading->m_AlfaColor = 1.0f;
	}
	if (m_Fade->GetFadeFinish())
	{
		
		Manager::SetScene<Game>();
	}
}


