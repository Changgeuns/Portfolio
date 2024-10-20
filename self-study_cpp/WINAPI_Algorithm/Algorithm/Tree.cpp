#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

// - �����ڷ��� : vector, list, stack, queue
// - �����ڷ��� : graph, tree

// tree
// 1. ���������� ǥ���� �� ���� ���δ�.
// -> �θ���� �ڽĳ�尡 ���� �̾����ִ�.
// -> Root Node : �ֻ��� �θ� -> ��� Ʈ������ ������ ���ϳ��� ��Ʈ��尡 �ִ�.
// -> Leaf Node : ������ �ڽ�
// 2. Ʈ���� �߶� Ʈ����.
// -> ����Ʈ��
// => ��������� �ڽ��� Ÿ��� �� �ִ�.

// Ʈ���� ����
// 1. ����Ʈ��
// 2. ��ȭ����Ʈ��
// 3. ��������Ʈ��
// 4. ����Ž��Ʈ��
// 5. ��Ʈ��
// 6. �ڰ��������� Ž��Ʈ��

struct Node
{
	Node();
	Node(const string& data) : _data(data) {}

	vector<Node*> _children;
	string _data;
};

Node* CreateTree()
{
	Node* root = new Node("���ߺ�");
	{
		Node* node1 = new Node("���α׷�����");
		root->_children.push_back(node1);
		{
			Node* _node1 = new Node("�������α׷���");
			node1->_children.push_back(_node1);

			Node* _node2 = new Node("Ŭ���̾�Ʈ���α׷���");
			node1->_children.push_back(_node2);

			Node* _node3 = new Node("�������α׷���");
			node1->_children.push_back(_node3);
		}

		Node* node2 = new Node("��ȹ��");
		root->_children.push_back(node2);
		{
			Node* _node1 = new Node("����������");
			node2->_children.push_back(_node1);

			Node* _node2 = new Node("���丮");
			node2->_children.push_back(_node2);

			Node* _node3 = new Node("�ý��� ��ȹ");
			node2->_children.push_back(_node3);
		}

		Node* node3 = new Node("��Ʈ��");
		root->_children.push_back(node3);
		{
			Node* _node1 = new Node("���");
			node3->_children.push_back(_node1);

			Node* _node2 = new Node("�𵨸�");
			node3->_children.push_back(_node2);

			Node* _node3 = new Node("�Ϸ���Ʈ");
			node3->_children.push_back(_node3);
		}
	}

	return root;
}

void PrintTree(Node* node, int depth)
{
	for (int i = 0; i < depth; i++)
	{
		cout << " - ";
	}

	cout << node->_data << endl;

	// Ʈ���� ���ȣ��� ��ȸ�ϴ� ���
	for (auto child : node->_children)
	{
		PrintTree(child, depth + 1);
	}
}


int main()
{
	Node* root = CreateTree();
	PrintTree(root, 0);

	return 0;
}