#pragma once

#include"model.h"
#include"gameobject.h"


class Player :public GameObject
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
	class Audio* m_StayEnginBGM{};
	class Audio* m_EnginBGM{};

	class Shadow* m_Shadow{};
	

	bool EnginFlag = false;
	bool EnginBGMFlag = false;

	D3DXVECTOR3 m_PlayerOldPos;
	D3DXVECTOR3 m_PlayerNewPos;

	bool MoveFlag = false;

	int new_mouseX;
	int old_mouseX;

	
	
public:


	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool m_Dead = false;
	int m_KillCount = 0;
};

