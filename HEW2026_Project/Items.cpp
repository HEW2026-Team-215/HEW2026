#include "Items.h"
#include "Geometory.h"
#include "Collision.h"
#include "DirectXMath.h"

Items::Items() : m_isCarried(false), m_parent(nullptr)
{
	m_type = GameObject::Type::Item;

	m_pos = DirectX::XMFLOAT3(6.0f, 0.0f, 6.0f);

	DirectX::XMFLOAT3 size = DirectX::XMFLOAT3(2.0f, 2.0f, 2.0f);

	m_collision.type = Collision::eBox;
	m_collision.box = {
		m_pos,
		size
	};
}

Items::~Items()
{

}

void Items::Update()
{
	m_collision.box.center = m_pos;
	
}

void Items::Draw()
{
	////--- １つ目の地面
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);// 天面がグリッドよりも下に来るように移動
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(2.0f, 2.0f, 2.0f); // 地面となるように、前後左右に広く、上下に狭くする
	DirectX::XMMATRIX mat = S * T;

	mat = DirectX::XMMatrixTranspose(mat);
	DirectX::XMFLOAT4X4 fMat;
	DirectX::XMStoreFloat4x4(&fMat, mat);
	Geometory::SetWorld(fMat);
	Geometory::DrawBox();
}

void Items::SetCarried(bool carried) { m_isCarried = carried; }

bool Items::IsCarried()const  { return m_isCarried; }

void Items::SetParent(Player* player) { m_parent = player; }
Player* Items::GetParent()const  { return m_parent; }
