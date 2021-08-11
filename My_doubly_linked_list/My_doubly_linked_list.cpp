#include <iostream>
using std::cout;
using std::cin;
using std::endl;


template <typename T>
class List
{
public:
	~List();
	void print();
	int get_size() { return size; }

	void push_back(T value);
	void push_front(T value);

	void pop_front();
	void pop_back();
	void clear();

	void insert(T value, int index);
	void removeAt(int index);

	T& operator [] (int index);
private:
	template<typename T_1>
	class Node
	{
	public:
		Node(T_1 value = T_1(), Node<T_1>* Lnode = nullptr, Node<T_1>* Nnode = nullptr)
		{
			this->value = value;
			this->Lnode = Lnode;
			this->Nnode = Nnode;
		}
		Node<T_1>* Nnode;
		Node<T_1>* Lnode;
		T_1 value;
	};
	int size = 0;
	Node<T>* Head;
	Node<T>* Tail;

	Node<T>* get_from_end(int index)
	{
		int current_index = size - 1;
		Node<T> *current_node = Tail;
		while (current_index != index)
		{
			current_node = current_node->Lnode;
			--current_index;
		}
		return current_node;
	}

	Node<T>* get_from_begin(int index)
	{
		int current_index = 0;
		Node<T>* current_node = Head;
		while (current_index != index)
		{
			current_node = current_node->Nnode;
			++current_index;
		}
		return current_node;
	}

	Node<T>* get_node(int index)
	{
		if (size - index > size / 2)
			return get_from_begin(index);
		else
			return get_from_end(index);
	}


	//friend std::ostream& operator << (std::ostream& os, List<T>& lst);
};

template<typename T>
List<T>::~List()
{
	clear();
}

template<typename T>
void List<T>::push_back(T value)
{
	if (size == 0)
	{
		Head = Tail = new Node<T>(value);
	}
	else
	{
		Tail = Tail->Nnode = new Node<T>(value, Tail);
	}
	++size;
}

template<typename T>
void List<T>::push_front(T value)
{
	if (size == 0)
	{
		Head = Tail = new Node<T>(value);
	}
	else
	{
		Head = Head->Lnode = new Node<T>(value, nullptr, Head);
	}
	++size;
}

template<typename T>
void List<T>::print()
{
	Node<T>* current_node = Head;
	for (size_t i = 0; i < size; i++)
	{
		cout << current_node->value << endl;
		current_node = current_node->Nnode;
	}
}

template<typename T>
void List<T>::pop_front()
{
	Node<T>* n_node_head = Head->Nnode;
	delete Head;
	Head = n_node_head;
	--size;
}

template<typename T>
void List<T>::pop_back()
{
	Node<T>* l_node_tail = Tail->Lnode;
	delete Tail;
	Tail = l_node_tail;
	--size;
}

template<typename T>
void List<T>::clear()
{
	while (size)
	{
		pop_back();
	}
}

template<typename T>
T& List<T>::operator [](int index)
{
	return get_node(index)->value;
}


template<typename T>
void List<T>::removeAt(int index)
{
	if (index == 0)
	{
		pop_front();
	}
	else if (index == size - 1)
	{
		pop_back();
	}
	else
	{
		Node<T>* left_node = get_node(index - 1);
		Node<T>* right_node = get_node(index + 1);
		delete get_node(index);
		left_node->Nnode = right_node;
		right_node->Lnode = left_node;
		--size;
	}
}

template<typename T>
void List<T>::insert(T value, int index)
{
	if (index == 0)
	{
		push_front(value);
	}
	else if (index == size - 1)
	{
		push_back(value);
	}
	else
	{
		Node<T>* left_node = get_node(index - 1);
		Node<T>* right_node = get_node(index);
		right_node->Lnode = left_node->Nnode = new Node<T>(value, left_node, right_node);
		++size;
	}
}

std::ostream& operator << (std::ostream& os, List<int> &lst)
{
	for (size_t i = 0; i < lst.get_size(); i++)
	{
		os << lst[i] << " ";
	}
	return os;
}

int main()
{
	List<int> test;
	test.push_back(1);
	test.push_back(2);
	test.push_back(3);
	test.push_back(4);
	test.push_back(5);
	cout << test;
	return 0;
}