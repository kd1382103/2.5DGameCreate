#pragma once

#include<Application/Scene/BaseScene/BaseScene.h>

class Stage;
class Goal;
class Rock1;
class Rock2;
class Rock3;

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

	std::shared_ptr<KdSoundInstance> m_gameBgm;



private:

	void Event() override;
	void Init()  override;

	void SpawnEnemies();

	//ステージ類
	std::shared_ptr<Stage>m_stage;
	std::shared_ptr<Goal>m_goal;
	std::shared_ptr<Rock1>m_rock1;
	std::shared_ptr<Rock2>m_rock2;
	std::shared_ptr<Rock3>m_rock3;

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

	//岩の設置テンプレート
	
	//単体
	template <class TRock>
	void CreateRocks(float x, float y, float z);

	//複数
	template <class TRock>
	void CreateRocksEX(const std::vector<float>& xs,float y,const std::vector<float>& zs);

	float m_nextSpawnTime = 10.0f;
	float m_spawnInterval = 10.0f;

};

//単体版
template<class TRock>
inline void GameScene::CreateRocks(float x, float y, float z)
{
	auto rock = std::make_shared<TRock>();
	rock->SetPos({ x, y, z });
	rock->Init();
	AddObject(rock);
}

//複数版
template<class TRock>
inline void GameScene::CreateRocksEX(const std::vector<float>& xs, float y, const std::vector<float>& zs)
{
	int count = std::min(xs.size(), zs.size());

	for (int i = 0; i < count; i++)
	{
		auto rock = std::make_shared<TRock>();
		rock->SetPos({ xs[i], y, zs[i] });
		rock->Init();
		AddObject(rock);
	}
}
