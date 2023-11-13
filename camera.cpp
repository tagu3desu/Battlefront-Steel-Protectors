#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"camera.h"
#include"player.h"
#include"playergun.h"
#include"scene.h"
#include"input.h"
void Camera::Init()
{	
	
	m_Position = D3DXVECTOR3(0.0f, 5.0f, -20.0f);
	m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	

}
void Camera::Update()
{

	Scene* scene =  Manager::GetScene();
	PlayerGun* playergun  = scene->GetGameObject<PlayerGun>();

	//トップビュー
	/*m_Target = player->GetPosition();
	m_Position = m_Target + D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	m_Position += D3DXVECTOR3(cosf(m_Rotation.y),0.0f, sinf(m_Rotation.y)) * 5.0f;*/

	//if (cameraSwitch)
	//{
	//	//サードパーソンビュー(フォートナイト)
	//	m_Target = player->GetPosition() + /*player->GetRight() * 0.5f*/ + D3DXVECTOR3(0.0f, 1.3f, 0.0f);
	//	m_Position = m_Target - player->GetForward() * 5.0f + D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//}
	//else
	//{
	//	//ファーストパーソンビュー
	//	/*m_Position = player->GetPosition() + player->GetRight() *0.2f + D3DXVECTOR3(0.0f,2.2f,0.0f);
	//	m_Target = m_Position +  player->GetForward();*/

	//	
	//	
	//}

	if (Input::GetKeyPress(VK_RBUTTON))
	{
		//FPS
		m_Target = playergun->GetPosition() + playergun->GetForward() * 5.0f + D3DXVECTOR3(0.0f, 1.2f, 0.0f);
		m_Position = m_Target - playergun->GetForward();
	}
	else
	{
		//TPS
		m_Target = playergun->GetPosition() + /*player->GetRight() * 0.5f*/ +D3DXVECTOR3(0.0f, 1.3f, 0.0f);
		m_Position = m_Target - playergun->GetForward() * 5.0f + D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}
	
}

void Camera::Draw()
{
	//ビューマトリクス設定
	D3DXVECTOR3 up = D3DXVECTOR3(0.0f,1.0f, 0.0f);
	D3DXMatrixLookAtLH(&m_ViewMatrix, &m_Position, &m_Target, &up);
	//m_target 注視点

	Renderer::SetViewMatrix(&m_ViewMatrix);

	//プロジェクションマトリックス設定
	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f/*視野*/, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(&projectionMatrix);
}