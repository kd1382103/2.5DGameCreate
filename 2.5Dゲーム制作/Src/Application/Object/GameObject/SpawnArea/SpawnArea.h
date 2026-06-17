#pragma once
#include<Application/Object/Base/BaseObject.h>

class SpawnArea:public Base
{
public:
	SpawnArea() { Init(); }
	~SpawnArea() override { Release(); }


	void Init() override;
	void DrawUnLit() override;

	// スポーン地点の中心位置
	void SetCenter(const Math::Vector3& pos) { m_center = pos; }
	const Math::Vector3& GetCenter() const { return m_center; }

	// スポーン範囲（半径 or 矩形サイズ）
	void SetRadius(float r) { m_radius = r; }
	float GetRadius() const { return m_radius; }

	// ★ プレイヤーが近づいたらスポーンする範囲（トリガー）
	void SetTriggerRadius(float r) { m_triggerRadius = r; }
	float GetTriggerRadius() const { return m_triggerRadius; }

	// ★ トリガー範囲チェック（スポーン判定用）
	bool IsPlayerInTrigger(const Math::Vector3& playerPos) const
	{
		float dist = (playerPos - m_center).Length();
		return dist <= m_triggerRadius;
	}

	/////////////////////////////////////////////////////////

	//出現数ランダムの場合

	//// このエリアから出す敵の数
	//void SetSpawnCount(int min, int max)
	//{
	//	m_minSpawn = min;
	//	m_maxSpawn = max;
	//}

	//int GetMinSpawn() const { return m_minSpawn; }
	//int GetMaxSpawn() const { return m_maxSpawn; }


	/////////////////////////////////////////////////////////
	
	// ★固定数の敵を出す
	void SetSpawnCount(int count) { m_spawnCount = count; }
	int GetSpawnCount() const { return m_spawnCount; }

	// ランダムなスポーン位置を取得
	Math::Vector3 GetRandomPos() const 
	{
		float rx = KdRandom::GetFloat(-m_radius, m_radius);
		float rz = KdRandom::GetFloat(-m_radius, m_radius);

		return { m_center.x + rx, m_center.y, m_center.z + rz };
	};

private:
	void Release() {}

	Math::Vector3 m_center = { 0,0,0 }; // スポーン中心
	float m_radius = 3.0f;              // スポーン範囲（円形）

	float m_triggerRadius = 10.0f;  // ★ プレイヤーが近づいたら湧く範囲（自由に設定可能）

	//int m_minSpawn = 8;                 // 最低出現数
	//int m_maxSpawn = 10;                // 最大出現数

	int m_spawnCount = 0;

	std::unique_ptr<KdDebugWireFrame>m_debug;
};