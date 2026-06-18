#include "GameScene.h"
#include<Application/Scene/SceneManager.h>

#include  <Application/Object/GameObject/Stage/Stage.h>
#include  <Application/Object/GameObject/Goal/Goal.h>

#include<Application/Object/GameObject/Player/Player.h>
#include<Application/Object/GameObject/Enemy/Enemy.h>

#include<Application/Object/GameObject/SpawnArea/SpawnArea.h>

#include<Application/Object/Score/Score.h>
#include<Application/Object/Timer/Timer.h>

void GameScene::Event()
{
	if (!m_player->GetAlive())
	{

		return;
	}

	//　カメラ処理
	{
		Math::Vector3 camPos = { 0,10,-10 };

		//上からの挙動確認用
		//Math::Vector3 camPos = { 0,20,0 };

		//横からの挙動確認用
		//Math::Vector3 camPos = { 0,3,-10 };

		//斜め上から斜め下に(メイン採用予定)
		//Math::Vector3 camPos = { -5,5,-5 };

		Math::Matrix rotationXMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(30));
		Math::Matrix rotationYMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(45));

		Math::Matrix transMat = Math::Matrix::CreateTranslation(camPos + m_player->GetPos());

		Math::Matrix camWorld = rotationXMat * transMat;
		//Math::Matrix camWorld = rotationXMat * rotationYMat * transMat;
		m_camera->SetCameraMatrix(camWorld);
	}

	//敵の追加スポーン
	//{
	//	int now = m_time->GetTime();   // Timer の秒数
	//	if (now >= m_nextSpawnTime)
	//	{

	//		// ③ 敵の最大数チェック
	//		int enemyCount = 0;
	//		for (auto& obj : SceneManager::Instance().GetObjList())
	//		{
	//			if (dynamic_cast<Enemy*>(obj.get()))
	//			{
	//				enemyCount++;
	//			}
	//		}

	//		// 上限以下ならスポーン
	//		if (enemyCount < 60)
	//		{
	//			// ② 経過時間で敵の種類を変える
	//			bool spawnNecromancer = (now >= 60);  // 60秒経過でネクロマンサー解禁

	//			for (auto& sp : m_spawnAreas)
	//			{
	//				//範囲チェック（プレイヤー）
	//				if (!sp->IsPlayerInTrigger(m_player->GetPos()))
	//				{
	//					continue; 
	//				}

	//				int count = sp->GetSpawnCount();

	//				for (int i = 0; i < count; i++)
	//				{
	//					m_enemy = std::make_shared<Enemy>();

	//					// ② 敵の種類を時間で変える
	//					if (spawnNecromancer)
	//					{
	//						m_enemy->SetEnemyType(Enemy::Necromancer);
	//					}
	//					else
	//					{
	//						m_enemy->SetEnemyType(Enemy::Skelton);
	//					}

	//					m_enemy->Init();
	//					m_enemy->SetPos(sp->GetRandomPos());
	//					m_enemy->SetTarget(m_player);
	//					m_enemy->SetScore(m_score);
	//					AddObject(m_enemy);
	//				}
	//			}
	//		}

	//		// 次のスポーン時間を更新
	//		m_nextSpawnTime += m_spawnInterval;
	//	}
	//}

	{
		int now = m_time->GetTime();   // Timer の秒数
		for (auto& sp : m_spawnAreas)
		{
			// まずタイマー更新
			sp->UpdateTimer(now, m_spawnInterval);

			// フラグが有効でなければスキップ
			if (!sp->CanSpawn())
				continue;

			// プレイヤーが範囲内にいなければスキップ
			if (!sp->IsPlayerInTrigger(m_player->GetPos()))
				continue;

			// 敵数チェック
			int enemyCount = 0;
			for (auto& obj : SceneManager::Instance().GetObjList())
			{
				if (dynamic_cast<Enemy*>(obj.get()))
					enemyCount++;
			}
			if (enemyCount >= 60)
				continue;

			// 敵の種類切り替え
			bool spawnNecromancer = (now >= 60);

			int count = sp->GetSpawnCount();
			for (int i = 0; i < count; i++)
			{
				auto enemy = std::make_shared<Enemy>();
				enemy->SetEnemyType(spawnNecromancer ? Enemy::Necromancer : Enemy::Skelton);
				enemy->Init();
				enemy->SetPos(sp->GetRandomPos());
				enemy->SetTarget(m_player);
				enemy->SetScore(m_score);
				AddObject(enemy);
			}

			// ★スポーンしたので、このスポーンエリアだけ時間リセット
			sp->ResetTimer(now, m_spawnInterval);
		}
	}
}

void GameScene::Init()
{
	m_camera = std::make_unique<KdCamera>();
	m_camera->SetProjectionMatrix(60);

	//ステージ
	m_stage = std::make_shared<Stage>();
	AddObject(m_stage);
	
	//ゴール
	m_goal = std::make_shared<Goal>();
	AddObject(m_goal);

	//プレイヤー
	m_player = std::make_shared<Player>();
	m_player->SetPos({ 0,0,-200 });
	m_player->SetAlive(true);
	m_player->SetOwner(shared_from_this());
	m_player->SetCamera(m_camera);
	AddObject(m_player);

	//スコア
	m_score = std::make_shared<Score>();
	m_score->SetScorePos({ -550,300 });
	AddObject(m_score);

	//敵の出現場所配置
	{
		int enemyNum = 8;
		{
			auto sp = std::make_shared<SpawnArea>();
			sp->SetCenter({ 0,0,-150 });
			sp->SetRadius(3.0f);
			sp->SetSpawnCount(enemyNum);
			AddObject(sp);
			m_spawnAreas.push_back(sp);
		}
		{
			auto sp = std::make_shared<SpawnArea>();
			sp->SetCenter({ -100,0,-75 });
			sp->SetRadius(4.0f);
			sp->SetSpawnCount(enemyNum);
			AddObject(sp);
			m_spawnAreas.push_back(sp);
		}
		{
			auto sp = std::make_shared<SpawnArea>();
			sp->SetCenter({ 100,0,-20 });
			sp->SetRadius(2.5f);
			sp->SetSpawnCount(enemyNum);
			AddObject(sp);
			m_spawnAreas.push_back(sp);
		}
		{
			auto sp = std::make_shared<SpawnArea>();
			sp->SetCenter({ 190,0,50 });
			sp->SetRadius(2.5f);
			sp->SetSpawnCount(enemyNum);
			AddObject(sp);
			m_spawnAreas.push_back(sp);
		}

		SpawnEnemies();
	}

	//タイマー
	m_time = std::make_shared<Timer>();
	m_time->SetTimePos({ 450,300 });
	m_time->SetPlayer(m_player);

	m_player->SetTime(m_time);

	AddObject(m_time);
}

void GameScene::SpawnEnemies()
{
	for (auto& sp : m_spawnAreas)
	{
		//int count = KdRandom::GetInt(sp->GetMinSpawn(), sp->GetMaxSpawn());
		int count = sp->GetSpawnCount();

		for (int i = 0; i < count; i++)
		{
			m_enemy= std::make_shared<Enemy>();
			m_enemy->Init();
			m_enemy->SetPos(sp->GetRandomPos());
			m_enemy->SetTarget(m_player);
			m_enemy->SetScore(m_score);
			AddObject(m_enemy);
		}
	}
}
