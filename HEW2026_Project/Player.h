
#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "model.h"
#include <vector>

class Player : public GameObject {
public:
	Player();
	~Player();

	// XVˆ—
	void Update()override;

	// •`‰æˆ—
	void Draw()override;

	// ƒJƒƒ‰‚Ìİ’è
	void SetCamera(Camera* camera);

	void ClampPosition();

	DirectX::XMFLOAT3 GetPos();

	void OnCollision(Collision::Result collision)override;

	// NEW: Getter for carried objects
	const std::vector<GameObject*>& GetCarriedObjects() const { return m_carriedObjects; }

private:

	void UpdateMove();

private:

	Camera* m_pCamera;
	DirectX::XMFLOAT3	m_size;
	DirectX::XMFLOAT3	m_move;		// ˆÚ“®—Ê
	float m_speed = 2.0f;  // units per second

	std::vector<GameObject*> m_carriedObjects; // List of carried objects
};