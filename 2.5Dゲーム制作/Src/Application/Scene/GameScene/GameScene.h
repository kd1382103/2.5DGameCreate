#pragma once

#include"../BaseScene/BaseScene.h"

class Stage;

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
	std::shared_ptr<Stage>m_stage;

	//キャラクター類
	std::shared_ptr<Player>m_player;
	std::shared_ptr<Enemy>m_enemy;
};
