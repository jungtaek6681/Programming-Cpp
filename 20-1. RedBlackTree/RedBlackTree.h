#pragma once

#include <cassert>
#include <iostream>
#include <string>

using namespace std;

template <typename T>
struct RedBlackNode
{
	T data;
	RedBlackNode* pParent;
	RedBlackNode* pLeft;
	RedBlackNode* pRight;

	enum class Color { Red, Black };
	Color color;

	bool isRootNode()
	{
		return nullptr == pParent;
	}
	bool isLeftChild()
	{
		if (nullptr != pParent && pParent->pLeft == this)
			return true;
		else
			return false;
	}
	bool isRightChild()
	{
		if (nullptr != pParent && pParent->pRight == this)
			return true;
		else
			return false;
	}
};

template <typename T>
class CRedBlackTree
{
private:
	RedBlackNode<T>* m_pRootNode;
	int m_size;

	void RotateLeft(RedBlackNode<T>* node);
	void RotateRight(RedBlackNode<T>* node);
	void InsertFixUp(RedBlackNode<T>* node);
	void DeleteFixUp(RedBlackNode<T>* node);
	void printNode(int depth, RedBlackNode<T>* node);

public:
	RedBlackNode<T>* m_pLeafNode;

	CRedBlackTree();
	virtual ~CRedBlackTree();

	int size();
	bool empty();
	void clear();

	class iterator
	{
		friend CRedBlackTree;
	private:
		CRedBlackTree<T>* m_pRedBlackTree;
		RedBlackNode<T>* m_pRedBlackNode;

	public:
		iterator();
		iterator(CRedBlackTree<T>* pBST, RedBlackNode<T>* pNode);
		virtual ~iterator();

		T& operator*();

		iterator& operator++();
		iterator operator++(int);
		iterator& operator--();
		iterator operator--(int);

		bool operator==(const iterator& _other);
		bool operator!=(const iterator& _other);
	};

	iterator insert(const T& data);
	int erase(const T& data);
	iterator erase(const iterator& iter);
	iterator find(const T& data);

	iterator begin();
	iterator end();

	void printAll();
};

template<typename T>
void CRedBlackTree<T>::RotateLeft(RedBlackNode<T>* node)
{
	RedBlackNode<T>* rightChild = node->pRight;
	if (nullptr == rightChild)
		assert(0);

	node->pRight = rightChild->pLeft;
	if (nullptr != rightChild->pLeft)
		rightChild->pLeft->pParent = node;
	rightChild->pParent = node->pParent;

	if (node->isRootNode())
		m_pRootNode = rightChild;
	else if (node->isLeftChild())
		node->pParent->pLeft = rightChild;
	else
		node->pParent->pRight = rightChild;

	node->pParent = rightChild;
	rightChild->pLeft = node;
}

template<typename T>
void CRedBlackTree<T>::RotateRight(RedBlackNode<T>* node)
{
	RedBlackNode<T>* leftChild = node->pLeft;
	if (nullptr == leftChild)
		assert(0);

	node->pLeft = leftChild->pRight;
	if (nullptr != leftChild->pRight)
		leftChild->pRight->pParent = node;
	leftChild->pParent = node->pParent;

	if (node->isRootNode())
		m_pRootNode = leftChild;
	else if (node->isLeftChild())
		node->pParent->pLeft = leftChild;
	else
		node->pParent->pRight = leftChild;

	node->pParent = leftChild;
	leftChild->pRight = node;

}

