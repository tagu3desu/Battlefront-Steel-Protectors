#pragma once
#include"gameobject.h"

class	HPBottom :public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};
	ID3D11ShaderResourceView* m_TextureFPS{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};
	int x=000;
	int	y=670;
	int sizeX = 350.0f;
	int sizeY = 50.0f;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	
};
