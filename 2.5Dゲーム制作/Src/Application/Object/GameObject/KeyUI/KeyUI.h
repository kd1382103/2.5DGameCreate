#pragma once
#include <Application/Object/Base/BaseObject.h>

class Player;
class KeyUI : public Base
{
public:

	KeyUI() { Init(); }
	~KeyUI() override { Release(); }
	void Init()			override;
	void Update()		override;
	void DrawSprite()	override;

	void SetTarget(const std::shared_ptr<KdGameObject> target) override
	{
		m_target = target;

		if (auto spPlayer = std::dynamic_pointer_cast<Player>(target))
		{
			m_player = spPlayer;
		}
	}
private:

	std::weak_ptr<Player> m_player;

	struct KeyIcon {
		std::shared_ptr<KdTexture> offTex;
		std::shared_ptr<KdTexture> onTex;
		bool isOn = false;
		Math::Vector2 pos;
	};

	std::shared_ptr<KdShaderManager>m_shader;
	KeyIcon m_up;
	KeyIcon m_down;
	KeyIcon m_left;
	KeyIcon m_right;
	KeyIcon m_space;
	KeyIcon m_z;

};