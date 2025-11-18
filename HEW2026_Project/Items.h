#pragma once
#include "GameObject.h"
#include "player.h"

class Items :public GameObject
{
public:
	Items();
	~Items();

	void SetCarried(bool carried);
	bool IsCarried() const;

	void SetParent(Player* player);
	Player* GetParent() const;

	void Update() final;
	void Draw() final; 
	

private:
	bool m_isCarried;
	Player* m_parent;
};