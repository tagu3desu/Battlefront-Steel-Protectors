#pragma once
#include"gameobject.h"

class	BulletNumber :public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};
	int count = 0;

	int m_BulletCount=5;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void AddNumber(int Count) { m_BulletCount += Count;}
	void SubtractNumber(int MainasuCount) { m_BulletCount -= MainasuCount;}
	void SetCount(int Count) {  m_BulletCount = Count;}
	int GetCount() { return count;}
};
