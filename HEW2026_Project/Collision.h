#pragma once
#include<DirectXmath.h>

class GameObject;

class Collision
{
public:
	//--- 当たり判定形状の種類
	enum Type {
		eNone,
		eBox,
		eSphere,
	};

	//--- 当たり判定の形状
	struct Box {		// 四角
		DirectX::XMFLOAT3		center;		// 中心座標
		DirectX::XMFLOAT3		size;		// サイズ	
	};
	
	struct Sphere {	// 球
		DirectX::XMFLOAT3		center;		// 中心座標
		float					radius;		// 半径
	};

	//--- 当たり判定の統合情報
	struct Info {
		Type type;
		union {
			Box box;
			Sphere sphere;
		};
	};

	//--- 当たり判定の結果
	struct Result {
		bool					isHit;		// 当たったかどうか
		DirectX::XMFLOAT3		point;		// ヒット位置
		DirectX::XMFLOAT3		normal;		// ヒット平面
		Info					other;		// 当たり判定オブジェクト
		GameObject* hitObject;
	};


public:
	// Info型での当たり判定
	static Result Hit(Info a, Info b);
	static Result Hit(Box a, Box b);
	static Result Hit(Sphere a, Sphere b);
	
};

