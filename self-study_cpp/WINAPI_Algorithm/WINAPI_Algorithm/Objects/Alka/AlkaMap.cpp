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

				// 사각형의 각 변을 계산
				float left = rect->Left();
				float right = rect->Right();
				float top = rect->Top();
				float bottom = rect->Bottom();

				// 공의 위치와 사각형 위치를 비교하여 충돌 방향 결정
				bool collisionFromLeft = ballPos._x < left && ballDir._x > 0;
				bool collisionFromRight = ballPos._x > right && ballDir._x < 0;
				bool collisionFromTop = ballPos._y < top && ballDir._y > 0;
				bool collisionFromBottom = ballPos._y > bottom && ballDir._y < 0;

				if (collisionFromLeft || collisionFromRight)
				{
					ballDir._x *= -1; // X축 방향 반전
				}

				if (collisionFromTop || collisionFromBottom)
				{
					ballDir._y *= -1; // Y축 방향 반전
				}

				ball->SetDirection(ballDir);

				rect->DeedMove();

			}




		}
	}
}

