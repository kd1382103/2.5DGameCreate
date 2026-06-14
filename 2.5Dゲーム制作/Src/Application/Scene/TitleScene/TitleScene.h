#pragma once

#include<Application/Scene/BaseScene/BaseScene.h>

class TitleBackGround;
class TitleScene : public BaseScene
{
public :

	TitleScene()  {}
	~TitleScene() {}

private :

	void Event() override;
	void Init()  override;

	std::shared_ptr<TitleBackGround>m_titleBack;
};
