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
	static const int DIGIT_W = 10;   // 元画像の1桁幅
	static const int DIGIT_H = 20;   // 元画像の1桁高さ
	static const int DRAW_W = 40;   // 描画時の幅
	static const int DRAW_H = 50;   // 描画時の高さ
	static const int DIGIT_SPACING = 40; // 桁間の距離

	//スコア表示
	for (int i = 0;i < maxDigits;++i)
	{
		Math::Rectangle rc = { DIGIT_W * m_digits[i],0,DIGIT_W,DIGIT_H };
	
		//表示サイズ変更
		KdShaderManager::Instance().m_spriteShader.
			DrawTex(m_tex, m_scorePos.x + (i * DIGIT_SPACING), m_scorePos.y, DRAW_W, DRAW_H, &rc);
		// テクスチャデータ,x,y,幅,高さ,矩形データ
	}
}
