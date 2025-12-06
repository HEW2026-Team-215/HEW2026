#ifndef _CAMERADEBUG_H
#define _CAMERADEBUG_H
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>

// ★ これを必ずどこか1つの .cpp に書く
#pragma comment(lib, "xinput.lib")
#include "Camera.h"
#include "Input.h"
#include "Defines.h"
class CameraDebug : public Camera
{
public:
	CameraDebug();
	~CameraDebug();
	void Update() final;
	void SetPos(const DirectX::XMFLOAT3& pos)override;
private:
	float m_radXZ;		// カメラの横回転
	float m_radY;		// カメラの縦回転
	float m_radius;	// カメラと注視点の距離
	float m_radius_Z;
};


// デバッグ用：カメラの位置をImGuiに渡すためのクラス
// 一時的なものなのでシングルトンで作成し,どこでも読み込めるようにする
// 安全にカメラに値を渡せるならなんでもいい
// ファイル追加すればよかったかもね。
// やりたいならやってどうぞ。
class Cam_Pos
{
private:
	Cam_Pos() = default;
	~Cam_Pos() = default;
public:
	// シングルトンインスタンス取得
	static Cam_Pos& GetInstance()
	{
		static Cam_Pos instance;
		return instance;
	}

	Cam_Pos(const Cam_Pos&) = delete;
	Cam_Pos& operator=(const Cam_Pos&) = delete;

public:
	// 自由に読み書きできていいので公開メンバ変数
	float m_posZ;
	float m_posY;
};

#endif//_CAMERADEBUG_H