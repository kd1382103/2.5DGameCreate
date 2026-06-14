#pragma once
#include<Application/Object/Base/BaseObject.h>

class Player;
class Timer :public Base
{
public:
	Timer() { Init(); }
	~Timer()override { Release(); }

	void Init()			override;
	void Update()		override;
	void DrawSprite()	override;

	void SetTimer(const int time) 
	{ 
		m_time = time;
		m_frame = time * 60;
	}
	void SetTimePos(const Math::Vector2 pos) { m_timerPos = pos; }
	void SetPlayer(const std::shared_ptr<Player>& player) { m_player = player; }

	int GetTime() const { return m_time; }

private:

	std::shared_ptr<KdTexture>m_fontTex;
	std::shared_ptr<Player>m_player;

	Math::Vector2 m_timerPos;

	//表示桁数
	static const int maxDigits = 5;

	//各桁の数字を格納する配列
	int m_digits[maxDigits] = {};
	float m_frame = 0.0f;
	int m_time;
};