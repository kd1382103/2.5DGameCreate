#include "ResultScene.h"
#include <Application/Scene/SceneManager.h>

//追加インクルード
#include<Application/Object/ResultObject/Backgraound/ResultBackGround.h>
#include<Application/Object/Score/Score.h>
#include<Application/Object/Timer/Timer.h>

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
	m_score->SetScorePos({ -150,-100 });
	m_resultScore = SceneManager::Instance().m_finalScore;
	m_score->SetScore(m_resultScore);
	AddObject(m_score);

	m_timer = std::make_shared<Timer>();
	m_timer->SetTimePos({ -150,100 });
	m_resultTimer = SceneManager::Instance().m_finalTime;
	m_timer->SetTimer(m_resultTimer);
	AddObject(m_timer);
}
