#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>
#include <concurrent_priority_queue.h>

using namespace std;

// 우선순위 큐
// 1. 완전이진트리
// 2. 부모가 항상 자식보다크다 (최대힙)
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


			// 자식이 부모보다 큰 경우
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

			// 자식이 없는 상황
			if (leftChild >= (int)_container.size())
			{
				break;
			}

			// leftChild, rightChild와 비교하면서 누가 더 큰수인지 확인
			int next = now;
			if (_container[next] < _container[leftChild])
			{
				next = leftChild;
			}

			// rightChild가 유효한지 확인
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
			// 가장 큰 값을 반환
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

	// N개에서 N만큼만 정렬하고 싶다.
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