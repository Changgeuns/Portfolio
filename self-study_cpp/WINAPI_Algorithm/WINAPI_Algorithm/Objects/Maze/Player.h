#pragma once

class Maze;
class Block;

class Player
{
public:
	Player(shared_ptr<Maze> maze);
	~Player();

	void BeginPlay();

	//void FindPath();
	void RightHand();
	void DFS(Vector2 start);
	void BFS(Vector2 start);
	void Djikstra(Vector2 start);

	bool Cango(int y, int x);

	void Update();

private:
	Vector2 _pos = {1,1};

	vector<Vector2> _path;
	int _pathIndex = 0;
	float  _time = 0.0f;

	Vector2 _dir = Vector2(0, 1);

	shared_ptr<Maze> _maze;
};

