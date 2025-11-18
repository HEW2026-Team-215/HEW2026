#ifndef _PLAYER_H
#define _PLAYER_H

#include"GameObject.h"
#include"Camera.h"
#include"CameraDebug.h"
#include"Geometory.h"
#include"Defines.h"
#include<DirectXMath.h>
#include"Sprite.h"

class Player : public GameObject {
public:
	Player();
	~Player();

	// XVˆ—
	void Update();

	// •`‰æˆ—
	void Draw();

	// ƒJƒƒ‰‚Ìİ’è
	void SetCamera(Camera* camera);

	void OnCollision(Collision::Result collision)override;

	void SetShadow(DirectX::XMFLOAT3 pos);
public:
	struct Index
	{
		int x;
		int z;
	};
	struct float2
	{
		float x;
		float y;
	};
private:
	// ‹…‚ğ‘Å‚Âˆ—
	void UpdateShot();

	void UpdateControl();

	// ˆÚ“®’†‚Ìˆ—
	void UpdateMove();

	void UpdateWall();

private:
	Camera* m_pCamera;	//@ƒJƒƒ‰î•ñ
	DirectX::XMFLOAT3	m_move;		// ˆÚ“®—Ê
	bool		m_isStop;	// ƒ{[ƒ‹‚Ì’â~”»’è
	int		m_shotStep; // 
	float	m_power;		// speed‚ÉvLen‚ğŠi”[
	float2 m_f2pos;
	Index m_idx;
	float m_angle;

	Texture* m_pShadowTex;	// ‰e‚ÌŒ©‚½–Ú
	DirectX::XMFLOAT3	m_shadowPos;	// ‰e‚ÌˆÊ’u

	CsvData& csv;

};

#endif//_PLAYER_H