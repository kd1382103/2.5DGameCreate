#pragma once

class Background :public KdGameObject
{
public:
	Background() { Init(); }
	~Background()	override { Release(); }

	void Init()			override;
	void DrawUnLit()		override;

private:

	//std::shared_ptr<KdSquarePolygon>m_polygon;
	KdSquarePolygon m_polygon;

};