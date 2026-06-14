#pragma once

#include<Application/Scene/BaseScene/BaseScene.h>

class Stage;

class Player;
class Enemy;

class Score;
class Timer;

class GameScene : public BaseScene,public std::enable_shared_from_this<GameScene>
{
public :

	GameScene()  {}
	~GameScene() {}

	std::shared_ptr<Score> GetScore() { return m_score; }
	std::shared_ptr<Timer> GetTimer() { return m_time; }

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

	//タイマー
	std::shared_ptr<Timer>m_time;
};
