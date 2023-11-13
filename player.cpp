#include "main.h"
#include"manager.h"
#include "renderer.h"
#include"input.h"
#include"scene.h"
#include"player.h"
#include"bullet.h"
#include"box.h"
#include"cylinder.h"
#include"audio.h"
#include"shadow.h"
#include<windows.h>
#include"house.h"
#include"wall.h"
#include"bill1.h"
#include"bill2.h"
#include"playerHPGage.h"

void Player::Init()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\TigerIIPaintTaiya.obj");
	
	speed = 1.0f;
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\vertexLightingPS.cso");


	m_ShotSE = AddComponent<Audio>();
	m_ShotSE->Load("asset\\audio\\shotTank2.wav");

	m_StayEnginBGM = AddComponent<Audio>();
	m_StayEnginBGM->Load("asset\\audio\\車のエンジンをかける1.wav");

	m_EnginBGM =AddComponent<Audio>();
	m_EnginBGM->Load("asset\\audio\\moveTank.wav");

	

	//m_Shadow = AddComponent<Shadow>();


}

void Player::Uninit()
{
	GameObject::Uninit();

	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	//GameObject::Uninit();
}

void Player::Update()
{
	D3DXVECTOR3 oldPosition = m_Position;
	GameObject::Update();
	
	
	
	Scene* scene = Manager::GetScene();
	
	
	
	D3DXVECTOR3 directionX(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 directionZ(0.0f, 0.0f, 0.0f);

	////サードパーソンビュー(斜め移動)
	if (Input::GetKeyPress('W')) { directionZ = GetForward();  speed = 0.3f; }
	else if (Input::GetKeyPress('S')) { directionZ = -GetForward(); speed = 0.3f; }
	else
	{
		if (!MoveFlag)
		{
			m_StayEnginBGM->Volume(0.01f);
			m_StayEnginBGM->Play(true);
			m_EnginBGM->Stop();
			MoveFlag = true;
		}
		
	}

	//x,zを加算します
	D3DXVECTOR3 direction = directionX + directionZ;
	//正規化します
	D3DXVec3Normalize(&direction, &direction);
	//PositonにSpeed加算します
	m_Position += direction*speed;
	

	if (Input::GetKeyPress('A'))
	{
		m_Rotation.y -= 0.01f;
	}
	if (Input::GetKeyPress('D'))
	{
		m_Rotation.y += 0.01f;
	}


	
	if (Input::GetKeyTrigger('W') || Input::GetKeyTrigger('S'))
	{
		m_EnginBGM->Volume(0.1f);
		m_EnginBGM->Play(true);
		m_StayEnginBGM->Stop();
		MoveFlag = false;
	}
	
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
		D3DXVECTOR3 scale = box->GetScale() * 2;
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
				m_Position.x = oldPosition.x;
				m_Position.z = oldPosition.z;
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

		if (postion.x - scale.x + 0.5 < m_Position.x &&
			m_Position.x < postion.x + scale.x  -0.5&&
			postion.z - scale.z - 2.5f < m_Position.z &&
			m_Position.z < postion.z + scale.z + 1.5f)
		{
			if (m_Position.y < postion.y + (scale.y - 0.5f) * 2.0f)
			{
				m_Position.x = oldPosition.x;
				m_Position.z = oldPosition.z;
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
			postion.z - scale.z - 4.5f < m_Position.z &&
			m_Position.z < postion.z + scale.z  -7.5f)
		{
			if (m_Position.y < postion.y + (scale.y - 0.5f) * 2.0f)
			{
				m_Position.x = oldPosition.x;
				m_Position.z = oldPosition.z;
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

		if (postion.x - scale.x  +20.5f < m_Position.x &&
			m_Position.x < postion.x + scale.x - 20.5f &&
			postion.z - scale.z - 4.5f < m_Position.z &&
			m_Position.z < postion.z + scale.z - 20.5f)
		{
			if (m_Position.y < postion.y + (scale.y - 0.5f) * 2.0f)
			{
				m_Position.x = oldPosition.x;
				m_Position.z = oldPosition.z;
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

	PlayerHPGage* playerHPGage = scene->GetGameObject<PlayerHPGage>();

;	if(playerHPGage->sizeX <= 0)
	{
		m_Dead = true;
	}
	/*D3DXVECTOR3 shadowPosition = m_Position;
	shadowPosition.y = groundHeight;
	m_Shadow->SetPosition(shadowPosition);*/

	if (Input::GetKeyPress(VK_LSHIFT))
	{
		m_KillCount = 10;
	}
	if (Input::GetKeyPress(VK_RSHIFT))
	{
		m_Dead = true;
	}
	
}

void Player::Draw()
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

