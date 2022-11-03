#pragma once
#include <cassert>

template <typename T>
struct BinaryNode
{
	T data;
	BinaryNode* pParent;
	BinaryNode* pLeft;
	BinaryNode* pRight;

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

	bool hasNoChild()
	{
		return nullptr == pLeft && nullptr == pRight;
	}
	bool hasLeftChild()
	{
		return nullptr != pLeft && nullptr == pRight;
	}
	bool hasRightChild()
	{
		return nullptr == pLeft && nullptr != pRight;
	}
	bool hasBothChild()
	{
		return nullptr != pLeft && nullptr != pRight;
	}
};

template <typename T>
class CBinarySearchTree
{
private:
	BinaryNode<T>* m_pRootNode;
	int m_size;

public:
	CBinarySearchTree();
	virtual ~CBinarySearchTree();
	int size();
	bool empty();
	void clear();

	class iterator
	{
		friend CBinarySearchTree;
	private:
		CBinarySearchTree<T>* m_pBST;
		BinaryNode<T>* m_pBinaryNode;

	public:
		iterator();
		iterator(CBinarySearchTree<T>* pBST, BinaryNode<T>* pNode);
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
};

template<typename T>
CBinarySearchTree<T>::CBinarySearchTree()
{
	m_pRootNode = nullptr;
	m_size = 0;
}

template<typename T>
CBinarySearchTree<T>::~CBinarySearchTree()
{
	clear();
}

template<typename T>
int CBinarySearchTree<T>::size()
{
	return m_size;
}

template<typename T>
bool CBinarySearchTree<T>::empty()
{
	return 0 == m_size;
}

template<typename T>
void CBinarySearchTree<T>::clear()
{
	while (!empty())
	{
		erase(begin());
	}
}

template<typename T>
typename CBinarySearchTree<T>::iterator CBinarySearchTree<T>::insert(const T& data)
{
	BinaryNode<T>* pNewNode = new BinaryNode<T>();
	pNewNode->data = data;

	// 1. �����Ͱ� ��� �־��� ��
	if (empty())
	{
		m_pRootNode = pNewNode;
		m_size++;
		return iterator(this, pNewNode);
	}

	BinaryNode<T>* pCurrent = m_pRootNode;
	while (true)
	{
		// 2-1. �߰� �ϴ� �����Ͱ� �� ū ���
		if (data > pCurrent->data)
		{
			// 3-1. �����ʿ� ��尡 �ִ� ���, ���������� ����.
			if (nullptr != pCurrent->pRight)
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
			if (nullptr != pCurrent->pLeft)
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

	m_size++;
	return iterator(this, pNewNode);
}

template<typename T>
int CBinarySearchTree<T>::erase(const T& data)
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
typename CBinarySearchTree<T>::iterator CBinarySearchTree<T>::erase(const iterator& iter)
{
	// 1. �����Ͱ� �ϳ��� ���� ���
	if (empty())
		assert(0);

	BinaryNode<T>* pCurrent = iter.m_pBinaryNode;

	// 2-1. �ڽ� ��尡 ���� ���, �׳� ��带 �����.
	if (pCurrent->hasNoChild())
	{
		iterator next = iter;
		next++;

		if (pCurrent->isLeftChild())
			pCurrent->pParent->pLeft = nullptr;
		else if (pCurrent->isRightChild())
			pCurrent->pParent->pRight = nullptr;
		else //(pCurrent->isRootNode())
			m_pRootNode = nullptr;

		m_size--;
		delete pCurrent;
		return next;
	}
	// 2-2. �ڽ� ��尡 �ϳ��� ���, �ڽ��� �ڱ� ��ġ�� �ű��.
	else if (pCurrent->hasLeftChild())
	{
		BinaryNode<T>* parentNode = pCurrent->pParent;
		BinaryNode<T>* childNode = pCurrent->pLeft;

		iterator next = iter;
		next++;
		if (pCurrent->isLeftChild())
		{
			// �θ� ����� ������ ���� ��忡 ����
			parentNode->pLeft = childNode;
			// ���� ����� ������ �θ� ��忡 ����
			childNode->pParent = parentNode;
		}
		else if (pCurrent->isRightChild())
		{
			// �θ� ����� ������ ���� ��忡 ����
			parentNode->pRight = childNode;
			// ���� ����� ������ �θ� ��忡 ����
			childNode->pParent = parentNode;
		}
		else // (pCurrent->isRootNode())
		{
			// ��Ʈ ��带 ���� ���� ����
			m_pRootNode = childNode;
			// ���� ����� ������ ����
			childNode->pParent = nullptr;
		}

		m_size--;
		delete pCurrent;
		return next;
	}
	else if (pCurrent->hasRightChild())
	{
		BinaryNode<T>* parentNode = pCurrent->pParent;
		BinaryNode<T>* childNode = pCurrent->pRight;

		iterator next = iter;
		next++;
		if (pCurrent->isLeftChild())
		{
			// �θ� ����� ������ ���� ��忡 ����
			parentNode->pLeft = childNode;
			// ���� ����� ������ �θ� ��忡 ����
			childNode->pParent = parentNode;
		}
		else if (pCurrent->isRightChild())
		{
			// �θ� ����� ������ ���� ��忡 ����
			parentNode->pRight = childNode;
			// ���� ����� ������ �θ� ��忡 ����
			childNode->pParent = parentNode;
		}
		else // (pCurrent->isRootNode())
		{
			// ��Ʈ ��带 ���� ���� ����
			m_pRootNode = childNode;
			// ���� ����� ������ ����
			childNode->pParent = nullptr;
		}

		m_size--;
		delete pCurrent;
		return next;
	}
	// 2-3. �ڽ� ��尡 ���� ���, ������ȸ���� �� ��峪 �� ��带 �ڱ� ��ġ�� �ű��.
	else // (hasBothChild())
	{
		iterator next = iter;
		next++;
		pCurrent->data = next.m_pBinaryNode->data;
		erase(next);

		return iterator(this, pCurrent);
	}
}

template<typename T>
typename CBinarySearchTree<T>::iterator CBinarySearchTree<T>::find(const T& data)
{
	// 1. �����Ͱ� �ϳ��� ���� ���
	if (empty())
		return end();

	BinaryNode<T>* pCurrent = m_pRootNode;
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
typename CBinarySearchTree<T>::iterator CBinarySearchTree<T>::begin()
{
	if (0 == m_size)
		return end();

	BinaryNode<T>* pCurrent = m_pRootNode;
	while (nullptr != pCurrent->pLeft)
	{
		pCurrent = pCurrent->pLeft;
	}
	return iterator(this, pCurrent);
}

template<typename T>
typename CBinarySearchTree<T>::iterator CBinarySearchTree<T>::end()
{
	return iterator(this, nullptr);
}

template<typename T>
CBinarySearchTree<T>::iterator::iterator()
{
	m_pBST = nullptr;
	m_pBinaryNode = nullptr;
}

template<typename T>
CBinarySearchTree<T>::iterator::iterator(CBinarySearchTree<T>* pBST, BinaryNode<T>* pNode)
{
	m_pBST = pBST;
	m_pBinaryNode = pNode;
}

template<typename T>
CBinarySearchTree<T>::iterator::~iterator()
{
	m_pBST = nullptr;
	m_pBinaryNode = nullptr;
}

template<typename T>
T& CBinarySearchTree<T>::iterator::operator*()
{
	return m_pBinaryNode->data;
}

template<typename T>
typename CBinarySearchTree<T>::iterator& CBinarySearchTree<T>::iterator::operator++()
{
	// 0. ����ó��, �ϳ��� ������ ��, �̹� end() iterator���� ��
	if (nullptr == this->m_pBST->m_pRootNode || nullptr == m_pBinaryNode)
	{
		assert(nullptr);
	}

	BinaryNode<T>* pCurrent = this->m_pBinaryNode;
	// 1. ������ �ڽ��� �ִ� ���, ������ �ڽ����� ���� ���� �ڽ��� ���� ������ ������
	// ������ �ڽ��� ���� ���� ���� �翬�� ���� ����̴�.
	if (nullptr != pCurrent->pRight)
	{
		pCurrent = pCurrent->pRight;
		while (true)
		{
			if (nullptr == pCurrent->pLeft)
				break;
			pCurrent = pCurrent->pLeft;
		}
		this->m_pBinaryNode = pCurrent;
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
				this->m_pBinaryNode = nullptr;
				return *this;
			}
			if (pCurrent->isLeftChild())
			{
				// �̶� �θ� �ڽ��� ���� Node
				this->m_pBinaryNode = pCurrent->pParent;
				return *this;
			}
			pCurrent = pCurrent->pParent;
		}
	}
}

template<typename T>
typename CBinarySearchTree<T>::iterator CBinarySearchTree<T>::iterator::operator++(int)
{
	iterator temp(*this);
	++(*this);
	return temp;
}

template<typename T>
typename CBinarySearchTree<T>::iterator& CBinarySearchTree<T>::iterator::operator--()
{
	// 0. ����ó��, �ϳ��� ������ ��, �̹� begin() iterator���� ��
	if (nullptr == this->m_pMyBST->m_pRootNode || this->m_pMyBST->begin() == this)
	{
		assert(nullptr);
	}

	// 0. end() iterator ���� ��
	if (nullptr == this->m_pBinaryNode)	// this->m_pMYBST->end() == this
	{
		BinaryNode<T>* pCurrent = this->m_pMyBST->m_pRootNode;
		while (true)
		{
			if (nullptr == pCurrent->pRight)
				break;
			pCurrent = pCurrent->pRight;
		}
		return iterator(this, pCurrent);
	}

	BinaryNode<T>* pCurrent = this->m_pBinaryNode;
	// 1. ���� �ڽ��� �ִ� ���, ���� �ڽ����� ���� ������ �ڽ��� ���� ������ ������
	// ���� �ڽ��� ���� ū ���� �翬�� ���� ����̴�.
	if (nullptr != pCurrent->pLeft)
	{
		pCurrent = pCurrent->pLeft;
		while (true)
		{
			if (nullptr == pCurrent->pRight)
				break;
			pCurrent = pCurrent->pRight;
		}
		this->m_pBinaryNode = pCurrent;
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
				this->m_pBinaryNode = pCurrent->pParent;
				return *this;
			}
			pCurrent = pCurrent->pParent;
		}
	}
}

template<typename T>
typename CBinarySearchTree<T>::iterator CBinarySearchTree<T>::iterator::operator--(int)
{
	iterator temp(*this);
	--(*this);
	return temp;
}

template<typename T>
bool CBinarySearchTree<T>::iterator::operator==(const iterator& _other)
{
	if (this->m_pBinaryNode == _other.m_pBinaryNode &&
		this->m_pBST == _other.m_pBST)
		return true;
	return false;
}

template<typename T>
bool CBinarySearchTree<T>::iterator::operator!=(const iterator& _other)
{
	return !(*this == _other);
}