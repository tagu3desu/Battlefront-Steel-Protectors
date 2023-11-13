#pragma once
#include"gameobject.h"

class EnemyGage :public GameObject
{
private:


	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};
	int m_Count{};
	

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	//HPバーの色
	float m_Red = 0.0f;
	float m_Blue = 0.0f;
	float m_Green = 1.0f;
	//HPゲージの長さ
	float m_GageX = 1.0f;
};

