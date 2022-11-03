#pragma once

#include <cassert>

template <typename T>
struct Node
{
	T			m_data;
	Node<T>* pPrev;
	Node<T>* pNext;
};

template <typename T>
class CLinkedList
{
private:
	Node<T>* pHeadNode;
	Node<T>* pTailNode;
	unsigned int m_size;

public:
	CLinkedList();
	virtual ~CLinkedList();

	void push_front(const T& data);
	void pop_front();
	void push_back(const T& data);
	void pop_back();

	int size();
	bool empty();
	void clear();

	class iterator
	{
		friend CLinkedList;
	private:
		CLinkedList*	m_pLinkedList;
		Node<T>*		m_pNode;

	public:
		iterator();
		iterator(CLinkedList* pLinkedList, Node<T>* pNode);
		virtual ~iterator();

		// 1. ���� (*) : �ݺ��ڰ� ����Ű�� ������ ������ ��������
		T& operator*();

		// 2. �̵� (++, --, +=, -=) : �ݺ��ڰ� ����Ű�� �ִ� ������ ���� ���ҳ� ���� ���Ҹ� ����Ŵ
		iterator& operator++();		// ���� : ++iter
		iterator  operator++(int);	// ���� : iter++
		iterator& operator--();		// ���� : --iter
		iterator  operator--(int);	// ���� : iter--
		iterator& operator+=(int);
		iterator& operator-=(int);

		// 3. �� (==, !=): �ݺ��ڰ� �ٸ� �ݺ��ڿ� ������ ���Ҹ� ����Ű�� �ִ°� �ƴѰ��� ���ؼ� �Ǵ�
		bool operator==(const iterator& other);
		bool operator!=(const iterator& other);
	};

	// 4. ��ȸ (begin(), end()): �ݺ��ڰ� �ڷᱸ���� ó������ ������ �ѹ��� ���� �־�� ��
	iterator begin();		// ���� iterator
	iterator end();			// �� iterator

	iterator insert(iterator iter, const T& value);
	iterator erase(iterator iter);
};

template <typename T>
CLinkedList<T>::CLinkedList()
{
	pHeadNode = nullptr;
	pTailNode = nullptr;
	m_size = 0;
}

template <typename T>
CLinkedList<T>::~CLinkedList()
{
	clear();
}

template <typename T>
void CLinkedList<T>::push_front(const T& data)
{
	if (m_size > 0)
	{
		// 1. ���ο� ��带 �����.
		Node<T>* newNode = new Node<T>();
		// 2. ��忡 ������ �ֱ�
		newNode->m_data = data;
		// 3. ���ο� ����� ���� �����͸� ó�� ���� �����Ѵ�.
		newNode->pNext = pHeadNode;
		// 4. ó�� ����� ���� �����͸� ���ο� ���� �����Ѵ�.
		pHeadNode->pPrev = newNode;
		// 5. ó�� ��带 ���ο� ���� �����Ѵ�.
		pHeadNode = newNode;
	}
	else
	{
		// 1 .���ο� ��带 �����.
		Node<T>* newNode = new Node<T>();
		// 2. ��忡 ������ �ֱ�
		newNode->m_data = data;
		// 3. ó�� ��带 ���ο� ���� �������ش�.
		pHeadNode = newNode;
		// 4. ������ ��嵵 ���ο� ���� �������ش�.
		pTailNode = newNode;
	}

	m_size++;
}

template <typename T>
void CLinkedList<T>::pop_front()
{
	if (0 == m_size)
	{
		// assert(0); // ���µ� ���� ���� ������� �Ǵ�
		return;	// ���µ� ���� ���� �����϶�� �Ǵ�
	}
	else if (1 == m_size)
	{
		// 1. ����� ���� ���� ����� �ּҸ� ��� ����
		Node<T>* deleteNode = pHeadNode;
		// 2. ó����带 nullptr ����.
		pHeadNode = nullptr;
		// 3. ��������带 nullptr ����.
		pTailNode = nullptr;
		// 4. ���� ��带 ����
		delete deleteNode;
	}
	else
	{
		// 1. ����� ���� ���� ����� �ּҸ� ��� ����
		Node<T>* deleteNode = pHeadNode;
		// 2 .ó����带 ���� ����� ���� ���� ������
		pHeadNode = deleteNode->pNext;
		// 3. ó���� �� ����� ���� �����͸�  Nullptr ����
		pHeadNode->pPrev = nullptr;
		// 4. �����带 ����
		delete deleteNode;
	}


	m_size--;
}

