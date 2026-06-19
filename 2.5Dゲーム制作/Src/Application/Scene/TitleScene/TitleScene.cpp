#include "TitleScene.h"
#include "../SceneManager.h"

//追加インクルード
#include<Application/Object/TitleObject/BackGround/TitleBackGround.h>

void TitleScene::Event()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Game
		);
	}

	//　カメラ処理
	Math::Vector3 camPos = { 0,0,-20 };

	Math::Matrix transMat = Math::Matrix::CreateTranslation(camPos);

	Math::Matrix camWorld = transMat;
	m_camera->SetCameraMatrix(camWorld);

	//BGM（ループ）
	//KdAudioManager::Instance().Play("", true);

}

void TitleScene::Init()
{
	BaseScene::Init();

	m_camera = std::make_unique<KdCamera>();

	m_titleBack = std::make_shared<TitleBackGround>();
	AddObject(m_titleBack);
}
