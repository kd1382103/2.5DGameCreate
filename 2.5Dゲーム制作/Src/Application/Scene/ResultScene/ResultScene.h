#pragma once

#include<Application/Scene/BaseScene/BaseScene.h>

class ResultBackGround;
class Score;
class Timer;
class Enemy;
class ResultScene : public BaseScene
{
public :

	ResultScene() {}
	~ResultScene() {}

	void Init()  override;

	void SetFinalScore(float score) { m_resultScore = score; }
private :

	void Event() override;

	std::shared_ptr<ResultBackGround>m_resultBack;
	std::shared_ptr<Score>m_score;
	std::shared_ptr<Enemy>m_enemy;
	std::shared_ptr<Timer>m_timer;
	
	float m_resultScore = 0.0f;
	int m_resultTimer = 0;
};