template <typename T>
void CLinkedList<T>::push_back(const T& data)
{
	if (m_size > 0)
	{
		// 1. ���ο� ��� ����
		Node<T>* newNode = new Node<T>();
		// 2. ���ο� ��忡 ������ ����
		newNode->m_data = data;
		// 3. ���ο� ����� ���� �����͸� ������ ���� ����
		newNode->pPrev = pTailNode;
		// 4. ������ ����� ���� �����͸� ���ο� ���� ����
		pTailNode->pNext = newNode;
		// 5. ������ ��带 ���ο� ���� ����
		pTailNode = newNode;
	}
	else
	{
		// 1. ���ο� ��� ����
		Node<T>* newNode = new Node<T>();
		// 2. ���ο� ��忡 ������ ����
		newNode->m_data = data;
		// 3. ó�� ��带 ���ο� ���� ����
		pHeadNode = newNode;
		// 4. ������ ��带 ���ο� ���� ����
		pTailNode = newNode;
	}

	m_size++;
}

template <typename T>
void CLinkedList<T>::pop_back()
{
	if (m_size == 0)
	{
		// assert(0);
		return;
	}
	else if (m_size == 1)
	{
		// 1. ���� ��带 ��� ���
		Node<T>* deleteNode = pTailNode;
		// 2. ó�� ��带 nullptr ����
		pHeadNode = nullptr;
		// 3. ������ ��带 nullptr ����
		pTailNode = nullptr;
		// 4. ���� ��带 ����
		delete deleteNode;
	}
	else
	{
		// 1. ���� ��带 ��� ���
		Node<T>* deleteNode = pTailNode;
		// 2. ������ ��带 ���� ����� ���� �����ͷ� ����
		pTailNode = deleteNode->pPrev;
		// 3. �������� ���� �����͸� nullptr ����
		pTailNode->pNext = nullptr;
		// 4. ���� ��带 ����
		delete deleteNode;
	}

	m_size--;
}

template <typename T>
int CLinkedList<T>::size()
{
	return m_size;
}

template <typename T>
bool CLinkedList<T>::empty()
{
	return 0 == m_size;
}

template <typename T>
void CLinkedList<T>::clear()
{
	while (!empty())
		pop_back();
}

template <typename T>
typename CLinkedList<T>::iterator CLinkedList<T>::begin()
{
	return iterator(this, pHeadNode);
}

template <typename T>
typename CLinkedList<T>::iterator CLinkedList<T>::end()
{
	return iterator(this, nullptr);
}

template<typename T>
typename CLinkedList<T>::iterator CLinkedList<T>::insert(iterator iter, const T& value)
{
	// ��ȿ���� ���� ��Ȳ���� insert�� �����ϴ� ���
	// 1. ����Ʈ�� �������� ���� ���
	if (iter.m_pLinkedList == nullptr)
		assert(0);
	// 2. iterator�� end()�� ����Ű�� �ִ� ���
	else if (iter.m_pNode == nullptr)
	{
		push_back(value);
		return iterator(this, pTailNode);
	}

	// ���ο� ��� �߰� ����
	// 1. ���ο� ��� ����
	Node<T>* newNode = new Node<T>();
	
	// 2. �������� ���ĳ�带 ��� ����
	Node<T>* leftNode = iter.m_pNode->pPrev;
	Node<T>* rightNode = iter.m_pNode;
	
	// 3. ���ο� ��忡 ������ �߰�
	newNode->m_data = value;

	// 4. ��尣�� ���� ����
	newNode->pPrev = leftNode;
	newNode->pNext = rightNode;

	if (leftNode == nullptr)
	{
		pHeadNode = newNode;
	}
	else
	{
		leftNode->pNext = newNode;
	}

	if (rightNode == nullptr)
	{
		// �̰��� �Ͼ�� ����
	}
	else
	{
		rightNode->pPrev = newNode;
	}
	
	//5. ���� �߰��� ��带 ����Ű�� ���ͷ����� ��ȯ
	return iterator(this, newNode);
}