template<typename T>
void CRedBlackTree<T>::InsertFixUp(RedBlackNode<T>* node)
{
	while (node != m_pRootNode && node->pParent->color == RedBlackNode<T>::Color::Red)
	{
		RedBlackNode<T>* parent = node->pParent;
		RedBlackNode<T>* grandParent = parent->pParent;

		// �θ� ���� �ڽ��� ���
		if (parent->isLeftChild())
		{
			RedBlackNode<T>* uncle = grandParent->pRight;
			// 1. ������ �������� ���
			// ���θ� ���������� ������ ���������� ���� ��, ���θ� �������� �ݺ�
			if (nullptr != uncle && uncle->color == RedBlackNode<T>::Color::Red)
			{
				parent->color = RedBlackNode<T>::Color::Black;
				uncle->color = RedBlackNode<T>::Color::Black;
				grandParent->color = RedBlackNode<T>::Color::Red;
				node = grandParent;
			}
			else
			{
				// 2. ������ �������̸� ���� ��尡 ������ �ڽ��� ���
				// �θ� �������� ����ȸ�� ��, ���� ������ ��带 �������� ����
				if (node->isRightChild())
				{
					node = node->pParent;
					RotateLeft(node);
				}

				// 3. ������ �������̸� ���� ��尡 ���� �ڽ��� ��
				// �θ� ���������� ���θ� ���������� ���� ��, ���θ� �������� ���������� ȸ�� �� �ݺ�
				node->pParent->color = RedBlackNode<T>::Color::Black;
				node->pParent->pParent->color = RedBlackNode<T>::Color::Red;
				RotateRight(node->pParent->pParent);
			}
		}
		// �θ� ������ �ڽ��� ���
		else
		{
			RedBlackNode<T>* uncle = grandParent->pLeft;
			// 1. ������ �������� ���
			// ���θ� ���������� ������ ���������� ���� ��, ���θ� �������� �ݺ�
			if (nullptr != uncle && uncle->color == RedBlackNode<T>::Color::Red)
			{
				parent->color = RedBlackNode<T>::Color::Black;
				uncle->color = RedBlackNode<T>::Color::Black;
				grandParent->color = RedBlackNode<T>::Color::Red;
				node = grandParent;
			}
			else
			{
				// 2. ������ �������̸� ���� ��尡 ���� �ڽ��� ��
				// �θ� �������� ������ȸ�� ��, ���� ������ ��带 �������� �ݺ�
				if (node->isLeftChild())
				{
					node = node->pParent;
					RotateRight(node);
				}

				// 3. ������ �������̸� ���� ��尡 ������ �ڽ��� ��
				// �θ� ���������� ���θ� ���������� ���� ��, ���θ� �������� �������� ȸ�� �� �ݺ�
				node->pParent->color = RedBlackNode<T>::Color::Black;
				node->pParent->pParent->color = RedBlackNode<T>::Color::Red;
				RotateLeft(node->pParent->pParent);
			}
		}
	}
	m_pRootNode->color = RedBlackNode<T>::Color::Black;
}

