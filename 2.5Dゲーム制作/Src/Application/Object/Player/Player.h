#pragma once
#include"../../../Framework/GameObject/KdGameObject.h"

class GameScene;
class Player : public KdGameObject
{
public:
	Player() {}
	~Player() { Release(); }

	void Update();

	void Draw();

private:

	void Release() {}
	void Init() override;

	GameScene* m_owner = nullptr;

	//単位行列で初期化
	Math::Matrix m_player=Math::Matrix::Identity;

};