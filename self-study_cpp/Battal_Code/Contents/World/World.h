#pragma once
class World
{
public:
	enum PlayerType
	{
		NONE = 0,
		KNIGHT = 1,
		ARCHER = 2
	};

	World();
	~World();
	void Init();

	bool End();
	bool MonstersCheck();

	void Battle1();
	void Battle2();

private:
	void SelectPlayer(int num, string name, Creature** creature);
	void Input();

	shared_ptr<Creature> _player;
	shared_ptr<Creature> _computer;
	vector<shared_ptr<Creature>> _monsters;
};

