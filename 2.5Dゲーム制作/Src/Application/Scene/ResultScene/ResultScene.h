#pragma once

#include<Application/Scene/BaseScene/BaseScene.h>

class ResultBackGround;
class ResultScene : public BaseScene
{
public :

	ResultScene()  { Init(); }
	~ResultScene() {}

private :

	void Event() override;
	void Init()  override;

	std::shared_ptr<ResultBackGround>m_resultBack;
};
