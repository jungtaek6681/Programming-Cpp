#pragma once

#include <cassert>

template <typename T>
class CVector
{
private:
	T* pDataArray;			// Vector�� �����͸� ��� ���� �迭�� �����Ҵ� �� �ּҰ�.
	unsigned int m_size;		// Vector ���� �迭�� �� �ִ� ������ ��
	unsigned int m_capacity;	// Vector ���� �迭�� �� �� �ִ� ��뷮

public:
	CVector();
	virtual ~CVector();

	void push_back(const T& data);	// Vector�� ���� ������ �߰�
	void pop_back();				// Vector�� ���� ������ ����
	int size();						// Vector�� ����Ǿ� �ִ� ������ ��
	void resize(unsigned int resize);	// Vector �����迭�� ũ�⸦ ������
	bool empty();					// Vector�� ��� ���� ��� true ��ȯ
	void clear();					// Vector�� �ִ� ��� ������ ����

	T& operator[](unsigned int index);	// Vector�� index��° ������ ����
};

template <typename T>
CVector<T>::CVector()
{
	pDataArray = new T[5];
	m_size = 0;
	m_capacity = 5;
}

template <typename T>
CVector<T>::~CVector()
{
	delete[] pDataArray;
}

template <typename T>
void CVector<T>::resize(unsigned int resize)
{
	T* newArray = new T[resize];
	for (int i = 0; i < m_size; i++)
	{
		newArray[i] = pDataArray[i];
	}

	m_capacity = resize;
	delete[] pDataArray;
	pDataArray = newArray;
}

template<typename T>
void CVector<T>::push_back(const T& data)
{
	// �����͸� �߰��� �ֱ� ���� �̹� �� �� �־��� ��Ȳ�̶��
	if (m_size >= m_capacity)
	{
		resize(m_capacity + 5);
	}

	pDataArray[m_size] = data;
	m_size++;
}

template<typename T>
void CVector<T>::pop_back()
{
	if (!empty())
	{
		// �����͸� ���� ���� �̹� ������� �ʹ� ���� ��Ȳ�̶��
		if (m_size < m_capacity / 4)
		{
			resize(m_capacity / 2);
		}
		m_size--;
	}
}

template<typename T>
int CVector<T>::size()
{
	return m_size;
}

template<typename T>
bool CVector<T>::empty()
{
	return m_size == 0;
}

template<typename T>
void CVector<T>::clear()
{
	delete[] pDataArray;

	pDataArray = new T[5];
	m_size = 0;
	m_capacity = 5;
}

template<typename T>
T& CVector<T>::operator[](unsigned int index)
{
	if (index >= m_size)
	{
		assert(0);
	}
	return pDataArray[index];
}