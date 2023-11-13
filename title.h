#pragma once
#include"scene.h"
#include"polygon2D.h"
#include"sprite.h"
class Title:public Scene
{
private:
	class Fade* m_Fade{};
	

	class TitleButton* m_TitleButton{};
	class Loading* m_Loading{};

public:
	void Init() override;
	void Update() override;
};