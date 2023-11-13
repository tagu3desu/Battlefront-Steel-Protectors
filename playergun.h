#pragma once

#include"model.h"
#include"gameobject.h"


class PlayerGun :public GameObject
{
private:

	

	Model* m_Model{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	float m_MoveSpeed;
	D3DXVECTOR3  moveSpeed;
	float speed =0.0f;

	D3DXVECTOR3 m_Velocity{};

	class Audio* m_ShotSE{};
	class Audio* m_EnginSE{};
	class Audio* m_EnginBGM{};
	class Audio* m_ReloadSE{};

	class Shadow* m_Shadow{};

	bool EnginFlag = false;
	bool EnginBGMFlag = false;

	D3DXVECTOR3 m_PlayerOldPos;
	D3DXVECTOR3 m_PlayerNewPos;

	bool MoveFlag = false;
	int bulletCount=5;

	int m_Framecount=0;
	bool m_FireFlag = false;

public:


	void Init();
	void Uninit();
	void Update();
	void Draw();
};

