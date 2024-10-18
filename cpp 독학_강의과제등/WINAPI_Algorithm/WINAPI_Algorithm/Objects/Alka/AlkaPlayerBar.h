#pragma once
class AlkaPlayerBar
{
public:
	AlkaPlayerBar();
	~AlkaPlayerBar();

	void Update();
	void Render(HDC hdc);

	void Move();

	shared_ptr<RectCollider> GetRectCollider() { return _rect; }

	void IsCollision(shared_ptr<class AlkaBall> ball);

private:
	float speed = 6.0f;
	shared_ptr<RectCollider> _rect;
};