template<typename T>
typename CLinkedList<T>::iterator CLinkedList<T>::erase(iterator iter)
{
	// ��ȿ���� ���� ��Ȳ���� ����
	// 1. ����Ʈ�� �������� ���� ���
	if (iter.m_pLinkedList == nullptr)
		assert(0);
	// 2. iterator�� end() ����Ű�� �־��� ���
	else if (iter.m_pNode == nullptr)
		assert(0);

	// ����� ���� ����
	// 1. ������ ����
	Node<T>* deleteNode = iter.m_pNode;
	Node<T>* leftNode = iter.m_pNode->pPrev;
	Node<T>* rightNode = iter.m_pNode->pNext;

	// 2. ��带 ����
	delete deleteNode;

	// 3. ����� ���� ���� ����
	if (leftNode == nullptr)
	{
		pHeadNode = rightNode;
	}
	else
	{
		leftNode->pNext = rightNode;
	}

	if (rightNode == nullptr)
	{
		pTailNode = leftNode;
	}
	else
	{
		rightNode->pPrev = leftNode;
	}

	// 4. ������ ����� ���� ��带 ��ȯ
	return iterator(this, rightNode);
}

template <typename T>
CLinkedList<T>::iterator::iterator()
{
	m_pLinkedList = nullptr;
	m_pNode = nullptr;
}

template <typename T>
CLinkedList<T>::iterator::iterator(CLinkedList* pLinkedList, Node<T>* pNode)
{
	this->m_pLinkedList = pLinkedList;
	this->m_pNode = pNode;
}

template <typename T>
CLinkedList<T>::iterator::~iterator()
{
}

template <typename T>
typename T& CLinkedList<T>::iterator::operator*()
{
	// ��ȿ���� ���� �����͸� ������ ��
	// 1. end() iterator �� ��
	if (m_pNode == nullptr)
		assert(0);
	return m_pNode->m_data;
}

template <typename T>
typename CLinkedList<T>::iterator& CLinkedList<T>::iterator::operator++()
{
	// 1. ����Ʈ�� �������� ���� ���
	if (m_pLinkedList == nullptr)
		assert(0);
	// 2. iterator�� end() �� ����Ű�� �ִ� ���
	else if (m_pNode == nullptr)
		assert(0);
	
	m_pNode = m_pNode->pNext;
	return *this;
}

template <typename T>
typename CLinkedList<T>::iterator CLinkedList<T>::iterator::operator++(int)
{
	iterator tempIter = *this;
	++(*this);
	return tempIter;
}

template <typename T>
typename CLinkedList<T>::iterator& CLinkedList<T>::iterator::operator+=(int count)
{
	for (int i = 0; i < count; i++)
		++(*this);
	return *this;
}

template <typename T>
typename CLinkedList<T>::iterator& CLinkedList<T>::iterator::operator--()
{
	// 1. ����Ʈ�� �������� ���� ���
	if (m_pLinkedList == nullptr)
		assert(0);
	// 2. iterator�� begin()�� ����Ű�� �ִ� ���
	else if (m_pNode == m_pLinkedList->pHeadNode)
		assert(0);
	// 3. iterator�� end()�� ����Ű�� �ִ� ���
	else if (m_pNode == nullptr)
	{
		m_pNode = m_pLinkedList->pTailNode;
		return *this;
	}

	m_pNode = m_pNode->pPrev;
	return *this;
}

template <typename T>
typename CLinkedList<T>::iterator CLinkedList<T>::iterator::operator--(int)
{
	iterator tempIter = *this;
	--(*this);
	return tempIter;
}

template <typename T>
typename CLinkedList<T>::iterator& CLinkedList<T>::iterator::operator-=(int count)
{
	for (int i = 0; i < count; i++)
		--(*this);
	return *this;
}

template <typename T>
bool CLinkedList<T>::iterator::operator==(const iterator& other)
{
	if (this->m_pLinkedList == other.m_pLinkedList &&
		this->m_pNode		== other.m_pNode)
		return true;
	else
		return false;
}

template <typename T>
bool CLinkedList<T>::iterator::operator!=(const iterator& other)
{
	return !(*this == other);
}