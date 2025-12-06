#pragma once
#include <DirectXMath.h>
#include <Windows.h>

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
    void Update();

    // Get current scale/rotation offset for the model
    DirectX::XMFLOAT3 GetScale() const;
    DirectX::XMFLOAT3 GetRotation() const;
    DirectX::XMFLOAT3 GetPos() const;

    // Set parameters
    void SetState(AnimState state);
    void SetAnimSpeed(float amplitude, float speed);
    // State update helpers
    void UpdateIdle();
    void UpdateMove();
    void UpdateCatch();

    // Reset animation
    void Reset();
 

private:
    // Idle animation variables
    float m_idleTimer;
    float m_amplitude;
    float m_scaleReturnSpeed = 8.0f;
    float m_rotationReturnSpeed = 10.0f; // tweak
    float m_speed;
    static constexpr float FRAME_TIME = 1.0f / 60.0f;
    AnimState m_animState;

    // Current transform offsets
    DirectX::XMFLOAT3 m_targetScale;
    DirectX::XMFLOAT3 m_targetRotation;
    DirectX::XMFLOAT3 m_animScale;
    DirectX::XMFLOAT3 m_animRotation;
    DirectX::XMFLOAT3 m_animPos;
};