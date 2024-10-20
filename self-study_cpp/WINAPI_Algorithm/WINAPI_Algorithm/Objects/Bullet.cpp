#include "pch.h"
#include "Bullet.h"
#include "Cannon.h"

Bullet::Bullet()
{
	_col = make_shared<CircleCollider>(CENTER, 7);
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	if(_isActive == false) return;

	Attack_Cannon();


	_col->Update();
	_col->_center += _direction * _speed;

	_col->_center += _downVector;
	_downVector += Vector2(0, 1) * GRAVITY;

	// OutControll : 반사를 위한 함수
	bool isout = IsOut();
	//bool isout = false;
	//OutControll();
	if (_lifeTime > _delayTime || isout)
	{
		_lifeTime = 0.0f;
		_isActive = false;
	}

	_lifeTime += 0.01f;
}

void Bullet::Render(HDC hdc)
{
	if(_isActive == false) return;

	_col->Render(hdc);
}

void Bullet::Fire(Vector2 startPos, Vector2 direction)
{
	_isActive = true;
	_col->_center = startPos;
	_direction = direction;
	_direction.Normalize();
	_downVector = Vector2();
}

void Bullet::SetActive(bool isActive)
{
	_downVector = Vector2();
	_isActive = isActive;
}

bool Bullet::IsOut()
{
	if(_col->_center._x > WIN_WIDTH || _col->_center._x < 0)
		return true;

	if(_col->_center._y > WIN_HEIGHT || _col->_center._y < 0)
		return true;

	return false;
}

void Bullet::OutControll()
{
	Vector2 center = _col->_center;
	if (center._x > WIN_WIDTH || center._x < 0)
	{
		_direction._x *= -1.0f;
	}
	if (center._y > WIN_HEIGHT || center._y < 0)
	{
		_direction._y *= -1.0f;
	}
}

void Bullet::Attack_Cannon(shared_ptr<Cannon> cannon)
{
	if(IsActive() == false)
		return;

	// => cannon의 body
	if (cannon->GetCollider()->IsCollision(_col))
	{
		SetActive(false);
		cannon->Gethp() -= 1;

		if (cannon->Gethp() == 5) cannon->GetCollider()->SetBLUE();
		else if (cannon->Gethp() == 4) cannon->GetCollider()->SetGreen();
		else if (cannon->Gethp() == 3) cannon->GetCollider()->SetYELLOW();
		else if (cannon->Gethp() == 2) cannon->GetCollider()->SetORANGE();
		else if (cannon->Gethp() == 1) cannon->GetCollider()->SetRed();
		else if (cannon->Gethp() <= 0)
		{
			cannon->deedmove(); // 체력이 0이하라면 안보이는곳으로 이동
			return;
		}
	}

}

void Bullet::Attack_Cannon()
{
	if (_target.expired() == false)
	{
		shared_ptr<Cannon> targetCannon = _target.lock();
		shared_ptr<Collider> targetCannonCol = targetCannon->GetCollider();
		if (targetCannonCol->IsCollision(_col))
		{
			SetActive(false);
			
		}
	}
}
