#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;


// n <= 100
// r <= 100
vector<vector<int>> cache = vector<vector<int>>(100, vector<int>(100, -1));

int Combination(int n, int r)
{
	if (r == 0 || n == r) return 1;

	if (r == 1) return n;
	
	//메모이제이션
	int& ref = cache[n][r];

	if (ref != -1) return ref;

	// 구하기
	ref = Combination(n - 1, r) + Combination(n - 1, r - 1);

	return ref;
}

int main()
{
	
	//cout << Combination(5, 3) << endl;
	vector<int> v = { 1,2,3,4,5,6,7 };
	 

	// 7p3
	int count = 0;
	while (true)
	{
		// 23
		// 4x3x2x1
		if (std::next_permutation(v.begin(), v.begin() + 4))
		{
			count++;
			cout << v[0] << v[1] << v[2] << v[3] << endl;
		}
		else
		{
			break;
		}
	}



	return 0;
}