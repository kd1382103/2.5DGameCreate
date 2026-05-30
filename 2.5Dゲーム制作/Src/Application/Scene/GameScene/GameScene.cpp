#include "GameScene.h"
#include"../SceneManager.h"

#include "../../Object/Stage/Stage.h"

#include"../../Object/Player/Player.h"
#include"../../Object/Enemy/Enemy.h"


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
	Math::Vector3 camPos = { 0,3,-5 };
	Math::Matrix rotationMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(20));

	Math::Matrix transMat = Math::Matrix::CreateTranslation( camPos + m_player->GetPos());

	Math::Matrix camWorld = rotationMat * transMat;
	m_camera->SetCameraMatrix(camWorld);

}

void GameScene::Init()
{
	//カメラ生成＆視野角設定
	m_camera = std::make_unique<KdCamera>();		//メモリ確保
	m_camera->SetProjectionMatrix(60);				//視野角設定

	m_stage = std::make_shared<Stage>();
	m_objList.push_back(m_stage);

	m_player = std::make_shared<Player>();
	m_objList.push_back(m_player);

	m_enemy = std::make_shared<Enemy>();
	m_objList.push_back(m_enemy);
}
