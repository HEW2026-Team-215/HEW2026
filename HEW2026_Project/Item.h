#pragma once

#include<string>
#include<DirectXMath.h>

/// <summary>
/// 落下情報
/// </summary>
/// <param name="IDLE">待機状態</param>
/// <param name="DROP">落下状態</param>
/// <param name="HAVE">持っている状態</param>
/// <param name="PREV">予測表示状態</param>
enum drop_state
{
	IDLE,   // 待機状態
	DROP,   // 落下状態
	CATCH,   // 持っている状態
	PREV    // 予測表示状態
};
class CItem
{
public:
	CItem();
	virtual ~CItem() = 0;

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
public:
	virtual void SetPos(DirectX::XMFLOAT3 set) = 0;
	virtual void SetSize(DirectX::XMFLOAT3 set) = 0;
	virtual void SetVelocity(DirectX::XMFLOAT3 set) = 0;
	virtual DirectX::XMFLOAT3 GetPos() = 0;
	virtual DirectX::XMFLOAT3 GetSize() = 0;
	virtual DirectX::XMFLOAT3 GetVelocity() = 0;
protected:
	std::string m_szName;			// 食材の名前
	std::string m_sFilePath_Model;	// モデルファイルパス
	std::string m_sFilePath_Texture;// テクスチャファイルパス
	float m_texColor4[4];
	float m_fDropVelocity;			// 落下スピード
	DirectX::XMFLOAT3 m_pos;		// 位置情報
	DirectX::XMFLOAT3 m_size;		// サイズ情報
	DirectX::XMFLOAT3 m_velocity;	// 移動量情報
	drop_state m_dropState;
};

