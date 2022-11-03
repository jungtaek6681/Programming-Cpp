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

	// ������� iterator ��ɵ�
	class iterator
	{
		friend CVector;
	private:
		CVector*	m_pVec;
		T*			m_pVecData;
		int			m_index;

	public:
		iterator();
		iterator(CVector* pVec, T* pDataArray, int index);
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

template<typename T>
typename CVector<T>::iterator CVector<T>::begin()
{
	return iterator(this, pDataArray, 0);
}

template<typename T>
typename CVector<T>::iterator CVector<T>::end()
{
	return iterator(this, pDataArray, -1);
}

template<typename T>
typename CVector<T>::iterator CVector<T>::insert(CVector<T>::iterator iter, const T& value)
{
	// ���ͷ����Ͱ� ��ȿ���� ���� ��Ҹ� �߰��Ϸ��� �Ѵٸ�
	// 1. ���Ϳ� �ִ� ������ ���� ���� ��Ҹ� �߰��Ϸ��� �� ��
	if (iter.m_index >= m_size || iter.m_index < -1)
	{
		assert(0);
	}
	// 2. ����Ű�� ����� �ٸ� ������ ��Ҹ� ������� �� ��
	else if (iter.m_pVec != this || iter.m_pVecData != this->pDataArray)
	{
		assert(0);
	}
	// 3. end() �� �߰��Ϸ��� �� ��
	else if (iter.m_index == -1)
	{
		push_back(value);
		return iterator(this, pDataArray, m_size);
	}
	
	int index = iter.m_index;
	push_back(0);

	for (int i = m_size - 1; i > index; i--)
	{
		pDataArray[i] = pDataArray[i - 1];
	}
	pDataArray[index] = value;

	return iterator(this, pDataArray, index);
}

template<typename T>
typename CVector<T>::iterator CVector<T>::erase(CVector<T>::iterator iter)
{
	// ���ͷ����Ͱ� ��ȿ���� ���� ��Ҹ� ������� �Ѵٸ�
	// 1. ���Ϳ� �ִ� �����͹��� ���� ��Ҹ� ������� �� ��
	if (iter.m_index >= m_size || iter.m_index < 0)
	{
		assert(0);
	}
	// 2. ����Ű�� ����� �ٸ� ������ ��Ҹ� ������� �� ��
	else if (iter.m_pVec != this || iter.m_pVecData != this->pDataArray)
	{
		assert(0);
	}

	// �迭�� �ε����� �̿��� ����
	int index = iter.m_index;
	for (int i = index; i < m_size - 1; i++)
	{
		pDataArray[i] = pDataArray[i + 1];
	}

	// ���ͷ����͸� �̿��� ����
	//iterator curIter = iter;
	//iterator nextIter = curIter;
	//nextIter++;
	//for (; nextIter != end(); curIter++, nextIter++)
	//{
	//	*curIter = *nextIter;
	//}

	pop_back();

	if (index < m_size)
	{
		return iterator(this, pDataArray, index);
	}
	else
	{
		return end();
	}
}

template<typename T>
CVector<T>::iterator::iterator()
{
	m_pVec = nullptr;
	m_pVecData = nullptr;
	m_index = -1;
}

template<typename T>
inline CVector<T>::iterator::iterator(CVector* pVec, T* pDataArray, int index)
{
	m_pVec = pVec;
	m_pVecData = pDataArray;
	m_index = index;
}

template<typename T>
CVector<T>::iterator::~iterator()
{
}

template<typename T>
T& CVector<T>::iterator::operator*()
{
	// 1. �� iterator�� end() ���� ��
	if (m_index < 0)
		assert(0);

	return m_pVecData[m_index];
}

template<typename T>
typename CVector<T>::iterator& CVector<T>::iterator::operator++()
{
	// 1. ������ �����Ͱ� �߰�&���� �Ǿ �迭�� ��ġ�� ����� ���
	if (m_pVec->pDataArray != m_pVecData)
	{
		assert(0);
	}
	// 2. iterator�� ������ �����͸� ����Ű�� �ִ� ���
	else if (m_index == m_pVec->size() - 1)
	{
		m_index = -1;
	}
	// 3. iterator�� end()���� ��
	else if (-1 == m_index)
	{
		assert(0);
	}
	// 4. �� �ܿ��� ���� �����͸� ����Ű�� �Ѵ�.
	else
	{
		++m_index;
	}
	return *this; // ���� ����Ű�� ������ ������ ������ �� �ִ°� == ����
}

template<typename T>
typename CVector<T>::iterator CVector<T>::iterator::operator++(int)
{
	iterator tempIter = *this;
	++(*this);	// ���� ++ ������
	return tempIter;
}

template<typename T>
typename CVector<T>::iterator& CVector<T>::iterator::operator--()
{
	// 1. ������ �����Ͱ� �߰�&���� �Ǿ �迭�� ��ġ�� ����� ���
	if (m_pVec->pDataArray != m_pVecData)
	{
		assert(0);
	}
	// 2. iterator�� ù��° �����͸� ����Ű�� �ִ� ���
	else if (0 == m_index)
	{
		assert(0);
	}
	// 3. iterator�� end()���� ��
	else if (-1 == m_index)
	{
		m_index = m_pVec->size() - 1;
	}
	// 4. �� �ܿ��� ���� �����͸� ����Ű�� �Ѵ�.
	else
	{
		--m_index;
	}

	return *this;
}

template<typename T>
typename CVector<T>::iterator CVector<T>::iterator::operator--(int)
{
	iterator tempIter = *this;
	--(*this);	// ���� -- ������
	return tempIter;
}

template<typename T>
typename CVector<T>::iterator& CVector<T>::iterator::operator+=(int count)
{
	for (int i = 0; i < count; i++)
		++(*this);
	return *this;
}

template<typename T>
typename CVector<T>::iterator& CVector<T>::iterator::operator-=(int count)
{
	for (int i = 0; i < count; i++)
		--(*this);
	return *this;
}

template<typename T>
bool CVector<T>::iterator::operator==(const iterator& other)
{
	// 1. ���� ���� �Ҽ��̰�
	// 2. ���� �迭 ����Ű��
	// 3. ���� �ε��� ������ ������
	if (this->m_pVec		== other.m_pVec		&&
		this->m_pVecData	== other.m_pVecData	&&
		this->m_index		== other.m_index		)
		return true;
	else
		return false;
}

template<typename T>
bool CVector<T>::iterator::operator!=(const iterator& other)
{
	return !(*this == other);
}
