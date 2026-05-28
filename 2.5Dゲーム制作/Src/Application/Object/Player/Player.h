#pragma once

class GameScene;
class Player : public KdGameObject
{
public:
	Player() { Init(); }
	~Player() { Release(); }

	void Init()							override;
	void Update()						override;
	void PostUpdate()					override;
	void GenerateDepthMapFromLight()	override;
	void DrawLit()						override;

private:

	void Release() {}

	GameScene* m_owner = nullptr;

	std::shared_ptr<KdSquarePolygon>m_poly;

	float m_anime = 0;
};