template<typename T>
void CRedBlackTree<T>::DeleteFixUp(RedBlackNode<T>* doubleBlackNode)
{
	while (nullptr != doubleBlackNode->pParent && doubleBlackNode->color == RedBlackNode<T>::Color::Black)
	{
		// ��尡 ���� �ڽ��� ���
		if (doubleBlackNode->isLeftChild())
		{
			RedBlackNode<T>* parent = doubleBlackNode->pParent;
			RedBlackNode<T>* brother = parent->pRight;

			// 1. ������ �������� ���
			// �θ� ���������� ������ ���������� ���� ��, �θ� �������� �������� ȸ�� �� ����
			if (brother->color == RedBlackNode<T>::Color::Red)
			{
				brother->color = RedBlackNode<T>::Color::Black;
				parent->color = RedBlackNode<T>::Color::Red;
				RotateLeft(parent);
				brother = doubleBlackNode->pParent->pRight;
			}

			// 2. ������ �������̸� ������ ���� �ڽ��� ��� �������� ���
			// ������ ���������� �θ� �������̹Ƿ� ���������� ĥ�� �� ������.
			if (brother->pLeft->color == RedBlackNode<T>::Color::Black &&
				brother->pRight->color == RedBlackNode<T>::Color::Black)
			{
				brother->color = RedBlackNode<T>::Color::Red;
				doubleBlackNode = doubleBlackNode->pParent;
			}
			else
			{
				// 3. ������ �������̸� ������ ������ �ڽĸ� �������� ���
				// ������ ���������� ������ ���� �ڽ��� ���������� ���� ��, ������ �������� ���������� ȸ�� �� ����
				if (brother->pRight->color == RedBlackNode<T>::Color::Black)
				{
					brother->pLeft->color = RedBlackNode<T>::Color::Black;
					brother->color = RedBlackNode<T>::Color::Red;
					RotateRight(brother);
					brother = doubleBlackNode->pParent->pRight;
				}

				// 4. ������ �������̸� ������ ���� �ڽĸ� �������� ���
				// ������ �θ������ �θ�� ������ ������ �ڽ��� ���������� ���� ��
				// �θ� �������� ��ȸ���ϰ� ��Ʈ��忡 �������� �ش�.(�ݺ� ����)
				brother->color = doubleBlackNode->pParent->color;
				doubleBlackNode->pParent->color = RedBlackNode<T>::Color::Black;
				brother->pRight->color = RedBlackNode<T>::Color::Black;
				RotateLeft(doubleBlackNode->pParent);
				doubleBlackNode = m_pRootNode;
			}
		}
		// ��尡 ������ �ڽ��� ���
		else
		{
			RedBlackNode<T>* parent = doubleBlackNode->pParent;
			RedBlackNode<T>* brother = parent->pLeft;

			// 1. ������ �������� ���
			// �θ� ���������� ������ ���������� ���� ��, �θ� �������� ���������� ȸ�� �� ����
			if (brother->color == RedBlackNode<T>::Color::Red)
			{
				brother->color = RedBlackNode<T>::Color::Black;
				parent->color = RedBlackNode<T>::Color::Red;
				RotateRight(parent);
				brother = doubleBlackNode->pParent->pLeft;
			}
			// 2. ������ �������̸� ������ ���� �ڽ��� ��� �������� ���
			// ������ ���������� �θ� �������̹Ƿ� ���������� ĥ�� �� ������.
			if (brother->pLeft->color == RedBlackNode<T>::Color::Black &&
				brother->pRight->color == RedBlackNode<T>::Color::Black)
			{
				brother->color = RedBlackNode<T>::Color::Red;
				doubleBlackNode = doubleBlackNode->pParent;
			}
			else
			{
				// 3. ������ �������̸� ������ ���� �ڽĸ� �������� ���
				// ������ ���������� ������ ������ �ڽ��� ���������� ���� ��, ������ �������� �������� ȸ�� �� ����
				if (brother->pRight->color == RedBlackNode<T>::Color::Black)
				{
					brother->pRight->color = RedBlackNode<T>::Color::Black;
					brother->color = RedBlackNode<T>::Color::Red;
					RotateLeft(brother);
					brother = doubleBlackNode->pParent->pLeft;
				}

				// 4. ������ �������̸� ������ ������ �ڽĸ� �������� ���
				// ������ �θ������ �θ�� ������ ���� �ڽ��� ���������� ���� ��
				// �θ� �������� ��ȸ���ϰ� ��Ʈ��忡 �������� �ش�.(�ݺ� ����)
				brother->color = doubleBlackNode->pParent->color;
				doubleBlackNode->pParent->color = RedBlackNode<T>::Color::Black;
				brother->pLeft->color = RedBlackNode<T>::Color::Black;
				RotateRight(doubleBlackNode->pParent);
				doubleBlackNode = m_pRootNode;
			}
		}
	}
	doubleBlackNode->color = RedBlackNode<T>::Color::Black;
	m_pRootNode->color = RedBlackNode<T>::Color::Black;
}

template<typename T>
CRedBlackTree<T>::CRedBlackTree()
{
	m_pLeafNode = new RedBlackNode<T>();
	m_pLeafNode->color = RedBlackNode<T>::Color::Black;
	m_pRootNode = m_pLeafNode;
	m_size = 0;
}

template<typename T>
CRedBlackTree<T>::~CRedBlackTree()
{
	clear();
	delete m_pLeafNode;
}

template<typename T>
int CRedBlackTree<T>::size()
{
	return m_size;
}

template<typename T>
bool CRedBlackTree<T>::empty()
{
	return 0 == m_size;
}

template<typename T>
void CRedBlackTree<T>::clear()
{
	while (!empty())
	{
		erase(begin());
	}
}

