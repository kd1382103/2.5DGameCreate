#pragma once

#include"../BaseScene/BaseScene.h"

class ResultScene : public BaseScene
{
public :

	ResultScene()  { Init(); }
	~ResultScene() {}

private :

	void Event() override;
	void Init()  override;

	std::shared_ptr<KdSquarePolygon>m_poly;

};
