#pragma once

#include"GameObject.h"
#include"Camera.h"
#include"CameraDebug.h"
#include"Geometory.h"
#include"Defines.h"
#include<DirectXMath.h>
#include"CsvData.h"

class Block :
    public GameObject
{
public:
	Block();
	~Block();
public:
	struct f2col
	{
		float x;
		float z;
	};

	enum BlockState
	{
		Block_Idle,
		Block_Drop,
		Block_Catch,
		Block_Catched,
		Block_Draw
	};

	enum Block_Color
	{
		None,
		Bacon,
		Buns_up,
		Buns_Button,
		Cheese,
		Fried_egg,
		Patty,
		Tomato
	};

	void Update()override;
	
	void Draw()override;

	void OnCollision(Collision::Result collision)override;

	void GetCamera(Camera *set);

	void SetCollision(f2col size);

	void SetPlayerPos(DirectX::XMFLOAT3 set);

	BlockState GetState();

	void SetState(BlockState set);

	void SetStep(int set);

	int GetStep();

private:
	Camera* m_pCamera;	//@ƒJƒƒ‰î•ñ
	DirectX::XMFLOAT3	m_move;		// ˆÚ“®—Ê
	DirectX::XMFLOAT3	m_playerPos;		// ˆÚ“®—Ê
	CsvData& csv;
	f2col m_CollisionSize;
	BlockState m_state;
	int m_nStep;// ‰½’i–Ú‚É‚ ‚é‚Ì‚©
	float m_fStepSizeY;
	Block_Color m_bColor;
public:
	Block(Block_Color set);
	Block(Block_Color set, float setX, float setY);
};

