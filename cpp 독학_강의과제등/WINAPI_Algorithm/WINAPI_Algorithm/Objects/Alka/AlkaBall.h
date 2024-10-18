#pragma once
class AlkaBall
{
public:
	AlkaBall();
	~AlkaBall();

	void Update();
	void Render(HDC hdc);

	void SetPosition(Vector2 pos) { _circle->_center = pos; }
	Vector2 GetPosition() { return _circle->_center; }
	void SetDirection(Vector2 direction) { _direction = direction; }
	Vector2 GetDirection() { return _direction; }

	void Move();
	shared_ptr<CircleCollider> GetCircleCollider() { return _circle; }

	void BallOut();
	bool _ballout = false;
private:
	Vector2 leftTop = { 0,0 };
	Vector2 rightBottom = { WIN_WIDTH, WIN_HEIGHT };

	shared_ptr<CircleCollider> _circle;
	Vector2 _direction;
	float _speed = 7.0f;

};

