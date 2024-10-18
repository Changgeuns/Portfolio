#include "pch.h"
#include "AlkaMap.h"

#include "Objects/Alka/AlkaRect.h"
#include "Objects/Alka/AlkaBall.h"

AlkaMap::AlkaMap()
{
	Vector2 offSet = Vector2(60, 80);

	_rect.reserve(MAXCOUNT_Y);

	for (int i = 0; i < MAXCOUNT_Y; i++)
	{
		vector<shared_ptr<AlkaRect>> rect_X;
		rect_X.reserve(MAXCOUNT_X);

		for (int j = 0; j < MAXCOUNT_X; j++)
		{
			Vector2 rectOffset = offSet + Vector2(60.0f * j, 20.0f * i);

			shared_ptr<AlkaRect> rect = make_shared<AlkaRect>();
			rect->SetPosition(rectOffset);
			rect_X.push_back(rect);
		}

		_rect.push_back(rect_X);
	}
}

AlkaMap::~AlkaMap()
{
}

void AlkaMap::Update()
{
	for (auto rect_X : _rect)
	{
		for (auto rect : rect_X)
		{
			rect->Update();
		}
	}
}

void AlkaMap::Render(HDC hdc)
{
	for (auto rect_X : _rect)
	{
		for (auto rect : rect_X)
		{
			rect->Render(hdc);
		}
	}
}

void AlkaMap::IsCollision(shared_ptr<AlkaBall> ball)
{
	for (auto rect_X : _rect)
	{
		for (auto rect : rect_X)
		{
			Vector2 ballPos = ball->GetPosition();
			Vector2 ballDir = ball->GetDirection();


			if (rect->IsCollision(ball->GetCircleCollider()))
			{

				// �簢���� �� ���� ���
				float left = rect->Left();
				float right = rect->Right();
				float top = rect->Top();
				float bottom = rect->Bottom();

				// ���� ��ġ�� �簢�� ��ġ�� ���Ͽ� �浹 ���� ����
				bool collisionFromLeft = ballPos._x < left && ballDir._x > 0;
				bool collisionFromRight = ballPos._x > right && ballDir._x < 0;
				bool collisionFromTop = ballPos._y < top && ballDir._y > 0;
				bool collisionFromBottom = ballPos._y > bottom && ballDir._y < 0;

				if (collisionFromLeft || collisionFromRight)
				{
					ballDir._x *= -1; // X�� ���� ����
				}

				if (collisionFromTop || collisionFromBottom)
				{
					ballDir._y *= -1; // Y�� ���� ����
				}

				ball->SetDirection(ballDir);

				rect->DeedMove();

			}





			/*Vector2 dir = ball->GetDirection();
			if (rect->IsCollision(ball->GetCircleCollider()) == false) continue;
			dir._y *= -1.0f;
			ball->SetDirection(dir);
			rect->DeedMove();*/



		}
	}
}

