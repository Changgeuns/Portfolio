#include "pch.h"
#include "Cannon.h"
#include "Objects/Barrel.h"
#include "Objects/Bullet.h"

Cannon::Cannon()
{
	_body = make_shared<CircleCollider>(CENTER, 50.0f);
	_barrel = make_shared<Barrel>();

	for(int i=0;i<1;i++)//
	{
		shared_ptr<Bullet> bullet = make_shared<Bullet>();
		bullet->SetActive(false);
		_bullets.push_back(bullet);
	}

	Move();
}

Cannon::~Cannon()
{
}

void Cannon::Update()
{
	if (isControlled)
	{
		Move();
		Fire();
	}

	_body->Update();
	_barrel->Update();

	for(auto bullet : _bullets)
		bullet->Update();
}

void Cannon::Render(HDC hdc)
{
	_barrel->Render(hdc);
	_body->Render(hdc);

	for(auto bullet : _bullets)
		bullet->Render(hdc);
}

void Cannon::Move()
{
	if (GetAsyncKeyState(VK_RIGHT))
	{
		_body->_center._x += 1.5f;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		_body->_center._x -= 1.5f;
	}
	if (GetAsyncKeyState(VK_UP))
	{
		_angle -= 0.05f;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		_angle += 0.05f;
	}

	_barrel->SetAngle(_angle);

	_barrel->SetStart(_body->_center);
}

void Cannon::Fire()
{
	// KEY DOWN
	if (GetAsyncKeyState(VK_SPACE) & 0x0001)
	{
		// _bullets... 꺼진 얘(isActive == false)가 있는지 확인하고
		// -> 꺼진 애를 찾아서 Fire

		//_bullet->Fire(_barrel->GetEndPos(), _barrel->GetDirection());

		//for (auto bullet : _bullets)
		//{
		//	if (bullet->IsActive() == false)
		//	{
		//		bullet->Fire(_barrel->GetEndPos(), _barrel->GetDirection());
		//		break;
		//	}
		//}
		Attack_trg = true;

		auto iter = std::find_if(_bullets.begin(), _bullets.end(), 
		[](shared_ptr<Bullet> bullet)->bool 
		{
			if(!bullet->IsActive()) return true;
			return false;
		});

		if (iter != _bullets.end())
		{
			(*iter)->Fire(_barrel->GetEndPos(), _barrel->GetDirection());
		}

	}

}
