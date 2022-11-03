#pragma once

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

	class iterator
	{

	};

	void push_front(const T& data);
	void pop_front();
	void push_back(const T& data);
	void pop_back();

	int size();
	bool empty();
	void clear();
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