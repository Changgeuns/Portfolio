#include "pch.h"
#include "CannonScene.h"
#include "Objects/Cannon.h"
#include "Objects/Bullet.h"

// 사양서
// 턴제 포트리스
// 각 cannon을 턴마다 서로 컨트롤을 받아서 공격
// cannon의 HP는 5
// 맞으면 hp - 1, hp가 0이면 cannon이 사라짐

CannonScene::CannonScene()
{
	_cannon1 = make_shared<Cannon>();
	_cannon2 = make_shared<Cannon>();

	_cannon1->isControlled = true;

	// Attack2
	//for (auto bullet : _cannon1->GetBullets())
	//{
	//	bullet->SetTarget(_cannon2);
	//}
}

CannonScene::~CannonScene()
{
}

void CannonScene::Update()
{
	_cannon1->Update();
	_cannon2->Update();

	if (!deedCheck(_cannon1, _cannon2)) TurnChange(); 
	
	// Attack1
	for (auto bullet : _cannon1->GetBullets())
	{
		bullet->Attack_Cannon(_cannon2);
	}
	for (auto bullet : _cannon2->GetBullets())
	{
		bullet->Attack_Cannon(_cannon1);
	}

}

void CannonScene::Render(HDC hdc)
{
	_cannon1->Render(hdc);
	_cannon2->Render(hdc);
}

void CannonScene::TurnChange()
{
	if (_cannon1->Attack_trg)
	{
		_cannon1->Attack_trg = false;
		_cannon1->isControlled = false;
		_cannon2->isControlled = true;

	}
	else
	{
		if (_cannon2->Attack_trg)
		{
			_cannon2->Attack_trg = false;
			_cannon2->isControlled = false;
			_cannon1->isControlled = true;
		}

	}

}

bool CannonScene::deedCheck(shared_ptr<Cannon> a, shared_ptr<Cannon> b)
{
	if (a->Gethp() <= 0)// 둘중하나가 죽으면 리턴값은 트루반환후 반대편 캐논이 컨트롤
	{ // 주도권을 게속 가져감
		b->isControlled = true;
		a->isControlled = false;

		return true;
	}
	if (b->Gethp() <= 0)
	{
		b->isControlled = false;
		a->isControlled = true;

		return true;
	}

	return false;
}

