#include "Buns_Top.h"

Buns_Top::Buns_Top()
{
	m_sFilePath_Model = "";
	m_sFilePath_Texture = "";
	m_texColor4[0] = 1.0f;
	m_fDropVelocity = 0.1f;
	m_pos = DirectX::XMFLOAT3{ 0.0f,0.0f,0.0f };
	m_size = DirectX::XMFLOAT3{ 0.0f,0.0f,0.0f };
	m_velocity = DirectX::XMFLOAT3{ 0.0f,0.0f,0.0f };
	m_dropState = drop_state::IDLE;
}

Buns_Top::~Buns_Top()
{
}

void Buns_Top::Init()
{
}

void Buns_Top::Uninit()
{
}

void Buns_Top::Update()
{
	m_pos.x += m_velocity.x;
	m_pos.y += m_velocity.y;
	m_pos.z += m_velocity.z;

	m_velocity.x *= 0.99f;
	m_velocity.y *= 0.99f;
	m_velocity.z *= 0.99f;
}

void Buns_Top::Draw()
{

}

void Buns_Top::SetPos(DirectX::XMFLOAT3 set)
{
	m_pos = set;
}

void Buns_Top::SetSize(DirectX::XMFLOAT3 set)
{
	m_size = set;
}

void Buns_Top::SetVelocity(DirectX::XMFLOAT3 set)
{
	m_velocity = set;
}

DirectX::XMFLOAT3 Buns_Top::GetPos()
{
	return m_pos;
}

DirectX::XMFLOAT3 Buns_Top::GetSize()
{
	return m_size;
}

DirectX::XMFLOAT3 Buns_Top::GetVelocity()
{
	return m_velocity;
}
