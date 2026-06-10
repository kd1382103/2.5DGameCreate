#include "Score.h"

void Score::Init()
{
	m_tex = std::make_shared<KdTexture>();
	m_tex->Load("Asset/Textures/Object/Score/numbers.png");

	m_scorePos = {-550,300};
	m_score = 0;
}

void Score::Update()
{
	if (m_score > 999999)
	{
		m_score = 999999;
	}

	//配列に各桁の数値を格納
	unsigned long tmp = m_score;
	for (int i = maxDigits - 1;i >= 0;--i)
	{
		//下位の桁から抽出し配列に格納
		m_digits[i] = tmp % 10;	//余りを求める演算子 %
		tmp /= 10;	//次のけたへ

	}
}

void Score::DrawSprite()
{
	//スコア表示
	for (int i = 0;i < maxDigits;++i)
	{
		Math::Rectangle rc = { 7 * m_digits[i],0,7,10 };
	
		//表示サイズ変更
		KdShaderManager::Instance().m_spriteShader.
			DrawTex(m_tex, m_scorePos.x + (i * 50), m_scorePos.y, 50, 70, &rc);
		// テクスチャデータ,x,y,幅,高さ,矩形データ
	}
}
