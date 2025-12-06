#pragma once

#include<Windows.h>
#include <Xinput.h>

extern XINPUT_STATE g_currentState;
extern XINPUT_STATE g_prevState;
struct Stick
{
    float x = 0.0f;   // -1.0?1.0
    float y = 0.0f;   // -1.0?1.0
    float len = 0.0f; // ƒxƒNƒgƒ‹’· 0.0?1.0
};

void UpdateGamepad();
bool IsButtonDown(WORD button);
bool IsButtonPressed(WORD button);
bool IsButtonReleased(WORD button);

Stick GetLeftStick();
Stick GetRightStick();
