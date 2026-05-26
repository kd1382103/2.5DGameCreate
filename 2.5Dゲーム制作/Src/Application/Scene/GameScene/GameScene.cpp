#include "GameScene.h"
#include"../SceneManager.h"
#include"../../Object/Player/Player.h"

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
	Math::Vector3 camPos = { 0,1,-5 };
	Math::Matrix transMat = Math::Matrix::CreateTranslation(camPos + m_player->GetPos());
	m_camera->SetCameraMatrix(transMat);

}

void GameScene::Init()
{
	//カメラ生成＆視野角設定
	m_camera = std::make_unique<KdCamera>();		//メモリ確保
	m_camera->SetProjectionMatrix(60);				//視野角設定

	m_player = std::make_shared<Player>();
	m_objList.push_back(m_player);

}
