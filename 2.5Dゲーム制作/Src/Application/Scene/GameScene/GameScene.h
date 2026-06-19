#pragma once

#include<Application/Scene/BaseScene/BaseScene.h>

class Stage;
class Goal;
class Fog;

class Player;
class Enemy;

class Score;
class Timer;

class SpawnArea;

class KeyUI;

class GameScene : public BaseScene ,public std::enable_shared_from_this<GameScene>
{
public :

	GameScene()  {}
	~GameScene() {}

	std::shared_ptr<Score> GetScore() { return m_score; }
	std::shared_ptr<Timer> GetTimer() { return m_time; }

private:

	void Event() override;
	void Init()  override;

	void SpawnEnemies();

	//ステージ類
	std::shared_ptr<Stage>m_stage;
	std::shared_ptr<Goal>m_goal;
	std::shared_ptr<Fog>m_fog;

	//キャラクター類
	std::shared_ptr<Player>m_player;
	std::shared_ptr<Enemy>m_enemy;

	//敵の出現場所
	std::vector<std::shared_ptr<SpawnArea>> m_spawnAreas;
	
	//スコア
	std::shared_ptr<Score>m_score;

	//タイマー
	std::shared_ptr<Timer>m_time;

	//キーUI
	std::shared_ptr<KeyUI>m_KeyUI;

	float m_nextSpawnTime = 15.0f;
	float m_spawnInterval = 15.0f;
};
