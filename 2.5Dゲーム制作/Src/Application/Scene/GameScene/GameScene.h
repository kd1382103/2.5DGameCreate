#pragma once

#include"../BaseScene/BaseScene.h"

class Player;
class GameScene : public BaseScene
{
public :

	GameScene()  { Init(); }
	~GameScene() {}

private:

	void Event() override;
	void Init()  override;

	//変数
	std::shared_ptr<Player>m_player;

};
