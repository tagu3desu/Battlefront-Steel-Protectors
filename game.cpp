#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"game.h"
#include "polygon2D.h"
#include "field.h"
#include"camera.h"
#include"player.h"	
#include"enemy.h"
#include"Cylinder.h"
#include"bullet.h"
#include"explosion.h"
#include"box.h"
#include"input.h"
#include"crossHear.h"
#include"score.h"
#include"audio.h"
#include"sky.h"
#include"fade.h"
#include"enemyGage.h"
#include"playergun.h"
#include"enemydethState.h"
#include"HPbottom.h"
#include"enemybullet.h"
#include"playerHPGage.h"
#include"tree.h"
#include"house.h"
#include"breakheri.h"
#include"bill1.h"
#include"bulletNumber.h"
#include"bulletUI.h"
#include"wall.h"
#include"bill2.h"
#include"gameover.h"
#include"gameclear.h"
#include"crushing.h"
#include"cyutoriaru.h"

void Game::Init()
{
	Bullet::Load();
	Enemy::Load();
	DethEnemy::Load();
	EnemyBullet::Load();

	AddGameObject<Camera>(0);
	AddGameObject<Sky>(1)->SetScale(D3DXVECTOR3(200.0f,200.0f,200.0f));
	AddGameObject<Field>(1);

	
	auto* enemy1= AddGameObject<Enemy>(1);
	enemy1->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 15.0f));
	//enemy1->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	auto* enemy2 = AddGameObject<Enemy>(1);
	enemy2->SetPosition(D3DXVECTOR3(-40.0f, 0.0f, 5.0f));
	//enemy2->SetRotation(D3DXVECTOR3(0.0f, 187.0f, 0.0f));

	auto* enemy3 = AddGameObject<Enemy>(1);
	enemy3->SetPosition(D3DXVECTOR3(-45.0f, 0.0f, 45.0f));
	//enemy3->SetRotation(D3DXVECTOR3(0.0f, 168.0f, 0.0f));

	auto* enemy4 = AddGameObject<Enemy>(1);
	enemy4->SetPosition(D3DXVECTOR3(-10.0f, 0.0f, 95.0f));

	auto* enemy5 = AddGameObject<Enemy>(1);
	enemy5->SetPosition(D3DXVECTOR3(20.0f, 0.0f, 95.0f));

	auto* enemy6 = AddGameObject<Enemy>(1);
	enemy6->SetPosition(D3DXVECTOR3(40.0f, 0.0f, 95.0f));
	
	auto* enemy7 = AddGameObject<Enemy>(1);
	enemy7->SetPosition(D3DXVECTOR3(60.0f, 0.0f, 95.0f));
	//enemy7->SetRotation(D3DXVECTOR3(0.0f, 120.0f, 0.0f));

	auto* enemy8 = AddGameObject<Enemy>(1);
	enemy8->SetPosition(D3DXVECTOR3(-60.0f, 0.0f, 95.0f));
	//enemy8->SetRotation(D3DXVECTOR3(0.0f, 150.0f, 0.0f));

	

	//マップ関連
	//壁
	{
		Box* box = AddGameObject<Box>(1);
		box->SetPosition(D3DXVECTOR3(-50.0f, 0.0f, 0.0f));
		box->SetScale(D3DXVECTOR3(1.0f, 3.0f, 10.2f));

		Box* box2 = AddGameObject<Box>(1);
		box2->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -50.0f));
		box2->SetScale(D3DXVECTOR3(350.0f, 3.0f, 0.05f));	

		Box* box3 = AddGameObject<Box>(1);
		box3->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 50.0f));
		box3->SetScale(D3DXVECTOR3(350.0f, 3.0f, 0.05f));
	
		Box* box4 = AddGameObject<Box>(1);
		box4->SetPosition(D3DXVECTOR3(50.0f, 0.0f, 0.0f));
		box4->SetScale(D3DXVECTOR3(1.0f, 3.0f, 10.2f));

		AddGameObject<House>(1)->SetPosition(D3DXVECTOR3(35.0f, 0.0f, 0.0f));
		AddGameObject<House>(1)->SetPosition(D3DXVECTOR3(35.0f, 0.0f, -20.0f));
		AddGameObject<House>(1)->SetPosition(D3DXVECTOR3(35.0f, 0.0f, 15.0f));
		AddGameObject<House>(1)->SetPosition(D3DXVECTOR3(35.0f, 0.0f, 35.0f));

		AddGameObject<Tree>(1)->SetPosition(D3DXVECTOR3(-35.0f, 0.0f, 25.0f));
		AddGameObject<Tree>(1)->SetPosition(D3DXVECTOR3(-10.0f, 0.0f, 40.0f));
		AddGameObject<Tree>(1)->SetPosition(D3DXVECTOR3(35.0f, 0.0f, -10.0f));

		auto* bill1_1 = AddGameObject<Bill1>(1);
		bill1_1->SetPosition(D3DXVECTOR3(0.0f, 0.01f, -30.0f));

		auto* bill1_2 = AddGameObject<Bill1>(1);
		bill1_2->SetPosition(D3DXVECTOR3(20.0f, 0.01f, -30.0f));

		auto* bill2 = AddGameObject<Bill2>(1);
		bill2->SetPosition(D3DXVECTOR3(-24.5f, 0.01f, -37.0f));
		
		auto* wall1 = AddGameObject<Wall>(1);
		wall1->SetPosition(D3DXVECTOR3(-42.0f, 0.0f, 40.0f));
		wall1->SetScale(D3DXVECTOR3(7.0f, 3.0f, 1.0f));

		auto* wall2 = AddGameObject<Wall>(1);
		wall2->SetPosition(D3DXVECTOR3(-42.0f, 0.0f, 0.0f));
		wall2->SetScale(D3DXVECTOR3(7.0f, 3.0f, 1.0f));

		auto* wall3 = AddGameObject<Wall>(1);
		wall3->SetPosition(D3DXVECTOR3(-50.0f, 0.0f, 0.0f));
		wall3->SetScale(D3DXVECTOR3(0.0f, 3.0f, 55.5f));

		auto* wall4 = AddGameObject<Wall>(1);
		wall4->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -50.0f));
		wall4->SetScale(D3DXVECTOR3(55.5f, 3.0f, 0.0f));

		auto* wall5 = AddGameObject<Wall>(1);
		wall5->SetPosition(D3DXVECTOR3(50.0f, 0.0f, 0.0f));
		wall5->SetScale(D3DXVECTOR3(0.0f, 3.0f, 55.5f));

		auto* wall6 = AddGameObject<Wall>(1);
		wall6->SetPosition(D3DXVECTOR3(8.0f, 0.0f, 0.0f));
		wall6->SetScale(D3DXVECTOR3(3.0f, 1.5f, 1.0f));

		auto* wall7 = AddGameObject<Wall>(1);
		wall7->SetPosition(D3DXVECTOR3(-8.0f, 0.0f, 10.0f));
		wall7->SetScale(D3DXVECTOR3(3.0f, 1.5f, 1.0f));

		auto* wall8 = AddGameObject<Wall>(1);
		wall8->SetPosition(D3DXVECTOR3(-16.0f, 0.0f, 30.0f));
		wall8->SetScale(D3DXVECTOR3(3.0f, 1.5f, 1.0f));

		auto* wall9 = AddGameObject<Wall>(1);
		wall9->SetPosition(D3DXVECTOR3(16.0f, 0.0f, 40.0f));
		wall9->SetScale(D3DXVECTOR3(3.0f, 1.5f, 1.0f));
	}
	

	
	Player* player = AddGameObject<Player>(1);
	player->SetPosition(D3DXVECTOR3(10.0f, 0.0f,-40.0f));
	player->SetScale(D3DXVECTOR3(0.5f, 0.5f, 0.5f));

	PlayerGun* playergun = AddGameObject<PlayerGun>(1);
	playergun->SetPosition(D3DXVECTOR3(3.5f, 0.0f, 0.0f));
	playergun->SetScale(D3DXVECTOR3(0.5f, 0.5f, 0.5f));

	
	AddGameObject<CrossHear>(2);
	AddGameObject<HPBottom>(2);



	
	AddGameObject<Cyutoriaru>(2);
	AddGameObject<BulletNumber>(2);
	AddGameObject<BulletUI>(2);
	AddGameObject<Crushing>(2);
	AddGameObject<Score>(2);

	
	


	AddGameObject<PlayerHPGage>(2);
	m_Fade = AddGameObject<Fade>(2);
	
  
	
}


void Game::Update()
{
	Scene::Update();
	
	Player* player = GetGameObject<Player>();
	if (player->m_Dead)
	{
		m_Fade->FadeOut();
		toGameOver = true;
	}
	if (player->m_KillCount>=8)
	{
		m_Fade->FadeOut();
		toGameClear = true;
	}
	if (m_Fade->GetFadeFinish()&& toGameOver)
	{
		Manager::SetScene<GameOver>();
	}
	if (m_Fade->GetFadeFinish() && toGameClear)
	{
		Manager::SetScene<GameClear>();
	}
	

}

void Game::Uninit()
{
	Scene::Uninit();
	Bullet::Unload();
	Enemy::Unload();
	DethEnemy::Unload();
	EnemyBullet::Unload();
}