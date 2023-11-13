#include "main.h"
#include"manager.h"
#include "renderer.h"
#include"input.h"
#include"scene.h"
#include"playergun.h"
#include"player.h"
#include"bullet.h"
#include"box.h"
#include"cylinder.h"
#include"audio.h"
#include"shadow.h"
#include<windows.h>
#include"bulletNumber.h"
void PlayerGun::Init()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\TigerIIPaintGun.obj");
	
	speed = 1.0f;
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\vertexLightingPS.cso");


	m_ShotSE = AddComponent<Audio>();
	m_ShotSE->Load("asset\\audio\\TankFire.wav");

	m_ReloadSE = AddComponent<Audio>();
	m_ReloadSE->Load("asset\\audio\\Reload.wav");		
}

void PlayerGun::Uninit()
{
	GameObject::Uninit();

	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	//GameObject::Uninit();
}

void PlayerGun::Update()
{
	D3DXVECTOR3 oldPosition = m_Position;
	GameObject::Update();
	
	Scene* scene = Manager::GetScene();
	auto player = scene->GetGameObject<Player>();
	m_Position = player->GetPosition()+ player->GetForward()*-1.0;
	
	auto bulletNumber = scene->GetGameObject<BulletNumber>();
	

	//弾発射
	if (Input::GetKeyTrigger(VK_LBUTTON) && bulletCount > 0 && !m_FireFlag)
	{
		Bullet* bullet = scene->AddGameObject<Bullet>(1);
		bullet->SetPosition(m_Position + D3DXVECTOR3(0.0f, 1.0f, 0.0f));
		bullet->SetRotation(m_Rotation);
		bulletNumber->SubtractNumber(1);
		bulletCount -= 1;
		m_FireFlag = true;
		m_ShotSE->Volume(0.1f);
		m_ShotSE->Play();
	}

	if (m_FireFlag)
	{
		m_Framecount++;
	}
	if (m_Framecount > 60)
	{
		m_FireFlag = false;
		m_Framecount = 0;
	}
	

	if (Input::GetKeyTrigger('E'))
	{
		m_ReloadSE->Volume(0.1f);
		m_ReloadSE->Play();
		bulletNumber->SetCount(5);
		bulletCount = 5;
	}

	m_Rotation.y += GetMouseCursorPosX() / 600;
	//重力
	m_Velocity.y -= 0.015f;

	//ジャンプ用移動
	m_Position += m_Velocity;


	////障害物の衝突判定
	float groundHeight = 0.5f; //1,0f
	//円柱
	std::vector<Cylinder*> Cylinders = scene->GetGameObjects<Cylinder>();
	for (Cylinder* cylinder : Cylinders)//範囲for
	{
		D3DXVECTOR3 postion = cylinder->GetPosition();
		D3DXVECTOR3 scale = cylinder->GetScale();

		D3DXVECTOR3 direction2 = m_Position - postion;
		direction2.y = 0.0f;
		float length = D3DXVec3Length(&direction2);

		if (length < scale.x)
		{
			if (m_Position.y < postion.y + scale.y - 0.5f )
			{
				m_Position.x = oldPosition.x;
				m_Position.z = oldPosition.z;
				
			}
			else
			{
				
				groundHeight = postion.y + scale.y+groundHeight; //上判定
			}
			break;
		}

	}

	//四角柱
	std::vector<Box*> boxes = scene->GetGameObjects<Box>();

	for (Box* box : boxes)//範囲for
	{
		D3DXVECTOR3 postion = box->GetPosition();
		D3DXVECTOR3 scale = box->GetScale();
		if (postion.x - scale.x - 0.5f < m_Position.x &&
			m_Position.x < postion.x + scale.x + 0.5f &&
			postion.z - scale.z - 0.5f < m_Position.z &&
			m_Position.z < postion.z + scale.z + 0.5f)
		{
			if (m_Position.y < postion.y + (scale.y -0.5f)  * 2.0f)
			{
				m_Position.x = oldPosition.x;
				m_Position.z = oldPosition.z;
			}
			else
			{
				groundHeight = postion.y +groundHeight+ scale.y * 2.0f;
			}
			break;
		}
		

	}
	//接地
	if (m_Position.y < groundHeight && m_Velocity.y<0.0f)
	{
		m_Position.y = groundHeight;
		m_Velocity.y = 0.0f;
	}

}

void PlayerGun::Draw()
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
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y+D3DX_PI, m_Rotation.x, m_Rotation.z); //D3DX_PIで半周
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}