template<typename T>
typename CRedBlackTree<T>::iterator CRedBlackTree<T>::insert(const T& data)
{
	RedBlackNode<T>* pNewNode = new RedBlackNode<T>();
	pNewNode->pParent = nullptr;
	pNewNode->pLeft = m_pLeafNode;
	pNewNode->pRight = m_pLeafNode;
	pNewNode->color = RedBlackNode<T>::Color::Red;
	pNewNode->data = data;

	// 1. �����Ͱ� ��� �־��� ��
	if (empty())
	{
		m_pRootNode = pNewNode;
		InsertFixUp(pNewNode);
		m_size++;
		return iterator(this, pNewNode);
	}

	RedBlackNode<T>* pCurrent = m_pRootNode;
	while (true)
	{
		// 2-1. �߰� �ϴ� �����Ͱ� �� ū ���
		if (data > pCurrent->data)
		{
			// 3-1. �����ʿ� ��尡 �ִ� ���, ���������� ����.
			if (m_pLeafNode != pCurrent->pRight)
			{
				pCurrent = pCurrent->pRight;
			}
			// 3-2. �����ʿ� ��尡 ���� ���, �� ��ġ�� �߰�
			else
			{
				pCurrent->pRight = pNewNode;
				pNewNode->pParent = pCurrent;
				break;
			}
		}
		// 2-2. �߰� �ϴ� �����Ͱ� �� ���� ���
		else if (data < pCurrent->data)
		{
			// 3-1. ���ʿ� ��尡 �ִ� ���, �������� ����.
			if (m_pLeafNode != pCurrent->pLeft)
			{
				pCurrent = pCurrent->pLeft;
			}
			// 3-2. ���ʿ� ��尡 ���� ���, �� ��ġ�� �߰�.
			else
			{
				pCurrent->pLeft = pNewNode;
				pNewNode->pParent = pCurrent;
				break;
			}
		}
		// 2-3. �߰� �ϴ� �����Ͱ� ���� ���, ����
		else // (data == pCurrent->data)
		{
			delete pNewNode;
			return iterator(this, pCurrent);
		}
	}

	InsertFixUp(pNewNode);
	m_size++;
	return iterator(this, pNewNode);
}

template<typename T>
int CRedBlackTree<T>::erase(const T& data)
{
	// 1. �����Ͱ� �ϳ��� ���� ���
	if (empty())
		assert(0);

	iterator findIter = find(data);
	if (findIter != end())
		erase(findIter);

	return size();
}

template<typename T>
typename CRedBlackTree<T>::iterator CRedBlackTree<T>::erase(const iterator& iter)
{
	// 1. �����Ͱ� �ϳ��� ���� ���
	if (empty())
		assert(0);

	RedBlackNode<T>* pCurrent = iter.m_pRedBlackNode;
	RedBlackNode<T>* nextNode = m_pLeafNode;
	RedBlackNode<T>* removedNode = m_pLeafNode;
	RedBlackNode<T>* doubleBlackNode = m_pLeafNode;

	typename RedBlackNode<T>::Color color = pCurrent->color;

	if (pCurrent->pLeft == m_pLeafNode || pCurrent->pRight == m_pLeafNode)
	{
		removedNode = pCurrent;
		iterator next = iterator(this, pCurrent);
		next++;
		nextNode = next.m_pRedBlackNode;
	}
	else
	{
		iterator next = iter;
		next++;
		removedNode = next.m_pRedBlackNode;
		pCurrent->data = removedNode->data;
		nextNode = pCurrent;
	}

	if (removedNode->pLeft != m_pLeafNode)
		doubleBlackNode = removedNode->pLeft;
	else
		doubleBlackNode = removedNode->pRight;

	doubleBlackNode->pParent = removedNode->pParent;

	if (nullptr == removedNode->pParent)
		m_pRootNode = doubleBlackNode;
	else
	{
		if (removedNode->isLeftChild())
			removedNode->pParent->pLeft = doubleBlackNode;
		else
			removedNode->pParent->pRight = doubleBlackNode;
	}

	if (removedNode->color == RedBlackNode<T>::Color::Black)
		DeleteFixUp(doubleBlackNode);

	delete removedNode;
	m_size--;
	return iterator(this, nextNode);
}

