#pragma once
#include <list>
#include "Order.h"

class OrderManager
{
public:
		OrderManager();
		~OrderManager();
		void Update();
		void Draw();
		void Check();
private:
		std::list<COrder*> m_orderList;
};