#pragma once
#include"gameobject.h"
#include <list>
#include<typeinfo>
#include<vector>



class Scene
{
protected:
	std::list<GameObject*> m_GameObject[4];	//���C���[�L��STL�̃��X�g�\��
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
			 m_GameObject[i].clear();	//���X�g�\���̍폜
		 }
	 }
	 virtual void Update()
	 {
		 for (int i = 0; i < 3; i++) {
			 for (GameObject* gameObject : m_GameObject[i])
			 {
				 gameObject->Update();
			 }
			 m_GameObject[i].remove_if([](GameObject* object) {return object->Destroy(); });//�����_��
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

	 template <typename T>	//�e���v���[�g�֐�
	 T * AddGameObject(int Layer)
	 {
		 T* gameObject = new T();
		 m_GameObject[Layer].push_back(gameObject);	//���X�g�\���ɒǉ�
		 gameObject->Init();

		 return gameObject;
	 }

	 template <typename T>	//�e���v���[�g�֐�
	 T* GetGameObject()
	 {
		 for (int i=0;i<3;i++)
		 {
			 for (GameObject* object : m_GameObject[i])
			 {
				 if (typeid(*object) == typeid(T))//�^�𒲂ׂ�(RTTI���I�^���)typeid�@�^�𒲂ׂ��� ���s���x���Ȃ����肷��
				 {
					 return (T*)object;
				 }
			 }
		 }
		 return nullptr;
	 }

	 template <typename T>	//�e���v���[�g�֐�
	 std::vector<T*> GetGameObjects()
	 {
		 std::vector<T*>objects;	//STL�̔z��
		 for (int i = 0; i < 3; i++) {
			 for (GameObject* object : m_GameObject[i])
			 {
				 if (typeid(*object) == typeid(T))//�^�𒲂ׂ�(RTTI���I�^���)typeid�@�^�𒲂ׂ��� ���s���x���Ȃ����肷��
				 {
					 objects.push_back((T*)object);
				 }
			 }
		 }
		 return objects;
	 }

};