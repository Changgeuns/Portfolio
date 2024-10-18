#pragma once

#define GREEN_COLOR		0
#define RED_COLOR		1
#define BLUE_COLOR		2
#define ORANGE_COLOR		3
#define YELLOW_COLOR		4

class RectCollider;
class CircleCollider;

using ColorNum = int;

enum class ColliderType
{
	NONE,
	CIRCLE,
	RECT
};

class Collider
{
public:
	Collider(Vector2 center);
	virtual ~Collider();

	virtual void Update() abstract;
	virtual void Render(HDC hdc) abstract;

	bool IsCollision(shared_ptr<Collider> col);

	virtual bool IsCollision(Vector2 point) abstract;
	virtual bool IsCollision(shared_ptr<CircleCollider> other) abstract;
	virtual bool IsCollision(shared_ptr<RectCollider> other) abstract;

 	 virtual void SetRed() { SetColor(RED_COLOR); }
	 virtual void SetORANGE() { SetColor(ORANGE_COLOR); }
	 virtual void SetYELLOW() { SetColor(YELLOW_COLOR); }
	 virtual void SetGreen() { SetColor(GREEN_COLOR); }
	 virtual void SetBLUE() { SetColor(BLUE_COLOR); }

	Vector2 _center;

protected:
	void SetColor(ColorNum num);

	ColliderType _type = ColliderType::NONE;
	vector<HPEN> _pens;
	HPEN _curPen;
};

