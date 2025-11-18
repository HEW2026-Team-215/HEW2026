/*********************************************************************
 * \file   UIObject.cpp
 * \brief  UIオブジェクトの基底クラス Base class of UI Object.
 *
 * \author AT12C-41 Kotetsu Wakabayashi
 * \date   2025-11-18
 *********************************************************************/
//=====| Includes |=====//
#include "UIObject.h"
#include "Defines.h"

UIObject::UIObject() : UIObject("Placeholder", SCREEN_WIDTH * .5f, SCREEN_HEIGHT * .5f, 100.f, 100.f) {};
