#include "main.h"
#include "renderer.h"
#include "polygon2D.h"
#include"sprite.h"
#include"titleLogo.h"
#include"audio.h"
#include"input.h"
void TitleLogo::Init()
{


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");


	AddComponent<Sprite>()->Init(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, "asset/texture/Title.png");
	
	m_TitleBGM = AddComponent<Audio>();
	m_TitleBGM->Load("asset\\audio\\Alone.wav");
	m_TitleBGM->Play();
	
	m_DesideSE = AddComponent<Audio>();
	m_DesideSE->Load("asset\\audio\\決定ボタンを押す21.wav");

}

void TitleLogo::Uninit()
{


	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
	GameObject::Uninit();
}

void TitleLogo::Update()
{
	if(Input::GetKeyTrigger(VK_RETURN))
	{
		m_DesideSE->Play();
	}
			
	
	GameObject::Update();
}

void TitleLogo::Draw()
{
	//入力レイアウト
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//マトリクス設定
	Renderer::SetWorldViewProjection2D();

	//基底クラスのメソッド呼び出し
	GameObject::Draw();

}