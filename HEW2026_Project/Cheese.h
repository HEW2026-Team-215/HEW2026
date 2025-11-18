#pragma once
#include "Item.h"

class Cheese :
    public CItem
{
public:
    Cheese();
    ~Cheese();
public:
    void Init()override;
    void Uninit()override;
    void Update()override;
    void Draw()override;
public:
    void SetPos(DirectX::XMFLOAT3 set)override;
    void SetSize(DirectX::XMFLOAT3 set)override;
    void SetVelocity(DirectX::XMFLOAT3 set)override;
    DirectX::XMFLOAT3 GetPos()override;
    DirectX::XMFLOAT3 GetSize()override;
    DirectX::XMFLOAT3 GetVelocity()override;
};

