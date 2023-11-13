#pragma once
#include <list>
#include"compornent.h"
class GameObject
{
protected:
	bool m_Destroy = false;

	D3DXVECTOR3 m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 m_MoveSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	std::list<Component*> m_Component;	//STLのリスト構造
public:
	void SetDestroy() { m_Destroy = true; }
	void SetPosition(D3DXVECTOR3 Position) { m_Position = Position; }
	void SetRotation(D3DXVECTOR3 Rotation) { m_Rotation = Rotation; }
	void SetScale(D3DXVECTOR3 Scale) { m_Scale = Scale; };
	void SetScalePosition(D3DXVECTOR3  Scale, D3DXVECTOR3 Position) { m_Scale = Scale; m_Position = Position;}


	bool Destroy()
	{
		if (m_Destroy)
		{
			Uninit();
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	}
			
		
		
	D3DXVECTOR3 GetPosition()
	{
		return   m_Position;
	}

	D3DXVECTOR3 GetScale()
	{
		return m_Scale;
	}

	D3DXVECTOR3 GetForward() //前方面ベクトルを取得
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DXVECTOR3 forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		return forward;
	}

	D3DXVECTOR3 GetRight() //前方面ベクトルを取得
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DXVECTOR3 right;
		right.x = rot._11;
		right.y = rot._12;
		right.z = rot._13;

		return right;
	}


	virtual void Init() {};
	virtual void Uninit() 
	{
		for (Component* component : m_Component)
		{
			component->Uninit();
			delete component;
		}
		m_Component.clear();
	};
	virtual void Update() 
	{
		for (Component* component : m_Component)
		{
			component->Update();
		}
	};
	virtual void Draw() 
	{
		for (Component* component : m_Component)
		{
			component->Draw();
		}
	};

	template <typename T>	//テンプレート関数
	T* AddComponent()
	{
		Component* component = new T();
		m_Component.push_back(component);	//リスト構造に追加
		component->Init();

		return (T*)component;
	}
};

