#include "main.h"
#include "renderer.h"
#include"playerHPGage.h"
#include"sprite.h"
#include"camera.h"
#include"scene.h"
#include"player.h"
#include"playergun.h"
#include"input.h"
#include"manager.h"
void PlayerHPGage::Init()
{
	VERTEX_3D vertex[4];

	

	//頂点バッファ設定
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/PlayerHP.png",
		NULL,
		NULL,
		&m_Texture,
		NULL);
	assert(m_Texture);

	
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");

}

void PlayerHPGage::Uninit()
{
	m_VertexBuffer->Release();
	m_Texture->Release();
	


	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	GameObject::Uninit();
}

void PlayerHPGage::Update()
{
	if (Input::GetKeyPress('R'))
	{
		sizeX -= 1.0f;
	}
	
	if (sizeX <= MaxGage * 0.2) //赤ゲージ
	{
		m_Red = 1.0f;
		m_Green = 0.0f;
		m_Blue = 0.0f;
	}
	else if (sizeX <= MaxGage*0.6)	//黄色ゲージ
	{
		m_Red = 1.0f;
		m_Green = 1.0f;
		m_Blue = 0.0f;
	}
	else if (sizeX <= MaxGage )  //緑ゲージ
	{
		m_Red = 0.0f;
		m_Green = 1.0f;
		m_Blue = 0.0f;
	}
	
	

	GameObject::Update();
}

void PlayerHPGage::Draw()
{
	//入力レイアウト
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//マトリクス設定
	Renderer::SetWorldViewProjection2D();

	//基底クラスのメソッド呼び出し
	//GameObject::Draw();
	// 
	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(m_Red, m_Green, m_Blue, 1.0f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);


	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);
	Scene* scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>();
	if (Input::GetKeyPress(VK_RBUTTON))
	{
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextureFPS);
	}
	else
	{
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);
	}
	

	//プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);




	for (int i = 0; i < 3; i++) {
		
	

		//頂点データ書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		vertex[0].Position = D3DXVECTOR3(x, y, 0.0f);	//左奥
		vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].TexCoord = D3DXVECTOR2(0.0f,0.0f);

		vertex[1].Position = D3DXVECTOR3(x + sizeX, y, 0.0f);	//右奥
		vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].TexCoord = D3DXVECTOR2(1.0f,0.0f);

		vertex[2].Position = D3DXVECTOR3(x, y+ sizeY, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].TexCoord = D3DXVECTOR2(0.0f,1.0f);

		vertex[3].Position = D3DXVECTOR3(x+ sizeX, y+ sizeY, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(1.0f,1.0f);

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);	

		//ポリゴン描画
		Renderer::GetDeviceContext()->Draw(4, 0);

	}
	
	

}