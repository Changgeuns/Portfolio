#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

// queue : �� ����� ( ���ӿ��� ť ������)
// First input First Out 

template <typename T, typename Container = list<T>>
class Queue
{
public:
	void push(const T& a)
	{
		container.push_back(a);
	}
	void pop()
	{
		container.pop_front();
	}
	bool empty()
	{
		return container.size() == 0;
	}
	const T& front()
	{
		return container.front();
	}
	

private:
	Container container;
};


int main()
{
	queue<int, list<int>> q;

	q.push(51);
	q.push(2);
	q.push(3);
	q.push(23);
	q.push(77);

	while (true)
	{
		if (q.empty() == true)
			break;

		cout << q.front() << endl;
		q.pop();
	}

	return 0;
}