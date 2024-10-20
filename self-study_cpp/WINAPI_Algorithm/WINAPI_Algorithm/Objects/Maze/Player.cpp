#include "pch.h"
#include "Player.h"

#include "Maze.h"
#include "Block.h"

Player::Player(shared_ptr<Maze> maze)
{
	_maze = maze;
}

Player::~Player()
{
	_maze = nullptr;
}

void Player::BeginPlay()
{
	_maze->SetPlayerPos(_pos);
	_pos = _maze->GetStartPos();
	BFS(_pos);
}


void Player::RightHand()
{

	enum Direction
	{
		UP,
		LEFT,
		BOTTOM,
		RIGHT,

		DIR_COUNT = 4
	};

	Vector2 pos = _pos;
	_path.push_back(pos);
	Vector2 endPos = _maze->GetEndPos();

	Direction dir = Direction::BOTTOM;

	Vector2 frontPos[4] =
	{
		Vector2 {0,-1}, // Up
		Vector2 {-1,0}, //Left
		Vector2 {0,1},	// bottom
		Vector2 {1,0}	// right
	};

	while (true)
	{
		if (pos == endPos)
			break;

		int newDir = (dir - 1 + DIR_COUNT) % DIR_COUNT;
		Vector2 oldDirVector2 = frontPos[dir];
		Vector2 newDirVector2 = frontPos[newDir];

		Vector2 newPos = pos + newDirVector2;// 내 오른쪽 방향
		Vector2 oldPos = pos + oldDirVector2; //내 앞방향
		// 오른쪽으로 갈수있으면 방향을 바꾸고 오른쪽으로 진행
		if (Cango(newPos._y, newPos._x))
		{
			dir = static_cast<Direction>(newDir);
			pos += newDirVector2;
			_path.push_back(pos);
		}
		// 오른쪽이 막혀있고 앞으로 갈수있으면 방향그대로 앞으로 진행
		else if (Cango(oldPos._y, oldPos._x))
		{
			pos += oldDirVector2;
			_path.push_back(pos);
		}
		// 오른쪽, 앞 둘다 막혀있는 상황이라면 왼쪽으로 회전
		else
		{
			dir = static_cast<Direction>((dir + 1 + DIR_COUNT) % DIR_COUNT);
		}
	}

	stack<Vector2> s;

	for (int i = 0; i < _path.size() - 1; i++)
	{
		if (s.empty() == false && s.top() == _path[i + 1])
			s.pop();
		else
			s.push(_path[i]); 
	}
	s.push(_path.back());

	_path.clear();

	while (true)
	{
		if (s.empty() == true)
			break;

		_path.push_back(s.top());
		s.pop();
	}

	std::reverse(_path.begin(), _path.end());
}

void Player::DFS(Vector2 start)
{
	Vector2 frontPos[8] =
	{
		Vector2 {0,-1}, // Up
		Vector2 {-1,0}, //Left
		Vector2 {0,1},	// bottom
		Vector2 {1,0},	// right

		Vector2 {-1,-1}, // Up Left
		Vector2 {-1,1}, //Left Bottom
		Vector2 {1,1},	// bottom right
		Vector2 {1,-1}	// right up
	};

	vector<vector<bool>> discovered = vector<vector<bool>>(MAXCOUNT_Y, vector<bool>(MAXCOUNT_X, false));
	vector<vector<Vector2>> parent = vector<vector<Vector2>>(MAXCOUNT_Y, vector<Vector2>(MAXCOUNT_X, Vector2(-1, -1)));



}

void Player::BFS(Vector2 start)
{
	Vector2 frontPos[8] =
	{
		Vector2 {0,-1}, // Up
		Vector2 {-1,0}, //Left
		Vector2 {0,1},	// bottom
		Vector2 {1,0},	// right

		Vector2 {-1,-1}, // Up Left
		Vector2 {-1,1}, //Left Bottom
		Vector2 {1,1},	// bottom right
		Vector2 {1,-1}	// right up
	};

	//discovered[0] == true;
	vector<vector<bool>> discovered = vector<vector<bool>>(MAXCOUNT_Y, vector<bool>(MAXCOUNT_X,false));
	vector<vector<Vector2>> parent = vector<vector<Vector2>>(MAXCOUNT_Y, vector<Vector2>(MAXCOUNT_X, Vector2(-1,-1)));
	
	Vector2 pos = start;
	Vector2 endPos = _maze->GetEndPos();

	discovered[start._y][start._x] = true;
	parent[start._y][start._x] = start;

	queue<Vector2> q;
	q.push(start);

	while (true)
	{
		if (q.empty()) break;

		Vector2 here = q.front();
		q.pop();

		// 지금 큐의 front 가 도착점이면 break
		if (here == endPos) break;

		for (int i = 0; i < 8; i++)
		{
			Vector2 there = here + frontPos[i];

			// there 가 갈수있는 블럭인지 확인.
			if (!Cango(there._y, there._x)) continue;
			// there 가 방문되어 있엇는지 확인.
			if (discovered[there._y][there._x] == true) continue;


			q.push(there);
			discovered[there._y][there._x] = true;
			parent[there._y][there._x] = here;

		}
	}

	Vector2 check = endPos;
	_path.push_back(check);
	while (true)
	{
		if (check == start) break;

		check = parent[check._y][check._x];
		_path.push_back(check);
	}
	std::reverse(_path.begin(), _path.end());
}

void Player::Djikstra(Vector2 start)
{
}

bool Player::Cango(int y, int x)
{
	Block::BlockType blockType = _maze->GetBlockType(y,x);
	if(blockType == Block::BlockType::ABLE)
		return true;

	return false;
}

void Player::Update()
{
	if (_pathIndex >= _path.size())
	{
		_pathIndex = 0;
		_path.clear();

		return ;
	}

	_time += 0.03f;
	if (_time > 0.3f)
	{
		_time = 0.0f;
		_pos = _path[_pathIndex];

		if (_pathIndex != 0)
		{
			// 발자취
			_maze->SetPlayerPos(_pos);
		}

		_pathIndex++;
	}
}
