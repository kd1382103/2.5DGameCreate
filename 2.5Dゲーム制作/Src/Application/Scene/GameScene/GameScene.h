#pragma once

#include<Application/Scene/BaseScene/BaseScene.h>

class Stage;

class Player;
class Enemy;

class Weapons;

class GameScene : public BaseScene
{
public :

	GameScene()  { Init(); }
	~GameScene() {}

private:

	void Event() override;
	void Init()  override;

	//変数

	//ステージ
	std::shared_ptr<Stage>m_stage;

	//キャラクター類
	std::shared_ptr<Player>m_player;
	std::shared_ptr<Enemy>m_enemy;

	//武器
	std::shared_ptr<Weapons>m_weapon;
};
