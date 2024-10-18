#include "BinarySearchTree.h"

BinarySearchTree::~BinarySearchTree()
{
	// TODE : ��带 ������ �ӽÃ�
}

void BinarySearchTree::Insert(int key)
{
	Node* newNode = new Node(key);

	if (_root == nullptr)
	{
		_root = newNode;
		return;
	}


	Node* node = _root;
	Node* parent = nullptr;

	// �ڸ�ã��, �θ� ã��
	while (true)
	{
		if (node == nullptr)
			break;

		parent = node;
		if (key < node->key)
		{
			node = node->left;
		}
		else
		{
			node = node->right;
		}
	}

	newNode->parent = parent;
	if (key < parent->key)
	{
		parent->left = newNode;
	}
	else
	{
		parent->right = newNode;
	}
}

void BinarySearchTree::PrintTree(Node* node)
{
	if (node == nullptr) return;

	// Tree�� ������ȸ : �θ� - ���� �ڽĵ�(���ѹݺ�..) - ������ �ڽĵ�
	// Tree�� ������ȸ : ���� �ڽĵ� - �θ� - ������ �ڽĵ�
	// Tree �� ������ȸ : ���� �ڽĵ� - ������ �ڽĵ� - �θ�
	cout << node->key << endl;
	PrintTree(node->left);
	PrintTree(node->right);
}

Node* BinarySearchTree::Search(Node* node, int key)
{
	//if (node->left == nullptr || node->right == nullptr) return;
	//if (node->key < key)
	//{
	//	cout << "�·��Ѻ�" << endl;
	//	Search(node->left, key);
	//}
	//else
	//{
	//	cout << "��� �Ѻ�" << endl;
	//
	//	Search(node->right, key);
	//}
	//if (node->key == key)
	//{
	//	cout << "ã�Ҽ�" << endl;
	//	return node;
	//}

	if (node == nullptr) return nullptr;

	if (key == node->key) return node;

	if (key < node->key) return Search(node->left, key);
	else return Search(node->right, key);

	return nullptr;

}

Node* BinarySearchTree::Min(Node* node)	
{
	/*if (node->left == nullptr)
	{
		cout << node->key << endl;
		return node;
	}
	Min(node->left);*/

	if (node == nullptr) return nullptr;

	if (node->left != nullptr) return Min(node->left);

	return node;
}

Node* BinarySearchTree::Max(Node* node)
{
	/*if (node->right == nullptr)
	{
		cout << node->key << endl;
		return node;
	}
	Max(node->right);*/

	if (node == nullptr) return nullptr;

	if (node->right != nullptr) return Max(node->right);

	return node;
}

Node* BinarySearchTree::Previous(Node* node)
{
	if (node == nullptr) return nullptr;

	if (node->left == nullptr) return node;

	return Max(node->left);
}

Node* BinarySearchTree::Next(Node* node)
{
	if (node == nullptr) return nullptr;

	if (node->right == nullptr) return node;

	return Min(node->right);
}

void BinarySearchTree::Delete(Node* node)
{
	if (node == nullptr) return;

	if (node->left == nullptr)
	{
		Replace(node, node->right);
	}
	else if (node->right == nullptr)
	{
		Replace(node, node->left);
	}
	else
	{
		Node* prev = Previous(node);
		node->key = prev->key;
		node->data = prev->data;

		Delete(prev);
	}

}

void BinarySearchTree::Replace(Node* node1, Node* node2)
{
	if (node1->parent == nullptr) _root = node2;

	else if (node1 == node1->parent->left)
	{
		node1->parent->left = node2;
	}
	else
	{
		node1->parent->right = node2;
	}

	if (node2 != nullptr)
		node2->parent = node1->parent;

	delete node1;
}
