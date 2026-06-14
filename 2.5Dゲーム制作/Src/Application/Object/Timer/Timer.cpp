#include "Timer.h"

//追加インクルード
#include <Application/Object/GameObject/Player/Player.h>

void Timer::Init()
{
	m_fontTex = std::make_shared<KdTexture>();
	m_fontTex->Load("Asset/Textures/Object/Number/Number.png");	

	m_timerPos = {};
	m_time = 0;

}

void Timer::Update()
{
	if (!m_player)return;

	if (m_player && m_player->GetAlive())
	{
		m_frame++;
		m_time = m_frame / 60; // 秒単位に変換
	}

	int minutes = m_time / 60;
	int seconds = m_time % 60;

	m_digits[0] = minutes / 10;     // 分の十の位
	m_digits[1] = minutes % 10;     // 分の一の位
	m_digits[2] = 10;               // コロン（numbers.png の11番目をコロンにする）
	m_digits[3] = seconds / 10;     // 秒の十の位
	m_digits[4] = seconds % 10;     // 秒の一の位
}

void Timer::DrawSprite()
{
	const int digitW = 40;
	const int digitH = 60;

	const int drawW = 40;
	const int drawH = 60;

	Math::Vector2 pos = m_timerPos;

	for (int i = 0; i < 5; ++i)
	{
		Math::Rectangle rc = { digitW * m_digits[i], 0, digitW, digitH };
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_fontTex, pos.x,pos.y, drawW, drawH, &rc);
		pos.x += drawW;
	}
}
