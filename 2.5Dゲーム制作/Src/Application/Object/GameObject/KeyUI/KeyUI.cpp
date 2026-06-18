#include "KeyUI.h"
#include<Application/Object/GameObject/Player/Player.h>
void KeyUI::Init()
{
	// 画像読み込み
	m_up.offTex = std::make_shared<KdTexture>("Asset/Textures/Object/KeyUI/DefaultKey/Up.png");
	m_up.onTex = std::make_shared<KdTexture>("Asset/Textures/Object/KeyUI/PressKey/Up.png");
	m_up.pos = { 550, -250 };

	m_down.offTex = std::make_shared<KdTexture>("Asset/Textures/Object/KeyUI/DefaultKey/Down.png");
	m_down.onTex = std::make_shared<KdTexture>("Asset/Textures/Object/KeyUI/PressKey/Down.png");
	m_down.pos = { 550, -300 };

	m_left.offTex = std::make_shared<KdTexture>("Asset/Textures/Object/KeyUI/DefaultKey/Left.png");
	m_left.onTex = std::make_shared<KdTexture>("Asset/Textures/Object/KeyUI/PressKey/Left.png");
	m_left.pos = { 500, -300 };

	m_right.offTex = std::make_shared<KdTexture>("Asset/Textures/Object/KeyUI/DefaultKey/Right.png");
	m_right.onTex = std::make_shared<KdTexture>("Asset/Textures/Object/KeyUI/PressKey/Right.png");
	m_right.pos = { 600, -300 };

	m_space.offTex = std::make_shared<KdTexture>("Asset/Textures/Object/KeyUI/DefaultKey/Space.png");
	m_space.onTex = std::make_shared<KdTexture>("Asset/Textures/Object/KeyUI/PressKey/Space.png");
	m_space.pos = { -500, -300 };

	m_z.offTex = std::make_shared<KdTexture>("Asset/Textures/Object/KeyUI/DefaultKey/Z.png");
	m_z.onTex = std::make_shared<KdTexture>("Asset/Textures/Object/KeyUI/PressKey/Z.png");
	m_z.pos = { -350, -300 };
}

void KeyUI::Update()
{
	m_up.	isOn = (GetAsyncKeyState(VK_UP) & 0x8000);
	m_down.	isOn = (GetAsyncKeyState(VK_DOWN) & 0x8000);
	m_left.	isOn = (GetAsyncKeyState(VK_LEFT) & 0x8000);
	m_right.isOn = (GetAsyncKeyState(VK_RIGHT) & 0x8000);
	m_space.isOn = (GetAsyncKeyState(VK_SPACE) & 0x8000);

	// ★ 大技ゲージが満タンのときだけ Z を反応させる
	bool canUltimate = false;

	if (auto sp = m_player.lock())
	{
		canUltimate = (sp->GetUltimateGauge() >= sp->GetUltimateMax());
	}

	if (canUltimate)
	{
		m_z.isOn = (GetAsyncKeyState('Z') & 0x8000);
	}
	else
	{
		m_z.isOn = true; // ゲージ不足 → 押しても光らない
	}
}

void KeyUI::DrawSprite()
{
	auto& sprite = KdShaderManager::Instance().m_spriteShader;

	auto draw = [&](KeyIcon& key)
		{
			auto tex = key.isOn ? key.onTex : key.offTex;
			if (!tex) return;

			// 元テクスチャサイズ取得
			const KdTexture* raw = tex.get();
			float w = (float)raw->GetInfo().Width;
			float h = (float)raw->GetInfo().Height;

			// 拡大倍率
			float scale = 3.0f; // ここを好きな倍率に

			sprite.DrawTex(tex,
				key.pos.x, key.pos.y,
				w * scale, h * scale);
		};

	// ★★★ 大技ゲージの描画 ★★★
	KdShaderManager::Instance().ChangeBlendState(KdBlendState::Alpha);
	if (auto sp = m_player.lock())
	{
		float gauge = sp->GetUltimateGauge();
		float max = sp->GetUltimateMax();
		float rate = gauge / max;

		// 円ゲージの位置
		int cx = -350;
		int cy = -300;
		int radius = 60;

		auto& sprite = KdShaderManager::Instance().m_spriteShader;

		// 背景の円（黒）
		Math::Color bg = { 0, 0, 0, 0.5f };
		sprite.DrawCircle(cx, cy, radius, &bg, true);


		// 溜まる色（青）
		Math::Color fg = { 0, 0.5f, 1, 1 };

		// 円の上下
		int top		= cy - radius;
		int bottom	= cy + radius;

		// rate に応じてどこまで満たすか
		int height = bottom - top;
		int fillBottom = top + (int)(height * rate);

		// 下 → 上 に向かって塗る
		if (rate > 0.0f)
		{
			for (int y = top; y <= fillBottom; ++y)
			{
				float dy = (float)(y - cy);
				float inside = radius * radius - dy * dy;
				if (inside < 0) continue;

				float dx = sqrtf(inside);
				int xLeft = (int)(cx - dx);
				int xRight = (int)(cx + dx);

				int w = xRight - xLeft;

				sprite.DrawBox(xLeft + w / 2, y, w / 2, 1, &fg, true);
			}
		}

		// 枠（白い円）
		Math::Color frame = { 1,1,1,1 };
		sprite.DrawCircle(cx, cy, radius, &frame, false);
	}
	KdShaderManager::Instance().ChangeBlendState(KdBlendState::Alpha);

	draw(m_up);
	draw(m_down);
	draw(m_left);
	draw(m_right);
	draw(m_space);
	draw(m_z);

}