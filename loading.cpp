#include "main.h"
#include "renderer.h"
#include "polygon2D.h"
#include"sprite.h"
#include"loading.h"
#include"input.h"
#include"fade.h"
void Loading::Init()
{


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");


	m_Sprite = AddComponent<Sprite>();

	m_Sprite->Init(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, "asset/texture/Load.png");
	
}

void  Loading::Uninit()
{
	

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	GameObject::Uninit();
}

void Loading::Update()
{
	GameObject::Update();
	/*if (Input::GetKeyPress(VK_RETURN))
	{
		m_AlfaColor = 1.0f;
	}*/
	m_Sprite->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f,m_AlfaColor));
}

void Loading::Draw()
{
	//���̓��C�A�E�g
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//�V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//�}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Draw();

}