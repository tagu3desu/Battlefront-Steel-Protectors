#pragma once
#include"model.h"
#include"gameobject.h"

class Enemy : public GameObject
{
private:
	static Model* m_Model;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	class Audio* m_EnemyShotSE{};
	float m_bulletRate = 0.0f;

	float ShotRange = 0.0f;
	bool PlayerShot = false;

	class EnemyGage* m_EnemyGage{};
	class EnemyBullet* m_EnemyBullet{};
	
public:
	static void Load();
	static void Unload();
	float m_EnemyHP=4.0f;

	void Init();
	void Uninit();
	void Update();
	void Draw();
};