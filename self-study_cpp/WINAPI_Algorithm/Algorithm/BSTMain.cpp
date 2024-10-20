#include <unordered_map>
#include <map>

#include "BinarySearchTree.h"

// �ؽ� ���̺� : �޸𸮸� �ְ� Ž���ð��� ���Ѵ�.
// Ž�� : ���... �ؽ��浹�� ���� ü�̴׿� ���� �޶����� �ִ�.
// ���� : ���
// �浹, ü�̴�

// �ڰ����� Ž��Ʈ��
// Ž�� : logN
// ���� : logN

// �ؽ����̺� vs �ڰ���������Ž��Ʈ��
// �ؽ��Լ� �� �浹�� ���� �Ͼ ��� .. �ڰ���������Ž��Ʈ�� ��
// �浹�� ���� ���... �ؽ����̺� ��

int main()
{
#pragma region BST
	BinarySearchTree bst;

	bst.Insert(50);
	bst.Insert(40);
	bst.Insert(70);
	bst.Insert(30);
	bst.Insert(45);

	bst.PrintTree(bst._root);

	auto searchNode = bst.Search(bst._root, 100);
	if (searchNode != nullptr)
	{
		cout << "�ش��带 ã�ҽ��ϴ�." << endl;
		cout << searchNode->key << endl;
	}
	else
		cout << "�׷� ���� �����ϴ�." << endl;

	auto minNode = bst.Min(bst._root);
	cout << minNode->key << endl;

	auto maxNode = bst.Max(bst._root);
	cout << maxNode->key << endl;

#pragma endregion

	unordered_map<int, int> um;

	um[5] = 1;

	return 0;
}