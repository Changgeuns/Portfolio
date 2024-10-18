#pragma once

class Cannon;
class CannonScene : public Scene
{
public:
	CannonScene();
	~CannonScene();

	// Scene을(를) 통해 상속됨
	void Update() override;
	void Render(HDC hdc) override;
	
	void TurnChange();
	bool deedCheck(shared_ptr<Cannon> a, shared_ptr<Cannon> b);
private:
	shared_ptr<Cannon> _cannon1;
	shared_ptr<Cannon> _cannon2;
};

