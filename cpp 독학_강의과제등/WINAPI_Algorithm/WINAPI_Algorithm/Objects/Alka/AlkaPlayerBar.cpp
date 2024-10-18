#include "pch.h"
#include "AlkaPlayerBar.h"

#include "Objects/Alka/AlkaBall.h"

AlkaPlayerBar::AlkaPlayerBar()
{
	Vector2 rectpos = CENTER;
	rectpos._y += 200;
	_rect = make_shared<RectCollider>(rectpos, Vector2(60, 10));
	
}

AlkaPlayerBar::~AlkaPlayerBar()
{
}

void AlkaPlayerBar::Update()
{
	Move();


	_rect->Update();
}

void AlkaPlayerBar::Render(HDC hdc)
{
	_rect->Render(hdc);

}

void AlkaPlayerBar::Move()
{
	if (GetAsyncKeyState(VK_RIGHT))
	{
		_rect->_center._x += 1.0f * speed;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		_rect->_center._x -= 1.0f * speed;
	}
}

void AlkaPlayerBar::IsCollision(shared_ptr<class AlkaBall> ball)
{
	if (ball->GetDirection().Length() <= 0.001f)
	{
		return;
	}

	if (_rect->IsCollision(ball->GetCircleCollider()) == false)
		return;

	Vector2 cirPos = ball->GetCircleCollider()->_center;
	Vector2 rectPos = _rect->_center;

	Vector2 dir = cirPos - rectPos;
	dir.Normalize();

	ball->SetDirection(dir);
}

