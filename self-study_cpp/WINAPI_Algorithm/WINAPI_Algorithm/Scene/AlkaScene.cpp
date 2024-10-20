#include "pch.h"
#include "AlkaScene.h"

#include "Objects/Alka/AlkaPlayerBar.h"
#include "Objects/Alka/AlkaBall.h"
#include "Objects/Alka/AlkaMap.h"

AlkaScene::AlkaScene()
{
	_playerBar = make_shared<AlkaPlayerBar>();
	_playerBall = make_shared<AlkaBall>();
	_block = make_shared<AlkaMap>();
}

AlkaScene::~AlkaScene()
{
}

void AlkaScene::Init()
{
}

void AlkaScene::Update()
{
	notFire(); // 발사하지않은상태
	Fire(); // 발사한상태와 아웃되었을때 되돌리는 함수

	_playerBar->IsCollision(_playerBall);
	_block->IsCollision(_playerBall);

	_playerBar->Update();
	_playerBall->Update();
	_block->Update();
}

void AlkaScene::Render(HDC hdc)
{
	_playerBar->Render(hdc);
	_playerBall->Render(hdc);
	_block->Render(hdc);
}

void AlkaScene::notFire()
{

	if (_isFired == true) return;

	Vector2 pos = _playerBar->GetRectCollider()->_center;
	pos._y = _playerBar->GetRectCollider()->Top();
	pos._y -= _playerBall->GetCircleCollider()->_radius;

	_playerBall->SetPosition(pos);
}

void AlkaScene::Fire()
{
	if (_playerBall->_ballout == true)
	{
		_isFired = false;
		_playerBall->_ballout = false;
	}
	if (_isFired == true) return;

	if (GetAsyncKeyState(VK_SPACE) & 0x0001)
	{
		_isFired = true;
		_playerBall->SetDirection(Vector2(0, -1));
	}
}


