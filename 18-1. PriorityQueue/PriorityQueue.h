#pragma once
#include <vector>

template <typename T>
class CLess
{
public:
	bool operator()(const T& left, const T& right)
	{
		return left < right;
	}
};

template <typename T>
class CGreater
{
public:
	bool operator()(const T& left, const T& right)
	{
		return left > right;
	}
};

template <typename T, typename Container = std::vector<T>, typename Compare = CLess<T>>
class CPriorityQueue
{
private:
	Container container;
	Compare comp;

	void swap(T& left, T& right)
	{
		T temp = left;
		left = right;
		right = temp;
	}

	void popHeap()
	{
		// 1. �� ������ ��带 �ֻ�� ���� ��ü�ϰ� �� ���� ��带 ����
		swap(container.front(), container.back());
		container.pop_back();
		// 2. �ڽ� ����� ���Ͽ� �� ���� ���� �ڽĳ��� ���ϰ� ��ü
		int curIndex = 0;

		while (curIndex < container.size())
		{
			int leftChildIndex = curIndex * 2 + 1;
			int rightChildIndex = curIndex * 2 + 2;

			if (leftChildIndex < container.size() && rightChildIndex < container.size())
			{
				// ��尡 �Ѵ� �ִ� ���
				int lessIndex =
					comp(container[leftChildIndex], container[rightChildIndex]) ?
					leftChildIndex :
					rightChildIndex;

				//if (container[curIndex] > container[lessIndex])
				if (comp(container[lessIndex], container[curIndex]))
				{
					swap(container[curIndex], container[lessIndex]);
					curIndex = lessIndex;
				}
				else
				{
					break;
				}
			}
			else if (leftChildIndex < container.size() && rightChildIndex >= container.size())
			{
				// ���� �ڽ� ��常 �ִ� ���
				//if (container[curIndex] > container[leftChildIndex])
				if (comp(container[leftChildIndex], container[curIndex]))
				{
					swap(container[curIndex], container[leftChildIndex]);
					curIndex = leftChildIndex;
				}
				else
				{
					break;
				}
			}
			else
			{
				// ��尡 �Ѵ� ���� ���
				break;
			}
		}
		// 3. 2�� ������ �ݺ�
	}
	void pushHeap(const T& data)
	{
		// 1. ���� �� ������ �� ��带 �߰�
		container.push_back(data);
		int curIndex = container.size() - 1;
		while (curIndex > 0)
		{
			// 2. ������ ��尡 �θ�� ���ؼ�
			int parentIndex = (curIndex - 1) / 2;
			// 2-1. �� ������ ��ü
			//if (container[curIndex] < container[parentIndex])
			if (comp(container[curIndex], container[parentIndex]))
			{
				swap(container[curIndex], container[parentIndex]);
				curIndex = parentIndex;
			}
			// 2-2. �� ũ�� ��
			else
			{
				break;
			}
		}
		// 3. ��ü�� �θ� �������� �ٽ� ����
	}

public:
	CPriorityQueue() {}
	virtual ~CPriorityQueue() {}

	bool empty()
	{
		return container.empty();
	}
	void pop()
	{
		popHeap();
	}
	void push(const T& data)
	{
		pushHeap(data);
	}
	int size()
	{
		return container.size();
	}
	const T& top()
	{
		return container.front();
	}
};