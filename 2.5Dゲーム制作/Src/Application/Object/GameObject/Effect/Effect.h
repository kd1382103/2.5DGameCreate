#pragma once
#include<Application/Object/Base/BaseObject.h>

class Effect :public Base
{
public:
	Effect() {}
	~Effect() override { Release(); }

	void Init()		override;
	void Update()		override;
	void DrawEffect()		override;

	void SetPos(const Math::Vector3& _pos) override { m_nowPos = _pos; }

	// カメラを受け取る（3D→2D変換に必要）
	void SetCamera(const std::weak_ptr<KdCamera>& cam) { m_wpCamera = cam; }

private:

	struct Particle
	{
		Math::Vector3 pos;
		Math::Vector3 vel;
		float life = 0.0f;
		float maxLife = 0.0f;
	};

	std::vector<Particle>m_particle;
	std::weak_ptr<KdCamera> m_wpCamera;

};