#include "Timer.h"
#include "Texture.h"
#include <Sprite.h>
#include "Defines.h"
#include <sstream>
#include <iomanip>
#include <cmath>

constexpr int NUM_COLS = 11;				// 数字.png の数字の列数

CTimer::CTimer()
	:m_pTimerTex(nullptr)
{
	InitializeTimer();
	m_pTimerTex = new Texture();
	if (FAILED(m_pTimerTex->Create("Assets/Texture/数字.png")))
		MessageBox(NULL, "Texture load failed.Nunber.png", "Error", MB_OK);
	m_pTimerFrameTex = new Texture();
	if (FAILED(m_pTimerFrameTex->Create("Assets/Texture/time.png")))
		MessageBox(NULL, "Texture load failed,Timer.png", "Error", MB_OK);
}

CTimer::~CTimer()
{
	if (m_pTimerTex)
	{
		delete m_pTimerTex;
		m_pTimerTex = nullptr;
	}
	if (m_pTimerFrameTex)
	{
		delete m_pTimerFrameTex;
		m_pTimerFrameTex = nullptr;
	}
}

void CTimer::InitializeTimer()
{
	//CPUの周波数を取得
	QueryPerformanceFrequency(&m_cpuFrequency);
	//最初の時刻を取得
	QueryPerformanceCounter(&m_lastTime);

	m_totalTime = m_limitTime;
}

void CTimer::Update()
{
	// 時間計測ロジック
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);

	LONGLONG elapsedTicks = currentTime.QuadPart - m_lastTime.QuadPart;
	double deltaTime = (double)elapsedTicks / m_cpuFrequency.QuadPart;

	m_totalTime -= deltaTime;
	if (m_totalTime < 0.0f)
	{
		m_totalTime = 0.0;
		MessageBox(NULL, "GAMEOVER", "Gameover", MB_OK);
	}

	m_lastTime = currentTime;
}

void CTimer::Draw()
{
	DirectX::XMMATRIX mView = DirectX::XMMatrixIdentity();
	DirectX::XMMATRIX mProj = DirectX::XMMatrixOrthographicOffCenterLH(
		0.0f,
		static_cast<float>(SCREEN_WIDTH),
		0.0f,
		static_cast<float>(SCREEN_HEIGHT),
		0.0f,
		1.0f
	);
	DirectX::XMFLOAT4X4	view, proj;
	DirectX::XMStoreFloat4x4(&view, DirectX::XMMatrixTranspose(mView));
	DirectX::XMStoreFloat4x4(&proj, DirectX::XMMatrixTranspose(mProj));
	Sprite::SetView(view);
	Sprite::SetProjection(proj);

	std::string timerStr = TimeToString(m_totalTime);

	DirectX::XMFLOAT2 startPos;
	// タイマー描画の開始位置 (例: 画面左上に表示)
	const float PADDING_X = 50.0f;
	const float PADDING_Y = 50.0f;

	DirectX::XMFLOAT2 digitSize = { 30.0f,45.0f };
	const float DIGIT_SPACING = 5.0f;

	int numDigits = (int)timerStr.length();

	float totalWidth = numDigits * digitSize.x + (numDigits - 1) * DIGIT_SPACING;
	startPos.x = (SCREEN_WIDTH - totalWidth) / 2.0f;
	startPos.y = 70.0f + digitSize.y / 2.0f;

	for (int i = 0; i < numDigits; i++)
	{
		char c = timerStr[i];
		int number = -1;

		// 文字に応じてインデックスを決定
		if (c >= '0' && c <= '9')
		{
			number = (c - '0') + 1;
		}
		else if (c == ':')
		{
			number = 0; // コロン用のインデックス
		}

		float currentX = startPos.x + i * (digitSize.x + DIGIT_SPACING) + digitSize.x * 0.5f;
		float currentY = startPos.y - digitSize.y * 0.5f;

		if (number != -1)
		{
			DrawDigit(number, { currentX,currentY }, digitSize);
		}
	}

	if (m_pTimerFrameTex)
	{
		DirectX::XMFLOAT2 framePos;
		framePos.x = SCREEN_WIDTH / 2.0f;       // 横中央
		framePos.y = startPos.y - 10.0f;                // 数字と同じ高さ

		DirectX::XMFLOAT2 frameSize;
		frameSize.x = totalWidth + 20.0f;      // 少し余白
		frameSize.y = digitSize.y + 20.0f;

		DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(framePos.x, framePos.y, 0.0f);
		DirectX::XMFLOAT4X4 world;
		DirectX::XMStoreFloat4x4(&world, DirectX::XMMatrixTranspose(T));

		Sprite::SetWorld(world);
		Sprite::SetTexture(m_pTimerFrameTex);
		Sprite::SetColor({ 1.0f,1.0f,1.0f,1.0f });
		Sprite::SetOffset({ 0.5f,0.5f });  // 中心を原点に
		Sprite::SetSize(frameSize);
		Sprite::SetUVPos({ 0.0f,0.0f });
		Sprite::SetUVScale({ 1.0f,1.0f });
		Sprite::Draw();
	}
}

void CTimer::DrawDigit(int number, DirectX::XMFLOAT2 centerPos, DirectX::XMFLOAT2 size)
{
	// DrawDigit の内容は CScore のものと全く同じロジックです。
	// CalculateUVForNumber を呼び出し、Sprite::Draw を実行します。
	DirectX::XMFLOAT4 uvRect = CalculateUVForNumber(number);

	DirectX::XMFLOAT2 uvPos = { uvRect.x,uvRect.y };
	DirectX::XMFLOAT2 uvScale;
	uvScale.x = uvRect.z - uvRect.x;
	uvScale.y = uvRect.w - uvRect.y;

	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(centerPos.x, centerPos.y, 0.0f);

	const float UP_DOWN_FLIP = -1.0f;
	DirectX::XMMATRIX mWorld = T;

	DirectX::XMFLOAT4X4 world;
	DirectX::XMStoreFloat4x4(&world, DirectX::XMMatrixTranspose(mWorld));

	Sprite::SetWorld(world);
	Sprite::SetTexture(m_pTimerTex);	// Timer のテクスチャを設定
	Sprite::SetColor({ 1.0f,1.0f,1.0f,1.0f });

	Sprite::SetOffset({ 0.0f,0.0f });
	Sprite::SetSize(size);

	Sprite::SetUVPos(uvPos);
	Sprite::SetUVScale(uvScale);

	Sprite::Draw();
}

std::string CTimer::TimeToString(double timeInSeconds)
{
	// 時間を分解
	int totalMillis = static_cast<int>(timeInSeconds * 1000);

	int minutes = totalMillis / 60000;
	int seconds = (totalMillis % 60000) / 1000;

	std::stringstream ss;

	ss << std::setw(2) << std::setfill('0') << minutes;
	ss << ":";
	ss << std::setw(2) << std::setfill('0') << seconds;

	return ss.str();
}

DirectX::XMFLOAT4 CTimer::CalculateUVForNumber(int number)
{
	const float GRID_W = 1.0f / 11.0f;
	const float GRID_H = 1.0f;

	float u_min = number * GRID_W;
	float v_min = 0.0f;
	float u_max = (number + 1) * GRID_W;
	float v_max = GRID_H;

	return DirectX::XMFLOAT4(u_min, v_min, u_max, v_max);
}