template<typename T>
typename CRedBlackTree<T>::iterator CRedBlackTree<T>::find(const T& data)
{
	// 1. �����Ͱ� �ϳ��� ���� ���
	if (empty())
		return end();

	RedBlackNode<T>* pCurrent = m_pRootNode;
	while (nullptr != pCurrent)
	{
		// 2-1. ã���� �ϴ� �����Ͱ� �� ū ���, ���������� ����.
		if (data > pCurrent->data)
			pCurrent = pCurrent->pRight;
		// 2-2. ã���� �ϴ� �����Ͱ� �� ���� ���, �������� ����.
		else if (data < pCurrent->data)
			pCurrent = pCurrent->pLeft;
		// 2-3. ã���� �ϴ� �����Ͱ� ���� ���, ã�� ��ġ ��ȯ�ϱ�.
		else // (data == pCurrent->data)
			return iterator(this, pCurrent);
	}

	return end();
}

template<typename T>
typename CRedBlackTree<T>::iterator CRedBlackTree<T>::begin()
{
	if (0 == m_size)
		return end();

	RedBlackNode<T>* pCurrent = m_pRootNode;
	while (m_pLeafNode != pCurrent->pLeft)
	{
		pCurrent = pCurrent->pLeft;
	}
	return iterator(this, pCurrent);
}

template<typename T>
typename CRedBlackTree<T>::iterator CRedBlackTree<T>::end()
{
	return iterator(this, nullptr);
}

template<typename T>
CRedBlackTree<T>::iterator::iterator()
{
	m_pRedBlackTree = nullptr;
	m_pRedBlackNode = nullptr;
}

template<typename T>
CRedBlackTree<T>::iterator::iterator(CRedBlackTree<T>* pRBT, RedBlackNode<T>* pNode)
{
	m_pRedBlackTree = pRBT;
	m_pRedBlackNode = pNode;
}

template<typename T>
CRedBlackTree<T>::iterator::~iterator()
{
	m_pRedBlackTree = nullptr;
	m_pRedBlackNode = nullptr;
}

template<typename T>
T& CRedBlackTree<T>::iterator::operator*()
{
	return m_pRedBlackNode->data;
}

template<typename T>
typename CRedBlackTree<T>::iterator& CRedBlackTree<T>::iterator::operator++()
{
	// 0. ����ó��, �ϳ��� ������ ��, �̹� end() iterator���� ��
	if (this->m_pRedBlackTree->m_pLeafNode == this->m_pRedBlackTree->m_pRootNode || nullptr == m_pRedBlackNode)
	{
		assert(0);
	}

	RedBlackNode<T>* pCurrent = this->m_pRedBlackNode;
	RedBlackNode<T>* leafNode = this->m_pRedBlackTree->m_pLeafNode;
	// 1. ������ �ڽ��� �ִ� ���, ������ �ڽ����� ���� ���� �ڽ��� ���� ������ ������
	// ������ �ڽ��� ���� ���� ���� �翬�� ���� ����̴�.
	if (leafNode != pCurrent->pRight)
	{
		pCurrent = pCurrent->pRight;
		while (true)
		{
			if (leafNode == pCurrent->pLeft)
				break;
			pCurrent = pCurrent->pLeft;
		}
		this->m_pRedBlackNode = pCurrent;
		return *this;
	}
	// 2. ������ �ڽ��� ���� ���, �θ�� �����ϴµ� ���� �ڽ��� ������ ���� ��.
	// ���� ���� ���� �������� ���� ��尡 �� ��������.
	else   // nullptr == pCurrent->pRight;
	{
		while (true)
		{
			// ��� ���� �ö󰬴µ� �θ� ���������� �ö󰬴� == ó�� ��尡 ���� ū(������) Node����.
			if (nullptr == pCurrent->pParent)
			{
				this->m_pRedBlackNode = nullptr;
				return *this;
			}
			if (pCurrent->isLeftChild())
			{
				// �̶� �θ� �ڽ��� ���� Node
				this->m_pRedBlackNode = pCurrent->pParent;
				return *this;
			}
			pCurrent = pCurrent->pParent;
		}
	}
}

