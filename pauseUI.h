#pragma once
#include"gameobject.h"

class	PauseUI :public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};
	ID3D11ShaderResourceView* m_TextureFPS{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};
	int x=0;
	int	y=0;
	float sizeX = 800.0f;
	float sizeY = 800.0f;
	float m_AlfaColor = 0.0f;
	bool m_Pause = false;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	
};
