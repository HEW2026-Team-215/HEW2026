#include "Animation.h"
#include <cmath>
#include "Input.h"

Animation::Animation()
    : m_idleTimer(0.0f)
    , m_animState(AnimState::Idle)
    , m_amplitude(0.05f)
    , m_speed(8.0f)
    , m_animScale( 0.0f, 0.0f, 0.0f )
    , m_animRotation( 0.0f, 0.0f, 0.0f )
    , m_animPos(0.0f,0.0f,0.0f)
{
    Reset();
   
}

void Animation::Update()
{
    switch (m_animState)
    {
    case AnimState::Idle:
        UpdateIdle();
        break;
    case AnimState::Move:
        UpdateMove();
        break;
    case AnimState::Catch:
        UpdateCatch();
        break;
    default:
        break;
    }
}

void Animation::SetAnimSpeed(float amplitude, float speed)
{
    m_amplitude = amplitude;
    m_speed = speed;
}

void Animation::Reset()
{
    m_idleTimer = 0.0f;
    m_animScale = { 0.0f,0.0f,0.0f };
    m_animRotation = { 0.0f,0.0f,0.0f };
}

void Animation::SetState(AnimState state)
{
    if (m_animState != state) // <-- only reset if state changed
    {
        m_animState = state;

        if (state == AnimState::Idle)
        {
            m_idleTimer = 0.0f;
        }
    }
}

void Animation::UpdateIdle()
{
    // Smooth return to normal scale
    m_animScale.x += (1.0f - m_animScale.x) * FRAME_TIME * m_scaleReturnSpeed;
    m_animScale.y += (1.0f - m_animScale.y) * FRAME_TIME * m_scaleReturnSpeed;
    m_animScale.z += (1.0f - m_animScale.z) * FRAME_TIME * m_scaleReturnSpeed;

        m_idleTimer += FRAME_TIME;
        m_animScale.y= 1+ sinf(m_idleTimer * m_speed) * m_amplitude;
        m_animPos.y  = 1+ sinf(m_idleTimer * m_speed) * m_amplitude;
        
        m_animRotation.z = 0;
        m_animRotation.x = 0;
        m_targetScale = { 1.0f, 1.0f, 1.0f };

      
}

void Animation::UpdateMove()
{
    m_targetScale = { 1.0f, 1.0f, 1.0f };

    if (IsKeyPress('A'))
    {
        m_animRotation.z = -10.0f;
        m_targetScale.z = 0.85f; // squash

    }
    if (IsKeyPress('D'))
    {
        m_animRotation.z = 10.0f;
        m_targetScale.z = 0.85f;
    }

    if (IsKeyPress('W'))
    {
        m_animRotation.x = -10.0f;
        m_targetScale.y = 0.9f;
    }
    if (IsKeyPress('S'))
    {
        m_animRotation.x = 10.0f;
        m_targetScale.y = 0.9f;
    }

    // Smooth scale interpolation
    m_animScale.x += (m_targetScale.x - m_animScale.x) * FRAME_TIME * m_scaleReturnSpeed;
    m_animScale.y += (m_targetScale.y - m_animScale.y) * FRAME_TIME * m_scaleReturnSpeed;
    m_animScale.z += (m_targetScale.z - m_animScale.z) * FRAME_TIME * m_scaleReturnSpeed;
}

void Animation::UpdateCatch()
{

  
}

DirectX::XMFLOAT3 Animation::GetScale() const
{
    return m_animScale;
}
DirectX::XMFLOAT3  Animation::GetRotation() const
{
    return m_animRotation;
}
DirectX::XMFLOAT3  Animation::GetPos() const
{
    return m_animPos;
}
