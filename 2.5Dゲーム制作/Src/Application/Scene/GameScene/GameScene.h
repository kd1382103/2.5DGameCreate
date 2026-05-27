#pragma once

#include"../BaseScene/BaseScene.h"

class Background;
class Ground;

class Player;
class Enemy;

class GameScene : public BaseScene
{
public :

	GameScene()  { Init(); }
	~GameScene() {}

private:

	void Event() override;
	void Init()  override;

	//変数

	//背景類
	std::shared_ptr<Background>m_back;
	std::shared_ptr<Ground>m_ground;

	//キャラクター類
	std::shared_ptr<Player>m_player;
	std::shared_ptr<Enemy>m_enemy;
};
