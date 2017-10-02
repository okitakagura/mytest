#include<iostream>
#include<vector>
using namespace std;

template<typename T>
class queue
{
public:
	queue() {};
	~queue();

	bool empty();
	void enqueue(T element);
	void dequeue();
	T front();
	T back();
private:
	vector<T>vec;
};

template<typename T>
bool queue<T>::empty()
{
	if (vec.size() == 0)
		return true;
	else
		return false;
}

template<typename T>
void queue<T>::enqueue(T element)
{
	vec.push_back(element);
}

template<typename T>
void queue<T>::dequeue()
{
	vec.front();
}

template<typename T>
T queue<T>::front()
{
	return(vec.at(0));
}

template<typename T>
T queue<T>::back()
{
	return(vec.at(vec.size() - 1));
}

int main()
{
	queue<int>a;
	cout << a.empty() << endl;
	return 0;
}
