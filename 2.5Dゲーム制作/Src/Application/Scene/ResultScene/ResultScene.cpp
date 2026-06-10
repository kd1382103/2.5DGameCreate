#include "ResultScene.h"
#include <Application/Scene/SceneManager.h>

//追加インクルード
#include<Application/Object/ResultObject/Backgraound/ResultBackGround.h>
#include<Application/Object/Score/Score.h>

void ResultScene::Event()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Title);
	}

	//　カメラ処理
	Math::Vector3 camPos = { 0,0,-20 };

	Math::Matrix transMat = Math::Matrix::CreateTranslation(camPos);

	Math::Matrix camWorld = transMat ;
	m_camera->SetCameraMatrix(camWorld);

}

void ResultScene::Init()
{
	BaseScene::Init();

	m_camera = std::make_unique<KdCamera>();

	m_resultBack = std::make_shared<ResultBackGround>();
	AddObject(m_resultBack);

	m_score = std::make_shared<Score>();
	AddObject(m_score);

}
