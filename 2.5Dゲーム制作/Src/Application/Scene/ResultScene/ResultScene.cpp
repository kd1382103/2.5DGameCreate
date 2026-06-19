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

	//BGM（ループ）
	//KdAudioManager::Instance().Play("", true);


}

void ResultScene::Init()
{
	BaseScene::Init();

	m_camera = std::make_unique<KdCamera>();

	m_resultBack = std::make_shared<ResultBackGround>();
	AddObject(m_resultBack);

	//ゲーム結果取得
	float baseScore = SceneManager::Instance().m_finalScore;
	float finalTime = SceneManager::Instance().m_finalTime;

	// ★ クリアタイムボーナスの計算
	// （１分ごとにボーナスが減少し、その時間のところのボーナス値を加算）

	float timeBonus = 0.0f;

	if (finalTime < 60) {
		timeBonus = 5000;
	}
	else if (finalTime < 120) {
		timeBonus = 3000;
	}
	else if (finalTime < 180) {
		timeBonus = 1000;
	}
	// 最終スコア決定 
	m_resultScore = baseScore + timeBonus;

	m_score = std::make_shared<Score>();
	m_score->SetScorePos({ -150,-100 });
	m_score->SetScore(m_resultScore);
	AddObject(m_score);

	m_timer = std::make_shared<Timer>();
	m_timer->SetTimePos({ -150,100 });
	m_resultTimer = SceneManager::Instance().m_finalTime;
	m_timer->SetTimer(m_resultTimer);
	AddObject(m_timer);
}
