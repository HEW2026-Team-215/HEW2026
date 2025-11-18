#include "Item.h"

CItem::CItem()
	: m_szName("çﬁóø")
	, m_sFilePath_Model("unknown")
	, m_sFilePath_Texture("unknown")
	, m_texColor4{ 1.0f,1.0f,1.0f,1.0f }
	, m_fDropVelocity(0.0f)
	, m_pos{ 0.0f,0.0f,0.0f }
	, m_size{ 1.0f,1.0f,1.0f }
	, m_velocity{ 0.0f,0.0f,0.0f }
	, m_dropState(drop_state::IDLE)
{

}
