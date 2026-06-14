#include "GameScene.h"

#include  <Application/Object/GameObject/Stage/Stage.h>

#include<Application/Object/GameObject/Player/Player.h>
#include<Application/Object/GameObject/Enemy/Enemy.h>

#include<Application/Object/Score/Score.h>
#include<Application/Object/Timer/Timer.h>

void GameScene::Event()
{
	if (!m_player->GetAlive())
	{
		
		return;
	}

	//　カメラ処理
	//Math::Vector3 camPos = { 0,10,-10 };

	//上からの挙動確認用
	//Math::Vector3 camPos = { 0,20,0 };

	//横からの挙動確認用
	//Math::Vector3 camPos = { 0,3,-10 };

	//斜め上から斜め下に(メイン採用)
	Math::Vector3 camPos = { -5,5,-5 };

	Math::Matrix rotationXMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(30));
	Math::Matrix rotationYMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(45));

	Math::Matrix transMat = Math::Matrix::CreateTranslation(camPos + m_player->GetPos());

	//Math::Matrix camWorld = rotationXMat * transMat ;
	Math::Matrix camWorld = rotationXMat * rotationYMat * transMat;
	m_camera->SetCameraMatrix(camWorld);
}

void GameScene::Init()
{
	//カメラ生成＆視野角設定
	m_camera = std::make_unique<KdCamera>();
	m_camera->SetProjectionMatrix(60);		

	m_stage = std::make_shared<Stage>();
	AddObject(m_stage);

	m_player = std::make_shared<Player>();
	m_player->SetPos({ 0,0,10 });
	m_player->SetAlive(true);
	m_player->SetOwner(shared_from_this());
	AddObject(m_player);

	m_score = std::make_shared<Score>();
	m_score->SetScorePos({ -550,300 });
	AddObject(m_score);

	for (int i = 0;i < 10;i++)
	{
		float x = KdRandom::GetFloat(-30, 30);
		float y = KdRandom::GetFloat(-30, 30);
		m_enemy = std::make_shared<Enemy>();
		m_enemy->SetPos({ x,0,y });
		m_enemy->SetTarget(m_player);
		m_enemy->SetScore(m_score);
		AddObject(m_enemy);
	}

	m_time = std::make_shared<Timer>();
	m_time->SetTimePos({ 450,300 });
	m_time->SetPlayer(m_player);

	m_player->SetTime(m_time);

	AddObject(m_time);


}
