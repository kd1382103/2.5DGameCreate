#include "TitleScene.h"
#include "../SceneManager.h"

//追加インクルード
#include<Application/Object/TitleObject/BackGround/TitleBackGround.h>

void TitleScene::Event()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (m_titleBgm)
		{
			m_titleBgm->Stop();
			m_titleBgm.reset();
		}
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Game);
		return;
	}

	//　カメラ処理
	Math::Vector3 camPos = { 0,0,-20 };

	Math::Matrix transMat = Math::Matrix::CreateTranslation(camPos);

	Math::Matrix camWorld = transMat;
	m_camera->SetCameraMatrix(camWorld);
}

void TitleScene::Init()
{
	BaseScene::Init();

	m_camera = std::make_unique<KdCamera>();

	m_titleBack = std::make_shared<TitleBackGround>();
	AddObject(m_titleBack);

	m_titleBgm = KdAudioManager::Instance().Play("Asset/Sounds/Bgm/Title.wav", true);
}
