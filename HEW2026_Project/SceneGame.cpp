#include "SceneGame.h"
#include "Geometory.h"
#include "Defines.h"
#include "Player.h"
#include "CameraDebug.h"
#include "Collision.h"
#include "GameObject.h"

SceneGame::SceneGame()
{
	m_player = new Player();
	m_pCamera = new CameraDebug();
	//m_items = new Items();
	for (int i = 0; i < 5; i++)
	{
		Items* item = new Items();
		item->SetPosition({ float(i * 2+2), 0, float(i * 2+2) }); // spread out
		m_items.push_back(item);
	}
}

SceneGame::~SceneGame()
{
	if (m_player) {
		delete m_player;
		m_player = nullptr;
	}
	for (auto item : m_items)
	{
		if (item)
		{
			delete item;
		}
	}
	m_items.clear(); // clear vector

	if (m_pCamera) {
		delete m_pCamera;
		m_pCamera = nullptr;
	}
}

void SceneGame::Update()
{
	m_player->SetCamera(m_pCamera);
	m_pCamera->Update();
	

	Collision::Info playerCol = m_player->GetCollision();

	for (Items* item : m_items)
	{
		Collision::Info itemCol = item->GetCollision();
		Collision::Result result = Collision::Hit(playerCol, itemCol);

		if (result.isHit)
		{
			result.hitObject = item;  // <<< IMPORTANT
			m_player->OnCollision(result);
		}
	}

	m_player->Update();


}

void SceneGame::Draw()
{
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);// 天面がグ
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f);
	DirectX::XMMATRIX mat = S * T;
	DirectX::XMFLOAT4X4 wvp[3];
	DirectX::XMMATRIX world = DirectX::XMMatrixTranspose(mat);
	DirectX::XMMATRIX view, proj;
	DirectX::XMVECTOR EyePosition = DirectX::XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f);
	DirectX::XMVECTOR FocusPosition = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	DirectX::XMVECTOR UpDirection = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	//
	view = DirectX::XMMatrixLookAtLH(EyePosition, FocusPosition, UpDirection);
	proj = DirectX::XMMatrixPerspectiveFovLH(90.0f, 16 / 9.0f, 0.0001, 1000.0f);

	//　計算用のデータから読み取り用のデータに変換
	DirectX::XMStoreFloat4x4(&wvp[0], world);
	//	
		// モデルに変換行列を設定
	wvp[1] = m_pCamera->GetViewMatrix();
	wvp[2] = m_pCamera->GetProjectionMatrix();
	//
	//	// 仮置きしているボックスにカメラを設定
	Geometory::SetView(m_pCamera->GetViewMatrix());
	Geometory::SetProjection(m_pCamera->GetProjectionMatrix());

	m_player->Draw();

	for (Items* item : m_items)
	{
		if (item)
			item->Draw();
	}
	
}
