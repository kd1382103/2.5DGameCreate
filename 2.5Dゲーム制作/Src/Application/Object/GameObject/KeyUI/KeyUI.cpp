#include "KeyUI.h"

void KeyUI::Init()
{
	// 画像読み込み
	m_up.offTex = std::make_shared<KdTexture>("Asset/Textures/Object/KeyUI/DefaultKey/Up.png");
	m_up.onTex = std::make_shared<KdTexture>("Asset/Textures/Object/KeyUI/PressKey/Up.png");
	m_up.pos = { 50, -250 };

	m_down.offTex = std::make_shared<KdTexture>("Asset/Textures/Object/KeyUI/DefaultKey/Down.png");
	m_down.onTex = std::make_shared<KdTexture>("Asset/Textures/Object/KeyUI/PressKey/Down.png");
	m_down.pos = { 50, -300 };

	m_left.offTex = std::make_shared<KdTexture>("Asset/Textures/Object/KeyUI/DefaultKey/Left.png");
	m_left.onTex = std::make_shared<KdTexture>("Asset/Textures/Object/KeyUI/PressKey/Left.png");
	m_left.pos = { 0, -300 };

	m_right.offTex = std::make_shared<KdTexture>("Asset/Textures/Object/KeyUI/DefaultKey/Right.png");
	m_right.onTex = std::make_shared<KdTexture>("Asset/Textures/Object/KeyUI/PressKey/Right.png");
	m_right.pos = { 100, -300 };

	m_space.offTex = std::make_shared<KdTexture>("Asset/Textures/Object/KeyUI/DefaultKey/Space.png");
	m_space.onTex = std::make_shared<KdTexture>("Asset/Textures/Object/KeyUI/PressKey/Space.png");
	m_space.pos = { -100, -300 };
}

void KeyUI::Update()
{
	m_up.	isOn = (GetAsyncKeyState(VK_UP) & 0x8000);
	m_down.	isOn = (GetAsyncKeyState(VK_DOWN) & 0x8000);
	m_left.	isOn = (GetAsyncKeyState(VK_LEFT) & 0x8000);
	m_right.isOn = (GetAsyncKeyState(VK_RIGHT) & 0x8000);
	m_space.isOn = (GetAsyncKeyState(VK_SPACE) & 0x8000);
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

	draw(m_up);
	draw(m_down);
	draw(m_left);
	draw(m_right);
	draw(m_space);
}