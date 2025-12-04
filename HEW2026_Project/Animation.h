#pragma once
#include <DirectXMath.h>

class Animation
{
public:
    enum class AnimState
    {
        Idle,
        Catch,
        Move,
        None,
    };

    Animation();
   // ~Animation();

    // Update animation per frame
    void Update(float deltaTime);

    // Get current scale/rotation offset for the model
    DirectX::XMFLOAT3 GetScale() const { return m_scale; }
    DirectX::XMFLOAT3 GetRotation() const { return m_rotation; }

    // Set parameters
    void SetState(AnimState state);
    void SetIdle(float amplitude, float speed);

    // Reset animation
    void Reset();

private:
    // Idle animation variables
    float m_idleTimer;
    float m_idleAmplitude;
    float m_idleSpeed;
    AnimState m_animState;

    // Current transform offsets
    DirectX::XMFLOAT3 m_scale;
    DirectX::XMFLOAT3 m_rotation;
};