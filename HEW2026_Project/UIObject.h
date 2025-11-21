/*********************************************************************
 * \file   UIObject.h
 * \brief  UIオブジェクトの基底クラス Base class of UI Object.
 *
 * \author AT12C-41 Kotetsu Wakabayashi
 * \date   2025-11-18
 *********************************************************************/
#pragma once
#include <string>
#include "Sprite.h"
#include "Texture.h"
#include <DirectXMath.h>

class UIObject
{
public:
	UIObject();
	UIObject(std::string RelativeTexturePathFromTextureFolder);
	UIObject(std::string RelativeTexturePathFromTextureFolder, float PositionX, float PositionY);
	UIObject(std::string RelativeTexturePathFromTextureFolder, float PositionX, float PositionY, float Width, float Height);
	UIObject(std::string RelativeTexturePathFromTextureFolder, float PositionX, float PositionY, float Width, float Height, float RotationX, float RotationY, float RotationZ);
	~UIObject();
	virtual void Update() {};
	void Draw();

	void SetPosition(float X, float Y);
	void SetSize(float W, float H);
	void SetRotation(float X, float Y, float Z);
	void SetUVPos(float X, float Y);
	void SetUVScale(float X, float Y);

	DirectX::XMFLOAT2 GetPosition(void);
	DirectX::XMFLOAT2 GetSize(void);
	DirectX::XMFLOAT3 GetRotation(void);
	DirectX::XMFLOAT2 GetUVPos(void);
	DirectX::XMFLOAT2 GetUVScale(void);

private:
	Texture* m_pTexture;
	DirectX::XMFLOAT2 m_fPosition;
	DirectX::XMFLOAT2 m_fSize;
	DirectX::XMFLOAT3 m_fRotation;
	DirectX::XMFLOAT2 m_fUVPos;
	DirectX::XMFLOAT2 m_fUVSize;
};