#include "Collision.h"

Collision::Result Collision::Hit(Info a, Info b)
{
	Result out = {};
	if (a.type == b.type) {
		switch (a.type) {
		case eBox:		out = Hit(a.box, b.box);			break;
		case eSphere:	out = Hit(a.sphere, b.sphere);	break;
		}
	}
	return out;
}

Collision::Result Collision::Hit(Box a, Box b)
{
	Result out = {};
	// VECTOR型に変換
	DirectX::XMVECTOR vPosA = DirectX::XMLoadFloat3(&a.center);
	DirectX::XMVECTOR vPosB = DirectX::XMLoadFloat3(&b.center);
	DirectX::XMVECTOR vSizeA = DirectX::XMLoadFloat3(&a.size);
	DirectX::XMVECTOR vSizeB = DirectX::XMLoadFloat3(&b.size);
	// ボックスの半分のサイズを取得
	vSizeA = DirectX::XMVectorScale(vSizeA, 0.5f);
	vSizeB = DirectX::XMVectorScale(vSizeB, 0.5f);
	// ボックスの各軸の最大値、最小値を取得
	DirectX::XMVECTOR vMaxA = DirectX::XMVectorAdd(vPosA, vSizeA);
	DirectX::XMVECTOR vMinA = DirectX::XMVectorSubtract(vPosA, vSizeA);
	DirectX::XMVECTOR vMaxB = DirectX::XMVectorAdd(vPosB, vSizeB);
	DirectX::XMVECTOR vMinB = DirectX::XMVectorSubtract(vPosB, vSizeB);
	DirectX::XMFLOAT3 maxA, minA, maxB, minB;
	DirectX::XMStoreFloat3(&maxA, vMaxA);
	DirectX::XMStoreFloat3(&minA, vMinA);
	DirectX::XMStoreFloat3(&maxB, vMaxB);
	DirectX::XMStoreFloat3(&minB, vMinB);
	
	// ボックスの面同士の関係から当たり判定を行う
	out.isHit = false;
	if (maxA.x >= minB.x && minA.x <= maxB.x) {
		if (maxA.y >= minB.y && minA.y <= maxB.y) {
			if (maxA.z >= minB.z && minA.z <= maxB.z) {
				out.isHit = true;


				// 各軸のめり込み量を計算
				out.normal.x = std::min(maxA.x - minB.x, maxB.x - minA.x);
				out.normal.y = std::min(maxA.y - minB.y, maxB.y - minA.y) * 0.5f;
				out.normal.z = std::min(maxA.z - minB.z, maxB.z - minA.z);
				// めり込みが少ない面を当たった面とみなし、面の法線を計算する
				if (out.normal.x < out.normal.y) {
					if (out.normal.x < out.normal.z)
						out.normal = DirectX::XMFLOAT3(
							a.center.x >= b.center.x ? 1.0 : -1.0f, 0.0f, 0.0f);
					else
						out.normal = DirectX::XMFLOAT3(0.0f, 0.0f,
							a.center.z >= b.center.z ? 1.0 : -1.0f);
				}
				else {
					if (out.normal.y < out.normal.z)
						out.normal = DirectX::XMFLOAT3(0.0f,
							a.center.y >= b.center.y ? 1.0 : -1.0f, 0.0f);
					else
						out.normal = DirectX::XMFLOAT3(0.0f, 0.0f,
							a.center.z >= b.center.z ? 1.0 : -1.0f);
				}
			}
		}
	}
	return out;
}

Collision::Result Collision::Hit(Sphere a, Sphere b)
{
	Result out = {};
	// 計算に必要なデータを計算
	DirectX::XMVECTOR vPosA = DirectX::XMLoadFloat3(&a.center);
	DirectX::XMVECTOR vPosB = DirectX::XMLoadFloat3(&b.center);
	DirectX::XMVECTOR vDist = DirectX::XMVectorSubtract(vPosA, vPosB);
	DirectX::XMVECTOR vLen = DirectX::XMVector3Length(vDist);
	float length;
	DirectX::XMStoreFloat(&length, vLen);

	out.isHit = (length <= (a.radius + b.radius));

	return out;
}
