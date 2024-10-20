#pragma once
class AlkaRect;
class AlkaBall;

class AlkaMap
{
public:
	AlkaMap();
	~AlkaMap();

	void Update();
	void Render(HDC hdc);

	void IsCollision(shared_ptr<AlkaBall> ball);


private:
	vector<vector<shared_ptr<AlkaRect>>> _rect;

};

