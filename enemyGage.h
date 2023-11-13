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

	//HP�o�[�̐F
	float m_Red = 0.0f;
	float m_Blue = 0.0f;
	float m_Green = 1.0f;
	//HP�Q�[�W�̒���
	float m_GageX = 1.0f;
};

