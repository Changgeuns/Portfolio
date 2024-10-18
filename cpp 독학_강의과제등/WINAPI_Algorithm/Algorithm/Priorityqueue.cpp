#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>
#include <concurrent_priority_queue.h>

using namespace std;

// �켱���� ť
// 1. ��������Ʈ��
// 2. �θ� �׻� �ڽĺ���ũ�� (�ִ���)
template<typename T, typename Container = vector<T>, typename Pred>
class Priority_queue
{
public:
	void push(const int& value)
	{
		/*_container.push_back(value);

		std::sort(_container.begin(), _container.end(), [](int a, int b) {
			return a > b;
			});*/

		_container.push_back(value);

		int now = _container.size() - 1;

		while (true)
		{
			if (now <= 0) break;

			int parent = (now - 1) / 2;
			if (_container[parent] > _container[now]) break;


			// �ڽ��� �θ𺸴� ū ���
			std::swap(_container[now], _container[parent]);
			now = parent;
		}

	}

	void pop()
	{
		//if (!_container.empty())
		//{
		//	_container.erase(_container.begin());
		//}

		_container[0] = _container.back();
		_container.pop_back();

		int now = 0;

		while (true)
		{
			int leftChild = now * 2 + 1;
			int rightChild = now * 2 + 2; //(now + 1) * 2; 

			// �ڽ��� ���� ��Ȳ
			if (leftChild >= (int)_container.size())
			{
				break;
			}

			// leftChild, rightChild�� ���ϸ鼭 ���� �� ū������ Ȯ��
			int next = now;
			if (_container[next] < _container[leftChild])
			{
				next = leftChild;
			}

			// rightChild�� ��ȿ���� Ȯ��
			if (rightChild < (int)_container.size() && _container[next] < _container[rightChild])
			{
				next = rightChild;
			}

			if (next == now) break;

			std::swap(_container[now], _container[next]);
			now = next;

		}
	}

	const T& top()
	{
		if (!_container.empty())
		{
			// ���� ū ���� ��ȯ
			return _container.front();
		}
		
		return 0;
	}

	bool empty()
	{
		if (_container.size() == 0) return true;

		return false;
	}

private:
	Container<int> _container;
};

int main()
{
	priority_queue<int, vector<int>, greater<int>> pq;
	//Priority_queue pq;

	pq.push(5);
	pq.push(10);
	pq.push(50);
	pq.push(100);
	pq.push(1);
	pq.push(2);
	pq.push(4);

	// N������ N��ŭ�� �����ϰ� �ʹ�.
	// => priority_sort => M * logN
	while (true)
	{
		if (pq.empty()) break;

		int top = pq.top();
		cout << top << endl;

		pq.pop();
	}


	return 0;
}