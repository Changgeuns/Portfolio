#pragma once
class Cannon
{
public:
	Cannon();
	~Cannon();

	void Update();
	void Render(HDC hdc);

	void Move();
	void Fire();

	bool isControlled = false;
	bool Attack_trg = false;

	shared_ptr<Collider> GetCollider() { return _body; }
	vector<shared_ptr<class Bullet>>& GetBullets() { return _bullets; }

	int& Gethp() { return _curHP; }
	void deedmove() { _body->_center._x += 10000; }
private:
	shared_ptr<Collider> _body;
	shared_ptr<class Barrel> _barrel;
	vector<shared_ptr<class Bullet>> _bullets;
	int _maxHP = 5;
	int _curHP = _maxHP;

	float _angle = 0.0f;
};

