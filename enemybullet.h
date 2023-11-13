#pragma once
#include"gameobject.h"
#include"model.h"
class EnemyBullet :public GameObject
{
private:
	static Model* m_Model;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	D3DXVECTOR3 m_Velocity{};
	class Shadow*  m_Shadow{};
	
public:
	static void Load();
	static void Unload();

	void SetVerocity(D3DXVECTOR3 forward)
	{
		m_Velocity = forward;
	}

	void Init();
	void Uninit();
	void Update();
	void Draw();
};