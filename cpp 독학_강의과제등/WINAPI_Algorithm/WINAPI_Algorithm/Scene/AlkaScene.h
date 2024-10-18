#pragma once
class AlkaPlayerBar;
class AlkaBall;
class AlkaMap;

class AlkaScene : public Scene
{
public:
	AlkaScene();
	~AlkaScene();

	void Init();

	void Update() override;
	void Render(HDC hdc) override;

	void notFire();
	void Fire();

private:
	bool _isFired = false;

	shared_ptr<AlkaPlayerBar> _playerBar;
	shared_ptr<AlkaBall> _playerBall; 
	shared_ptr<AlkaMap> _block;

};

