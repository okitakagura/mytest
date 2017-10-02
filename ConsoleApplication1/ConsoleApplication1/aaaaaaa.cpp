#include<iostream>
#include<deque>
using namespace std;

template<class T>
class queue
{
private:
	deque<T> elements;
public:
	bool empty()const;
	void enqueue(T element);
	void dequeue();
	T front();
	T back();
};

template<class T>
bool queue<T>::empty()const
{
	return elements.empty();
}

template<class T>
void queue<T>::enqueue(T element)
{
	elements.push_back(element);
}

template<class T>
void queue<T>::dequeue()
{
	elements.pop_front();
}

template<class T>
T queue<T>::front()
{
	return elements.front();
}

template<class T>
T queue<T>::back()
{
	return elements.back();
}

int main()
{
	queue<int>a;
	a.enqueue(6);
	a.enqueue(6);
	a.enqueue(6);
	cout << a.back() << endl;
}