#include <iostream>
using namespace std;

template <typename T>
struct Node
{
	T data;
	Node<T>* next;

	Node(const T& dt, Node<T>* nxt = NULL)
	{
		data = dt;
		next = nxt;
	}
};

template <typename T>
class List
{
private:
	Node<T>* first;
	Node<T>* last;
	size_t counter;

public:
	List();
	List(const List&);
	List& operator=(const List&);
	~List();

	bool isEmpty() const;
	int getNumberOfElements() const;

	void push_front(const T& element);
	void push_back(const T& element);
	void pop_front();
	void pop_back();
	void insert(size_t, const T&);
	void remove(size_t);
	void changeValueAtIndex(size_t, const T&);

	T getFirstElement() const;
	T getLastElement() const;

	//getters for the pointers not for the actual values
	Node<T>* getFirst() const;
	Node<T>* getLast() const;

	//the operator with index
	T operator[](size_t index);

	//the private methods
private:
	void init();
	void copy(const List&);
	void empty();
	Node<T>* goToElement(size_t index);
};

template <typename T>
List<T>::List()
{
	this->first = NULL;
	this->last = NULL;
	this->counter = 0;
}


template <typename T>
List<T>::List(const List<T>& lst)
{
	this->first = NULL;
	this->last = NULL;
	this->counter = 0;
	this->copy(lst);
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& lst)
{
	if (this != &lst)
	{
		this->empty();
		this->init();
		this->copy(lst);
	}

	return *this;
}
template <typename T>
bool List<T>::isEmpty() const
{
	return (this->first == NULL) && (this->last == NULL);

	//the other variant is to return this->counter == 0
}


template <typename T>
Node<T>* List<T>::getFirst() const
{
	if (this->isEmpty()) return NULL;
	return this->first;
}
template <typename T>
Node<T>* List<T>::getLast() const
{
	if (this->isEmpty()) return NULL;
	return this->last;
}
//the getters of the private variables
template <typename T>
T List<T>::getFirstElement() const
{
	return this->first->data;
}
template <typename T>
T List<T>::getLastElement() const
{
	return this->last->data;
}

template <typename T>
int List<T>::getNumberOfElements() const
{
	return this->counter;
}
template <typename T>
T List<T>::operator[](size_t index)
{
	if (index < 0 || index >= this->counter)
	{
		cout << "Index can't be smaller than 0 or bigger than list length" << endl;
		return 0;
	}
	return this->goToElement(index)->data;
}

//the core methods of the list
template <typename T>
void List<T>::push_front(const T& element)
{
	Node<T>* node = new Node<T>(element, this->first);
	if (node)
	{
		if (this->isEmpty())
		{
			this->first = node;
			this->last = node;
		}
		else
		{
			this->first = node;
		}

		this->counter++;
	}
}
template <typename T>
void List<T>::push_back(const T& element)
{
	Node<T>* node = new Node<T>(element, NULL);
	if (node)
	{
		if (this->isEmpty())
		{
			this->first = node;
			this->last = node;
		}
		else
		{
			this->last->next = node;
			this->last = node;
		}
		this->counter++;

	}
}
template <typename T>
void List<T>::pop_front()
{
	if (!this->isEmpty())
	{
		Node<T>* node = this->first;
		this->first = this->first->next;
		if (this->counter == 1)
		{
			this->last = NULL;
			this->first = NULL;
		}

		this->counter--;

		delete node;
	}
	else cout << "Empty List[There is nothing to delete]" << endl;
}

template <typename T>
void List<T>::pop_back()
{
	if (!this->isEmpty())
	{
		if (this->last)
		{

			this->remove(this->counter - 1);
			//this->counter--;
		}

	}
	else cout << "Empty List[There is nothing to delete]" << endl;

}
//--------------------------------
//private methods of the list
template <typename T>
Node<T>* List<T>::goToElement(size_t index)
{
	if (index < 0 || index >= this->counter)
	{
		cout << "Index can't be smaller than 0 or bigger than list length" << endl;
		return NULL;
	}
	Node<T>* current = this->first;
	for (size_t i = 0; i < index; i++)
	{
		current = current->next;
	}

	return current;
}
template <typename T>
void List<T>::copy(const List<T>& lst)
{

	Node<T>* node = lst.getFirst();
	for (int i = 0; i < lst.getNumberOfElements(); i++)
	{
		this->push_back(node->data);
		node = node->next;
	}
}
template <typename T>
void List<T>::empty()
{


	for (size_t i = 0; i < this->counter; i++)
	{
		this->pop_front();
	}

	this->init();

}
template <typename T>
void List<T>::init()
{
	this->first = NULL;
	this->last = NULL;
	this->counter = 0;
}
//------------------------------
template <typename T>
void List<T>::insert(size_t index, const T& element)
{
	if (!this->isEmpty())
	{
		if (index < 0 || index >= this->counter)
			cout << "Index can't be smaller than 0 or bigger than list length" << endl;
		else if (index == 0) push_front(element);
		else if (index == this->counter - 1) push_back(element);
		else
		{
			Node<T>* node = new Node<T>(element, this->goToElement(index)->next);
			this->goToElement(index)->next = node;
		}

		this->counter++;
	}

}
template <typename T>
void List<T>::changeValueAtIndex(size_t index, const T& value)
{
	if (!this->isEmpty())
	{
		if (index < 0 || index >= this->counter)
			cout << "Index can't be smaller than 0 or bigger than list length" << endl;
		else
		{
			this->goToElement(index)->data = value->data;
		}
	}
	else
	{
		cout << "Error empty List" << endl;
	}
}
template <typename T>
void List<T>::remove(size_t index)
{
	if (!this->isEmpty())
	{
		if (index == 0) this->pop_front();
		else
		{
			Node<T>* removed = this->goToElement(index);
			Node<T>* temp = this->goToElement(index - 1);

			if (index == this->counter - 1) this->last = temp;
			temp->next = removed->next;
			delete removed;
			this->counter--;
		}
	}


}

//the destructor
template <typename T>
List<T>::~List()
{
	this->empty();
	this->init();
}
