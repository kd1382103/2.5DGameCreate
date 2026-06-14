#pragma once
#include <Application/Object/Base/BaseObject.h>

class Score :public Base
{
public:
	Score() { Init(); }
	~Score()	override { Release(); }

	void Init()			override;
	void Update()		override;
	void DrawSprite()	override;

	void SetScore(const float score) { m_score += score; }
	float GetScore() const { return m_score; }
	void SetScorePos(const Math::Vector2 pos) { m_scorePos = pos; }

private:

	std::shared_ptr<KdTexture>	m_tex;
	Math::Vector2 m_scorePos;

	//表示桁数
	static const int maxDigits = 6;

	//各桁の数字を格納する配列
	int m_digits[maxDigits] = {};

};