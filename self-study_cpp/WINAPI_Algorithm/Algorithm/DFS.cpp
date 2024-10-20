#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

// DFS
// ���̿켱 Ž��(Depth-First Search)
// ��� �Լ��� �����Ҽ� �ִ�.

vector<bool> visited;
vector<vector<bool>> adjacent;


void CreateGraph_AdjacentMatrix()
{
	//		0	1	2	3	4	5	6
	//	0	T	T	T	F	T	F	F
	//	1	T	T	F	F	F	F	F
	//	2	
	//	3
	//	4
	//	5
	//	6

	adjacent = vector<vector<bool>>(7, vector<bool>(7, false));

	adjacent[0][0] == true;
	adjacent[0][1] == true;
	adjacent[0][2] == true;
	adjacent[0][4] == true;

	adjacent[1][0] == true;
	adjacent[1][1] == true;

	adjacent[2][0] == true;
	adjacent[2][2] == true;
	adjacent[2][3] == true;
	adjacent[2][5] == true;

	adjacent[3][2] == true;
	adjacent[3][3] == true;

	adjacent[4][0] == true;
	adjacent[4][2] == true;
	adjacent[4][4] == true;
	adjacent[4][6] == true;

	adjacent[5][2] == true;
	adjacent[5][5] == true;

	adjacent[6][4] == true;
	adjacent[6][6] == true;

}

void DFS(int here)
{
	cout << here << "�湮" << endl;
	visited[here] = true;

	for (int there = 0; there < adjacent[0].size(); there++)
	{
		if (adjacent[here][there] == false)
			continue;

		if (visited[there] == true)
			continue;

		DFS(there);
	}
}


int main()
{
	CreateGraph_AdjacentMatrix();
	visited = vector<bool>(adjacent.size(), false);

	DFS(0);

	return 0;
}