#pragma once

#include<Application/Scene/BaseScene/BaseScene.h>

class Stage;

class Player;
class Enemy;


class Score;

class GameScene : public BaseScene
{
public :

	GameScene()  { Init(); }
	~GameScene() {}

private:

	void Event() override;
	void Init()  override;

	//ステージ
	std::shared_ptr<Stage>m_stage;

	//キャラクター類
	std::shared_ptr<Player>m_player;
	std::shared_ptr<Enemy>m_enemy;


	//スコア
	std::shared_ptr<Score>m_score;
};
