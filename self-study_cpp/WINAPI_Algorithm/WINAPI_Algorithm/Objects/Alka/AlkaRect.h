#pragma once

#define MAXCOUNT_X 20
#define MAXCOUNT_Y 10

class AlkaRect : public RectCollider
{
public:
	enum class RectType
	{
		ALIVE,
		DIE
	};

	AlkaRect();
	~AlkaRect();

	void Update();
	void Render(HDC hdc);

	void SetPosition(Vector2 pos);

	void DeedMove();


private:
	RectType _type = RectType::ALIVE;
	bool _deed = false;

	vector<HBRUSH> _brushes;
};

