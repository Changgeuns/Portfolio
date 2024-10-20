#include "pch.h"
#include "AlkaBall.h"

AlkaBall::AlkaBall()
{
	_circle = make_shared<CircleCollider>(Vector2(-1000,0), 8);
}


AlkaBall::~AlkaBall()
{
}

void AlkaBall::Update()
{
	Move();

	_circle->Update();
	
	BallOut();
}

void AlkaBall::Render(HDC hdc)
{
	_circle->Render(hdc);
}

void AlkaBall::Move()
{
	_circle->_center += _direction * _speed;
}

void AlkaBall::BallOut()
{
	if (_circle->_center._x < leftTop._x || _circle->_center._x > rightBottom._x)
	{
		_direction._x *= -1;
	}
	if (_circle->_center._y < leftTop._y)// || _circle->_center._y > rightBottom._y)
	{
		_direction._y *= -1;
	}
	if (_circle->_center._y > rightBottom._y)
	{
		_ballout = true;
	}
}



