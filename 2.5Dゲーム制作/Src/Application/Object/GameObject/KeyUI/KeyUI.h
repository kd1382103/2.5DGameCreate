#pragma once
#include <Application/Object/Base/BaseObject.h>

class KeyUI : public Base
{
public:

	KeyUI() { Init(); }
	~KeyUI() override { Release(); }
	void Init()			override;
	void Update()		override;
	void DrawSprite()	override;

private:
	struct KeyIcon {
		std::shared_ptr<KdTexture> offTex;
		std::shared_ptr<KdTexture> onTex;
		bool isOn = false;
		Math::Vector2 pos;
	};

	KeyIcon m_up;
	KeyIcon m_down;
	KeyIcon m_left;
	KeyIcon m_right;
	KeyIcon m_space;

};