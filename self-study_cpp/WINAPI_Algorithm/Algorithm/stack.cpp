#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>

using namespace std;

// stack : 팬케이크
// FILO : First input Last Out

//template <typename T, typename Container = vector<int>>
class Stack
{
public:
	void Push(int a)
	{
		stack.push_back(a);
	}
	void Pop()
	{
		stack.pop_back();
	}
	const int& Top()
	{
		return stack.back();
	}
	bool Empty()
	{
		return stack.size() == 0;
	}

private:
	vector<int> stack;
};


int main()
{
	stack s;

	s.Push(1);
	s.Push(3);
	s.Push(5);
	s.Push(7);
	s.Push(9);


	while (true)
	{
		if (s.Empty())
			break;

		cout << s.Top() << endl;
		s.Pop();


	}

	return 0;
}

