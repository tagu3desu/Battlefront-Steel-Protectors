#pragma once
#include"gameobject.h"
#include <list>
#include<typeinfo>
#include<vector>



class Scene
{
protected:
	std::list<GameObject*> m_GameObject[4];	//レイヤー有のSTLのリスト構造
public:
	 virtual void Init() {}
	 virtual void Uninit()
	 {
		 for (int i = 0; i < 3; i++){
			 for (GameObject* gameObject : m_GameObject[i])
			 {
				 gameObject->Uninit();
				 delete gameObject;
			 }
			 m_GameObject[i].clear();	//リスト構造の削除
		 }
	 }
	 virtual void Update()
	 {
		 for (int i = 0; i < 3; i++) {
			 for (GameObject* gameObject : m_GameObject[i])
			 {
				 gameObject->Update();
			 }
			 m_GameObject[i].remove_if([](GameObject* object) {return object->Destroy(); });//ラムダ式
		 }
		

		 
	 }
	 virtual void Draw()
	 {
		 for (int i = 0; i <3 ; i++) {
			 for (GameObject* gameObject : m_GameObject[i])
			 {
				 gameObject->Draw();
			 }
		 }
		
	 }

	 template <typename T>	//テンプレート関数
	 T * AddGameObject(int Layer)
	 {
		 T* gameObject = new T();
		 m_GameObject[Layer].push_back(gameObject);	//リスト構造に追加
		 gameObject->Init();

		 return gameObject;
	 }

	 template <typename T>	//テンプレート関数
	 T* GetGameObject()
	 {
		 for (int i=0;i<3;i++)
		 {
			 for (GameObject* object : m_GameObject[i])
			 {
				 if (typeid(*object) == typeid(T))//型を調べる(RTTI動的型情報)typeid　型を調べられる 実行が遅くなったりする
				 {
					 return (T*)object;
				 }
			 }
		 }
		 return nullptr;
	 }

	 template <typename T>	//テンプレート関数
	 std::vector<T*> GetGameObjects()
	 {
		 std::vector<T*>objects;	//STLの配列
		 for (int i = 0; i < 3; i++) {
			 for (GameObject* object : m_GameObject[i])
			 {
				 if (typeid(*object) == typeid(T))//型を調べる(RTTI動的型情報)typeid　型を調べられる 実行が遅くなったりする
				 {
					 objects.push_back((T*)object);
				 }
			 }
		 }
		 return objects;
	 }

};