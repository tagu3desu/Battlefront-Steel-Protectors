#pragma once
#include"gameobject.h"

class	CrossHear :public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};
	ID3D11ShaderResourceView* m_TextureFPS{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};
	int x, y;
	float sizeX = 100.0f;
	float sizeY = 100.0f;
	int m_Count=0;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	
};