template<typename T>
typename CRedBlackTree<T>::iterator CRedBlackTree<T>::iterator::operator++(int)
{
	iterator temp(*this);
	++(*this);
	return temp;
}

template<typename T>
typename CRedBlackTree<T>::iterator& CRedBlackTree<T>::iterator::operator--()
{
	// 0. ����ó��, �ϳ��� ������ ��, �̹� begin() iterator���� ��
	if (nullptr == this->m_pMyBST->m_pRootNode || this->m_pMyBST->begin() == this)
	{
		assert(nullptr);
	}

	RedBlackNode<T>* pCurrent = this->m_pRedBlackNode;
	RedBlackNode<T>* leafNode = this->m_pRedBlackTree->m_pLeafNode;

	// 0. end() iterator ���� ��
	if (nullptr == this->m_pRedBlackNode)   // this->m_pMYBST->end() == this
	{
		RedBlackNode<T>* pCurrent = this->m_pMyBST->m_pRootNode;
		while (true)
		{
			if (leafNode == pCurrent->pRight)
				break;
			pCurrent = pCurrent->pRight;
		}
		return iterator(this, pCurrent);
	}

	RedBlackNode<T>* pCurrent = this->m_pRedBlackNode;
	// 1. ���� �ڽ��� �ִ� ���, ���� �ڽ����� ���� ������ �ڽ��� ���� ������ ������
	// ���� �ڽ��� ���� ū ���� �翬�� ���� ����̴�.
	if (leafNode != pCurrent->pLeft)
	{
		pCurrent = pCurrent->pLeft;
		while (true)
		{
			if (leafNode == pCurrent->pRight)
				break;
			pCurrent = pCurrent->pRight;
		}
		this->m_pRedBlackNode = pCurrent;
		return *this;
	}
	// 2. ���� �ڽ��� ���� ���, �θ�� �����ϴµ� ������ �ڽ��� ������ ���� ��.
	// ���� ���� ���� ���������� ���� ��尡 �� ���� ����.
	else   // nullptr == pCurrent->pRight;
	{
		while (true)
		{
			// ��� ���� �ö󰬴µ� �θ� ���������� �ö󰬴� == ó�� ��尡 ���� ����(ó��) Node����.
			if (nullptr == pCurrent->pParent)
			{
				assert(nullptr);
			}
			if (pCurrent->isRightChild() == pCurrent)
			{
				// �̶� �θ� �ڽ��� ���� Node
				this->m_pRedBlackNode = pCurrent->pParent;
				return *this;
			}
			pCurrent = pCurrent->pParent;
		}
	}
}

template<typename T>
typename CRedBlackTree<T>::iterator CRedBlackTree<T>::iterator::operator--(int)
{
	iterator temp(*this);
	--(*this);
	return temp;
}

template<typename T>
bool CRedBlackTree<T>::iterator::operator==(const iterator& _other)
{
	if (this->m_pRedBlackNode == _other.m_pRedBlackNode &&
		this->m_pRedBlackTree == _other.m_pRedBlackTree)
		return true;
	return false;
}

template<typename T>
bool CRedBlackTree<T>::iterator::operator!=(const iterator& _other)
{
	return !(*this == _other);
}

template <typename T>
void CRedBlackTree<T>::printNode(int depth, RedBlackNode<T>* node)
{
	int i = 0;
	char c = 'X';
	T v = -1;
	string cnt;

	if (nullptr == node || m_pLeafNode == node)
		return;

	if (node->pParent != nullptr)
	{
		v = node->pParent->data;

		if (node->isLeftChild())
			c = 'L';
		else
			c = 'R';
	}

	for (int i = 0; i < depth; i++) cout << "  ";

	cout << node->data << " ";
	if (node->color == RedBlackNode<T>::Color::Red) cout << "Red";
	else cout << "Black";
	cout << " " << c << " " << v << " " << endl;

	printNode(depth + 1, node->pLeft);
	printNode(depth + 1, node->pRight);
}

template <typename T>
void CRedBlackTree<T>::printAll()
{
	printNode(0, m_pRootNode);
	cout << endl << endl;
}