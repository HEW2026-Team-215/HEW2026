
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>

#pragma comment(lib, "xinput.lib")

#include <cmath> // sqrtf, atan2f 使うので

#include "Controller.h"

XINPUT_STATE g_currentState{};
XINPUT_STATE g_prevState{};

void UpdateGamepad()
{
    g_prevState = g_currentState;

    XINPUT_STATE state{};
    if (XInputGetState(0, &state) == ERROR_SUCCESS)
    {
        g_currentState = state;
    }
    else
    {
        ZeroMemory(&g_currentState, sizeof(XINPUT_STATE));
    }
}

bool IsButtonDown(WORD button)
{
    return (g_currentState.Gamepad.wButtons & button) != 0;
}

bool IsButtonPressed(WORD button)
{
    bool now = (g_currentState.Gamepad.wButtons & button) != 0;
    bool prev = (g_prevState.Gamepad.wButtons & button) != 0;
    return now && !prev;
}

bool IsButtonReleased(WORD button)
{
    bool now = (g_currentState.Gamepad.wButtons & button) != 0;
    bool prev = (g_prevState.Gamepad.wButtons & button) != 0;
    return !now && prev;
}

static Stick NormalizeStick(SHORT rawX, SHORT rawY, SHORT deadZone)
{
    Stick s{};

    float fx = static_cast<float>(rawX);
    float fy = static_cast<float>(rawY);

    float mag = std::sqrt(fx * fx + fy * fy);
    if (mag < deadZone)
    {
        // デッドゾーン内は0扱い
        return s;
    }

    // デッドゾーンを引いた上で0～1に正規化
    float normMag = (mag - deadZone) / (32767.0f - deadZone);
    if (normMag > 1.0f) normMag = 1.0f;

    float nx = fx / mag;
    float ny = fy / mag;

    s.x = nx * normMag;  // -1〜1
    s.y = ny * normMag;  // -1〜1
    s.len = normMag;       // 0〜1

    return s;
}

Stick GetLeftStick()
{
    return NormalizeStick(
        g_currentState.Gamepad.sThumbLX,
        g_currentState.Gamepad.sThumbLY,
        XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
    );
}

Stick GetRightStick()
{
    return NormalizeStick(
        g_currentState.Gamepad.sThumbRX,
        g_currentState.Gamepad.sThumbRY,
        XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE
    );
}
