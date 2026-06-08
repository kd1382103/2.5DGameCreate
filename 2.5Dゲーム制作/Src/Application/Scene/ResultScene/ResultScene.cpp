#include "ResultScene.h"
#include "../SceneManager.h"

void ResultScene::Event()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Game
		);
	}
}

void ResultScene::Init()
{
	BaseScene::Init();

	m_poly = std::make_shared<KdSquarePolygon>();
	m_poly->SetMaterial("");


}
