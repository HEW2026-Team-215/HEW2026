#pragma once
#include <vector>
#include "Block.h"
#include "Timer.h"
#include "UIObject.h"

class OrderTimer : public CTimer
{
public: 
		OrderTimer();
		OrderTimer(float Limit);
		OrderTimer(float Limit, float WarnLine, float DangerLine);
		~OrderTimer();
		void Update() override;
		void Draw() override;

		float GetProgressRatio();
		void SetPosition(float x, float y);
private:
		float m_fWarnRatio = 0.65f;
		float m_fDangerRatio = 0.25f;
		UIObject* m_pUIOrderTimerFill = nullptr;
		UIObject* m_pUIOrderTimerPlaceholder = nullptr;
		UIObject* m_pUILineWarn = nullptr;
		UIObject* m_pUILineDanger = nullptr;
		DirectX::XMFLOAT2 m_pos;
};

class COrder
{
public:
	COrder();
	COrder(std::vector<Block::Block_Color> Recipe);
	COrder(std::vector<Block::Block_Color> Recipe, float limit);
	~COrder();
	void Update();
	void Draw();
	void SetOrderIndex(int num);
	int SellScore();
	bool GetIsFailure();

private:
	std::vector<Block::Block_Color> m_Order;
	int m_nBaseScore = 10;
	int m_nOrderIndex = 0;
	OrderTimer* m_pOrderTimer = nullptr;
	UIObject* m_pUIOrderBubble = nullptr;
	UIObject* m_pUIOrderBurger = nullptr;
	DirectX::XMFLOAT2 m_pos;
	bool m_bFailure = false; 
};