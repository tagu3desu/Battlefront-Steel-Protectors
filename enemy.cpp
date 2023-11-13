#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"scene.h"
#include"enemy.h"
#include"enemyGage.h"
#include"enemybullet.h"
#include"enemydethState.h"
#include"audio.h"
#include"player.h"
#include"score.h"

Model* Enemy::m_Model{};

void Enemy::Init()
{
	
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.8f, 0.8f, 0.8f);
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\vertexLightingPS.cso");


	m_EnemyShotSE = AddComponent<Audio>();
	m_EnemyShotSE->Load("asset\\audio\\shotTank2.wav");

	Scene* scene = Manager::GetScene();
	m_EnemyGage = scene->AddGameObject<EnemyGage>(0);
}

void Enemy::Load()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\TigerIIPaint.obj");
}

void Enemy::Uninit()
{
	

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
	m_EnemyGage->SetDestroy();
}

void Enemy::Unload(){
	m_Model->Unload();
	delete m_Model;
}

void Enemy::Update()
{
	m_EnemyGage->SetPosition(m_Position);
	Scene* scene = Manager::GetScene();
	auto* player = scene->GetGameObject<Player>();
	auto* score = scene->GetGameObject<Score>();

	//D3DXVECTOR3 playerPosition= player->GetPosition();
	//プレイヤーの位置をエネミーの位置を差分
	D3DXVECTOR3 direction = m_Position - player->GetPosition();
	D3DXVECTOR3 a = m_Position - player->GetPosition();
	float length = D3DXVec3Length(&a);


		m_bulletRate++;
		if (length < 10)
		{
			if (m_bulletRate > 120)
			{
				m_EnemyBullet = scene->AddGameObject<EnemyBullet>(1);
				m_EnemyBullet->SetPosition(m_Position + D3DXVECTOR3(0.0f, 2.0f, 0.0f));
				m_EnemyBullet->SetRotation(m_Rotation);
				m_EnemyBullet->SetVerocity(D3DXVECTOR3(GetForward().x * -1.3f, 0.0f, GetForward().z * -1.3f));
				m_EnemyShotSE->Volume(0.005f);
				m_EnemyShotSE->Play();
				m_bulletRate = 0;
			}
		}
		
		
		if (m_EnemyHP == 3)
		{
			m_EnemyGage->m_Red = 0.0f;
			m_EnemyGage->m_Green = 1.0f;
			m_EnemyGage->m_Blue = 0.0f;
			m_EnemyGage->m_GageX = 0.75f;
		}
		else if (m_EnemyHP == 2)
		{
			m_EnemyGage->m_Red = 1.0f;
			m_EnemyGage->m_Green = 1.0f;
			m_EnemyGage->m_Blue = 0.0f;
			m_EnemyGage->m_GageX = 0.5f;

		}
		else if (m_EnemyHP == 1)
		{
			m_EnemyGage->m_Red = 1.0f;
			m_EnemyGage->m_Green = 0.0f;
			m_EnemyGage->m_Blue = 0.0f;
			m_EnemyGage->m_GageX = 0.25f;
		}

		if (m_EnemyHP == 0)
		{
			SetDestroy();
			score->AddCount(1);
			player->m_KillCount += 1;
			DethEnemy* dethEnemy = scene->AddGameObject<DethEnemy>(1);
			dethEnemy->SetPosition(m_Position);
			dethEnemy->SetRotation(m_Rotation);
		}
	
		




		//上下の回転を無効にする
		direction.y = 0.0f;

		//方向ベクトルを正規化する
		D3DXVec3Normalize(&direction, &direction);

		m_Rotation.y = atan2f(direction.x, direction.z);


}

void Enemy::Draw()
{
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