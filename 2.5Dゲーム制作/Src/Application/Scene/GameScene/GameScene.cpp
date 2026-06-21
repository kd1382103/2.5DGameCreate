#include "GameScene.h"
#include<Application/Scene/SceneManager.h>

#include  <Application/Object/GameObject/Stage/Stage.h>
#include  <Application/Object/GameObject/Goal/Goal.h>
#include  <Application/Object/GameObject/StageObject/Rock1/Rock1.h>
#include  <Application/Object/GameObject/StageObject/Rock2/Rock2.h>
#include  <Application/Object/GameObject/StageObject/Rock3/Rock3.h>

#include<Application/Object/GameObject/Player/Player.h>
#include<Application/Object/GameObject/Enemy/Enemy.h>

#include<Application/Object/GameObject/SpawnArea/SpawnArea.h>

#include<Application/Object/GameObject/KeyUI/KeyUI.h>

#include<Application/Object/Score/Score.h>
#include<Application/Object/Timer/Timer.h>

void GameScene::Event()
{
	//　カメラ処理
	{
		Math::Vector3 camPos = { 0,10,-10 };

		//上からの挙動確認用
		//Math::Vector3 camPos = { 0,150,0 };

		//横からの挙動確認用
		//Math::Vector3 camPos = { 0,3,-10 };

		//斜め上から斜め下に
		//Math::Vector3 camPos = { -5,5,-5 };

		Math::Matrix rotationXMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(30));
		Math::Matrix rotationYMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(45));

		Math::Matrix transMat = Math::Matrix::CreateTranslation(camPos + m_player->GetPos());

		Math::Matrix camWorld = rotationXMat * transMat;
		//Math::Matrix camWorld = rotationXMat * rotationYMat * transMat;
		m_camera->SetCameraMatrix(camWorld);
	}

	
	//敵のスポーン
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
			if (enemyCount >= 80)
				continue;

			// 敵の種類切り替え
			bool spawnNecromancer = ((now / 40) % 2) == 1;

			int count = sp->GetSpawnCount();
			for (int i = 0; i < count; i++)
			{
				m_enemy = std::make_shared<Enemy>();
				m_enemy->SetEnemyType(spawnNecromancer ? Enemy::Necromancer : Enemy::Skelton);

				//三項演算子 ? ->true なら「? の右側（左側の値）」,false なら「: の右側（右側の値）」
				//今回だとtrueならネクロマンサー、falseならスケルトンが出現

				m_enemy->Init();
				m_enemy->SetPos(sp->GetRandomPos());
				m_enemy->SetTarget(m_player);
				m_enemy->SetScore(m_score);
				AddObject(m_enemy);
			}

			// ★スポーンしたので、このスポーンエリアだけ時間リセット
			sp->ResetTimer(now, m_spawnInterval);
		}
	}

}

void GameScene::Init()
{
	BaseScene::Init();

	m_camera = std::make_shared<KdCamera>();
	m_camera->SetProjectionMatrix(60);

	//ステージ
	m_stage = std::make_shared<Stage>();
	AddObject(m_stage);

	//ゴール
	m_goal = std::make_shared<Goal>();
	AddObject(m_goal);

	//岩配置
	{
		//複数設置
		CreateRocksEX<Rock1>({ 0,100 ,190,-110,-140,-115}, 0, { 0,0,80,-70,160,55 });
		//CreateRocksEX<Rock2>({ -120,-20 }, -2, { 0,-120 });
		CreateRocksEX<Rock3>({ 20,-20,70,90,-95,-110 }, 0, { -70,-120,-110,-15,70 ,-70});

		//単体設置
		// 教材として残す
		//CreateRocks<Rock>(X, Y,Z, 岩のタイプ,スケール );
	}
	
	//プレイヤー
	m_player = std::make_shared<Player>();
	m_player->Init();
	m_player->SetPos({ 0,0,-195 });
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
		int enemyNum = 10;
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
			sp->SetCenter({ 0,0,140 });
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
	}

	//タイマー
	m_time = std::make_shared<Timer>();
	m_time->SetTimePos({ 450,300 });
	m_time->SetPlayer(m_player);

	m_player->SetTime(m_time);

	AddObject(m_time);

	//キーUI
	m_KeyUI = std::make_shared<KeyUI>();
	m_KeyUI->SetTarget(m_player);
	AddObject(m_KeyUI);

	auto bg = std::make_shared<KdModelData>();
	bg->Load("Asset/Models/Stage/backgroundPlane.gltf");

	Math::Matrix scaleMat = Math::Matrix::CreateScale(100);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(0, -10, 0);
	Math::Matrix world = scaleMat * transMat;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*bg, world);
	
	m_gameBgm = KdAudioManager::Instance().Play("Asset/Sounds/Bgm/Game.wav", true);
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
