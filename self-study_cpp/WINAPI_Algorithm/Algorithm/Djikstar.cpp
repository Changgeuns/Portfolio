#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

struct Vertex
{
    Vertex(int vertexNum, int g) : vertextNum(vertexNum), g(g) {}


    int vertextNum = 0;
    int g = 0; // ����ġ

    bool operator<(const Vertex& other) const
    {
        if (g < other.g) return true;
        return false;
    }

    bool operator>(const Vertex& other) const
    {
        if (g > other.g) return true;
        return false;
    }
};

vector<vector<int>> adjacent;
vector<bool> discovered;
vector<int> parent;

void CreateGraph_AdjacentMatrix()
{


    adjacent = vector<vector<int>>(7, vector<int>(7, -1));

    adjacent[0][0] = 0;
    adjacent[0][1] = 3;
    adjacent[0][2] = 2;
    adjacent[0][4] = 10;

    adjacent[1][0] = 3;
    adjacent[1][1] = 0;

    adjacent[2][0] = 2;
    adjacent[2][2] = 0;
    adjacent[2][3] = 7;
    adjacent[2][4] = 3;
    adjacent[2][5] = 5;

    adjacent[3][2] = 7;
    adjacent[3][3] = 0;

    adjacent[4][0] = 10;
    adjacent[4][2] = 3;
    adjacent[4][4] = 0;
    adjacent[4][6] = 4;

    adjacent[5][2] = 5;
    adjacent[5][5] = 0;

    adjacent[6][4] = 4;
    adjacent[6][6] = 0;


}

void Djikstra(int start)
{
    parent = vector<int>(adjacent.size(), -1); 
    vector<int> best(adjacent.size(), INT_MAX);
    priority_queue<Vertex, vector<Vertex>, greater<Vertex>> pq;

    Vertex startV = Vertex(0, 0);
    best[start] = 0;
    pq.push(startV);

    //discovered[start] = true; // ���� ��� ��
    parent[start] = start;

    while (true)
    {
        if (pq.empty()) break;

        Vertex hereV = pq.top();
        pq.pop();

        // ���� �߰��� ���� �� ���� ��ο��� ��
        if (best[hereV.vertextNum] < hereV.g)
        {
            cout << hereV.vertextNum << endl;
            cout << hereV.g << endl;
            cout << best[hereV.vertextNum] << endl;
            continue;
        }

        for (int there = 0; there < adjacent.size(); there++)
        {
            if (hereV.vertextNum == there) continue;

            if (adjacent[hereV.vertextNum][there] == -1) continue;

            // ���� ���� ��ġ�� best �� + there������ ������ ����
            int newCost = best[hereV.vertextNum] + adjacent[hereV.vertextNum][there];
            
            // ������ �߰��� ���� best�� �� �۾����� pq�� ����x
            if (newCost >= best[there]) continue;

            Vertex thereV = Vertex(there, newCost);
            pq.push(thereV);
            best[there] = newCost;
            parent[there] = hereV.vertextNum;

        }

    }


    for (int i = 0; i < adjacent.size(); i++)
    {
        cout << i << "�� �θ� : " << parent[i] << endl;
        cout << "0���� " << i << " ������ �ּ� cost : " << best[i] << endl;
    }
}

int main()
{
    CreateGraph_AdjacentMatrix();
    Djikstra(0);

  

    return 0;
}