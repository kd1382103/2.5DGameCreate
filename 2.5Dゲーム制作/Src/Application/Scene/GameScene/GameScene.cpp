#include "GameScene.h"
#include<Application/Scene/SceneManager.h>

#include <Application/Object/Stage/Stage.h>

#include<Application/Object/Player/Player.h>
#include<Application/Object/Enemy/Enemy.h>

void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Result
		);
	}

	//　カメラ処理
	//Math::Vector3 camPos = { 0,10,-10 };

	//上からの挙動確認用
	//Math::Vector3 camPos = { 0,20,0 };

	//横からの挙動確認用
	Math::Vector3 camPos = { 0,3,-10 };

	Math::Matrix rotationMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0));

	Math::Matrix transMat = Math::Matrix::CreateTranslation(camPos + m_player->GetPos());

	Math::Matrix camWorld = rotationMat * transMat ;
	m_camera->SetCameraMatrix(camWorld);

	
}

void GameScene::Init()
{
	//カメラ生成＆視野角設定
	m_camera = std::make_unique<KdCamera>();		//メモリ確保
	m_camera->SetProjectionMatrix(60);				//視野角設定

	m_stage = std::make_shared<Stage>();
	AddObject(m_stage);

	m_player = std::make_shared<Player>();
	m_player->SetPos({ 0,0,10 });
	m_player->mp_enemy = m_enemy;
	AddObject(m_player);

	for (int i = 0;i < 10;i++)
	{
		float x = KdRandom::GetFloat(-30, 30);
		float y = KdRandom::GetFloat(-30, 30);
		m_enemy = std::make_shared<Enemy>();
		m_enemy->SetPos({x,0,y});
		m_enemy->mp_player = m_player;
		AddObject(m_enemy);
	}

}
