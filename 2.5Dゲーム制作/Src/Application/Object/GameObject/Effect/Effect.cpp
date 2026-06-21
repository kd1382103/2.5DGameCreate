#include"Effect.h"

void Effect::Init()
{
	m_particle.clear();
	const int particleCount = 20;
	for (int i = 0;i < particleCount;++i)
	{
		Particle p;
		// 発生位置
		p.pos = m_nowPos;

		// ランダム方向に飛ばす
		p.vel.x = (float(rand() % 200) / 100.0f - 1.0f) * 2.0f;
		p.vel.y = (float(rand() % 200) / 100.0f) * 3.0f; // 上方向を強め
		p.vel.z = (float(rand() % 200) / 100.0f - 1.0f) * 2.0f;

		// 寿命
		p.maxLife = p.life = (float(rand() % 30) / 100.0f) + 0.3f;

		m_particle.push_back(p);
	}
}

void Effect::Update()
{
	const float gravity = -9.8f * 0.2f;
	const float delta = 1.0f / 60.0f;

	for (auto& p : m_particle)
	{
		p.life -= delta;
		if (p.life <= 0) continue;

		// 重力
		p.vel.y += gravity * delta;

		// 移動
		p.pos += p.vel * delta;
	}

	// 全部死んだらエフェクト自体を消す
	bool allDead = true;
	for (auto& p : m_particle)
	{
		if (p.life > 0) { allDead = false; break; }
	}
	if (allDead) m_isExpired = true;
}

void Effect::DrawEffect()
{
	auto spCamera = m_wpCamera.lock();
	if (!spCamera) return;

	auto& sprite = KdShaderManager::Instance().m_spriteShader;


	for (auto& p : m_particle)
	{
		if (p.life <= 0) continue;

		float alpha = p.life / p.maxLife;

		// 3D → 2D変換
		Math::Vector3 screenPos;
		spCamera->ConvertWorldToScreenDetail(p.pos, screenPos);

		Math::Color col = { 0.8f, 0.0f, 0.0f, alpha };

		// extentX, extentY は半径
		sprite.DrawBox(
			(int)screenPos.x,
			(int)screenPos.y,
			3, 3,
			&col,
			true
		);
	}
}

