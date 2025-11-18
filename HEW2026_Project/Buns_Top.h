#pragma once
#include "Item.h"


class Buns_Top :
    public CItem
{
public:
    Buns_Top();
    ~Buns_Top();
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

