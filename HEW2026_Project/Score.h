#pragma once
#include "Texture.h"
#include "Sprite.h"
#include <DirectXMath.h>

struct SpriteUVDate
{
	//{Umin Vmin Umax Vmax}
	DirectX::XMFLOAT4 UVRect;
};

class CScore
{
public:
	CScore();
	~CScore();
	void Update();
	void Draw();
	void DrawDigit(int number, DirectX::XMFLOAT2 centerPos, DirectX::XMFLOAT2 size);
private:
	Texture* m_pScoreTex;
	Texture* m_pGaugeTex;
	float m_rate;

	// テクスチャのレイアウト定数 (テクスチャ全体のサイズを1.0fとして正規化)
	const float TEX_WIDTH_UNITS = 1.0f;
	const float TEX_HEIGHT_UNITS = 1.0f;
	const int NUM_COLS = 4; // '0123'
	const int NUM_ROWS = 3; // '0123' '4567' '89,'

	// 1文字あたりの幅と高さ (正規化された単位)
	const float GRID_W = TEX_WIDTH_UNITS / (float)NUM_COLS;
	const float GRID_H = TEX_HEIGHT_UNITS / (float)NUM_ROWS;

	DirectX::XMFLOAT4 CalculateUVForNumber(int number);
};