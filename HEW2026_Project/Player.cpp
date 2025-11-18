#include "Player.h"
#include "Defines.h"
#include "CameraDebug.h"
#include "Camera.h"
#include "Geometory.h"
#include "DirectXMath.h"
#include "ShaderList.h"
#include "Collision.h"

Player::Player() : m_pCamera(nullptr),m_size(2.0f,2.0f,2.0f), m_move()
{
	m_type = GameObject::Type::Player;

	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();
	SetRenderTargets(1, &pRTV, pDSV);
	SetDepthTest(true);

	//collision boxw
	m_collision.type = Collision::eBox;
	m_collision.box = {
		m_pos,m_size//size of collisionbox
	};
}

Player::~Player()
{
	
}

// 更新処理
void Player::Update()
{
	// カメラが設定されてない場合は処理しない
	if (!m_pCamera) return;

	// 1. Update player movement first
	UpdateMove();

	// 2. Update positions of carried items
	for (size_t i = 0; i < m_carriedObjects.size(); ++i)
	{
		GameObject* carry = m_carriedObjects[i];
		float offsetY = 2.0f + i * 1.0f;
		DirectX::XMFLOAT3 newPos = m_pos;
		newPos.y += offsetY;
		carry->SetPosition(newPos);
	}
}


// 描画処理
void Player::Draw() {
//	////--- １つ目の地面
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(2.0f, 2.0f, 2.0f);
	DirectX::XMMATRIX mat = S * T;
	mat = DirectX::XMMatrixTranspose(mat);
	DirectX::XMFLOAT4X4 fMat;
	DirectX::XMStoreFloat4x4(&fMat, mat);
	Geometory::SetWorld(fMat);
	Geometory::DrawBox();
}

// カメラの設定
void Player::SetCamera(Camera* camera)
{
	m_pCamera = camera;
}


// 移動中の処理
void Player::UpdateMove() {

	// reset movement
    m_move = {0.0f, 0.0f, 0.0f};

	if (IsKeyTrigger('A')) {
		m_move.x += 2.0f;
	}
	if (IsKeyTrigger('D')) {
		m_move.x -= 2.0f;
	}
	if (IsKeyTrigger('W')) {
		m_move.z -= 2.0f;
	}
	if (IsKeyTrigger('S')) {
		m_move.z += 2.0f;
	}

	// apply movement
	m_pos.x += m_move.x;
	m_pos.z += m_move.z;
	// Update collision box after moving
	m_collision.box.center = m_pos;
	ClampPosition();

}


void Player::ClampPosition() {
	const float FIELD_LIMIT = 10.0f;
	if (m_pos.x < -FIELD_LIMIT) m_pos.x = -FIELD_LIMIT;
	if (m_pos.x > FIELD_LIMIT)  m_pos.x = FIELD_LIMIT;
	if (m_pos.z < -FIELD_LIMIT) m_pos.z = -FIELD_LIMIT;
	if (m_pos.z > FIELD_LIMIT)  m_pos.z = FIELD_LIMIT;
}

DirectX::XMFLOAT3 Player::GetPos()
{
	return m_pos;
}

void Player::OnCollision(Collision::Result collision)
{
	GameObject* obj = collision.hitObject;
	if (!obj) return;

	if (obj->GetType() == GameObject::Type::Item)
	{
		// Avoid duplicates
		if (std::find(m_carriedObjects.begin(), m_carriedObjects.end(), obj) != m_carriedObjects.end())
			return;

		// Pick up the item
		obj->SetCarried(true);
		obj->SetParent(this);
		m_carriedObjects.push_back(obj);
	}
}