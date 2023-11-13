#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"scene.h"
#include"enemybullet.h"
#include"player.h"
#include"explosion.h"
#include"enemy.h"
#include"enemyGage.h"
#include"cylinder.h"
#include"box.h"
#include"score.h"
#include"shadow.h"
#include"playerHPGage.h"
#include"wall.h"
#include"bill1.h"
#include"bill2.h"
#include"house.h"
Model* EnemyBullet::m_Model{};

void EnemyBullet::Init()
{
	m_Scale = D3DXVECTOR3(0.1f, 0.1f, 0.1f);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\vertexLightingPS.cso");

	Scene* scene = Manager::GetScene();
	m_Shadow = AddComponent<Shadow>();
}

void EnemyBullet::Load()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\bullet.obj");
}

void EnemyBullet::Uninit()
{
	GameObject::Uninit();
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void EnemyBullet::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void EnemyBullet::Update()
{
	
	GameObject::Update();
	
	m_Position += m_Velocity;
	//プレイヤーとの衝突判定
	Scene* scene = Manager::GetScene();
	auto* playerHP = scene->GetGameObject<PlayerHPGage>();
	Score* score = scene->GetGameObject<Score>();
	auto  player = scene->GetGameObject<Player>();	
	D3DXVECTOR3 playerPos = player->GetPosition();
	D3DXVECTOR3 direction = m_Position - (playerPos + D3DXVECTOR3(0.0f,1.0f,0.0f)) ; 
	float length = D3DXVec3Length(&direction);
	if (length < 2.5f)
	{
			Explosion* explosion = scene->AddGameObject<Explosion>(1);
			explosion->SetScale(D3DXVECTOR3(3.0f, 3.0f, 3.0f));
			explosion->SetPosition(m_Position + D3DXVECTOR3(0.f, 0.1f, 0.0f));
			playerHP->sizeX -= 34.0f;
			SetDestroy();
			return;
	}
		
		
	
	//円柱との判定
	auto Cylindes = scene->GetGameObjects<Cylinder>();
	for (Cylinder* cylinder : Cylindes)
	{
		D3DXVECTOR3 postion = cylinder->GetPosition();
		D3DXVECTOR3 scale = cylinder->GetScale();

		D3DXVECTOR3 direction = m_Position - postion;
		direction.y = 0.0f;
		float length = D3DXVec3Length(&direction);
		if (length < scale.x)
		{
			if (m_Position.y < postion.y + scale.y - 0.5f)
			{
				Explosion* explosion = scene->AddGameObject<Explosion>(1);
				explosion->SetScale(D3DXVECTOR3(3.0f, 3.0f, 3.0f));
				explosion->SetPosition(m_Position + D3DXVECTOR3(0.f, 0.1f, 0.0f));
				SetDestroy();
			}
			break;
		}

	}
	//壁
	auto walls = scene->GetGameObjects<Wall>();
	for (Wall* wall : walls)
	{
		D3DXVECTOR3 postion = wall->GetPosition();
		D3DXVECTOR3 scale = wall->GetScale();

		if (postion.x - scale.x + 0.5f < m_Position.x &&
			m_Position.x < postion.x + scale.x - 0.5f &&
			postion.z - scale.z - 2.5f < m_Position.z &&
			m_Position.z < postion.z + scale.z + 1.5f)
		{
			if (m_Position.y < postion.y + (scale.y - 0.5f) * 2.0f)
			{
				Explosion* explosion = scene->AddGameObject<Explosion>(1);
				explosion->SetScale(D3DXVECTOR3(3.0f, 3.0f, 3.0f));
				explosion->SetPosition(m_Position + D3DXVECTOR3(0.f, 0.1f, 0.0f));
				SetDestroy();
			}
			break;
		}

	}

	//家
	auto houses = scene->GetGameObjects<House>();
	for (House* house : houses)
	{
		D3DXVECTOR3 postion = house->GetPosition();
		D3DXVECTOR3 scale = house->GetScale() * 40;

		if (postion.x - scale.x - 2.5f < m_Position.x &&
			m_Position.x < postion.x + scale.x + 0.5f &&
			postion.z - scale.z - 2.5f < m_Position.z &&
			m_Position.z < postion.z + scale.z + 1.5f)
		{
			if (m_Position.y < postion.y + (scale.y - 0.5f) * 2.0f)
			{
				Explosion* explosion = scene->AddGameObject<Explosion>(1);
				explosion->SetScale(D3DXVECTOR3(3.0f, 3.0f, 3.0f));
				explosion->SetPosition(m_Position + D3DXVECTOR3(0.f, 0.1f, 0.0f));
				SetDestroy();
			}
			break;
		}
	}


	//ビル1
	auto bills1 = scene->GetGameObjects<Bill1>();
	for (Bill1* bill1 : bills1)
	{
		D3DXVECTOR3 postion = bill1->GetPosition();
		D3DXVECTOR3 scale = bill1->GetScale() * 1.7;
		if (postion.x - scale.x + 3.5f < m_Position.x &&
			m_Position.x < postion.x + scale.x - 3.5f &&
			postion.z - scale.z - 3.5f < m_Position.z &&
			m_Position.z < postion.z + scale.z - 7.5f)
		{
			if (m_Position.y < postion.y + (scale.y - 0.5f) * 2.0f)
			{
				Explosion* explosion = scene->AddGameObject<Explosion>(1);
				explosion->SetScale(D3DXVECTOR3(3.0f, 3.0f, 3.0f));
				explosion->SetPosition(m_Position + D3DXVECTOR3(0.f, 0.1f, 0.0f));
				SetDestroy();
			}
			break;
		}
	}

	//ビル2
	auto bills2 = scene->GetGameObjects<Bill2>();
	for (Bill2* bill2 : bills2)
	{
		D3DXVECTOR3 postion = bill2->GetPosition();
		D3DXVECTOR3 scale = bill2->GetScale() * 100.0;

		if (postion.x - scale.x + 20.5f < m_Position.x &&
			m_Position.x < postion.x + scale.x - 20.5f &&
			postion.z - scale.z - 4.5f < m_Position.z &&
			m_Position.z < postion.z + scale.z - 20.5f)
		{
			if (m_Position.y < postion.y + (scale.y - 0.5f) * 2.0f)
			{
				Explosion* explosion = scene->AddGameObject<Explosion>(1);
				explosion->SetScale(D3DXVECTOR3(3.0f, 3.0f, 3.0f));
				explosion->SetPosition(m_Position + D3DXVECTOR3(0.f, 0.1f, 0.0f));
				SetDestroy();
			}
			break;
		}

	}

	D3DXVECTOR3 shadowposition = m_Position;
	shadowposition.y = 0.0f;
	m_Shadow->SetPosition(shadowposition);
	m_Shadow->SetScale(D3DXVECTOR3(0.1f, 0.1f, 0.1f));
}

void EnemyBullet::Draw()
{
	GameObject::Draw();

	//入力レイアウト
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}