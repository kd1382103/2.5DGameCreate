#include "SpawnArea.h"

void SpawnArea::Init()
{
	Base::Init();

	// デバッグ描画用
	m_debug = std::make_unique<KdDebugWireFrame>();
}

void SpawnArea::DrawUnLit()
{
	// スポーン範囲を可視化（円形）
	if (m_debug)
	{
		m_debug->AddDebugSphere(m_center, m_radius, { 1,1,0,1 });
	}
}