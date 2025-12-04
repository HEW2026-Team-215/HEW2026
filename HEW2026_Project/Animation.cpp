#include "Animation.h"
#include "math.h"
#include <cmath>

Animation::Animation()
    : m_idleTimer(0.0f)
	, m_animState(AnimState::Idle)
    , m_idleAmplitude(0.1f)
    , m_idleSpeed(1.0f)
    , m_scale({1.0f, 1.0f, 1.0f})
    , m_rotation({0.0f, 0.0f, 0.0f})
{}

void Animation::Update(float deltaTime)
{
    // Idle animation: simple sine scaling
	switch (m_animState) {
		// ãÖÇÃë≈ÇøÇÕÇ∂Çﬂ
	case AnimState::Idle:
	{
		// Idle animation: only when the player is stopped
		m_idleTimer += deltaTime;
		float offset = sinf(m_idleTimer * m_idleSpeed) * m_idleAmplitude;
		m_scale = { 1.0f + offset, 1.0f + offset, 1.0f + offset };
		break;
	}
		// ÉLÅ[ì¸óÕåpë±íÜ
	case AnimState::Move:

		m_rotation.y += deltaTime * 2.0f;
		break;

		// ãÖÇë≈Ç¬
	case AnimState::Catch:
	{
		// Example: quick scale up for "catch" effect
		float targetScale = 1.2f;
		m_scale.x += (targetScale - m_scale.x) * deltaTime * 5.0f;
		m_scale.y += (targetScale - m_scale.y) * deltaTime * 5.0f;
		m_scale.z += (targetScale - m_scale.z) * deltaTime * 5.0f;
		break;
	}
	
	}
  
}

void Animation::SetIdle(float amplitude, float speed)
{
    m_idleAmplitude = amplitude;
    m_idleSpeed = speed;
}

void Animation::Reset()
{
    m_idleTimer = 0.0f;
    m_scale = {1.0f,1.0f,1.0f};
    m_rotation = {0.0f,0.0f,0.0f};
}

void Animation::SetState(AnimState state) 
{
	m_animState = state;
}