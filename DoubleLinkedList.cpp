//This program represents the implementation of a doubly-connected list with template typing.
//also has a built-in stopwatch
#include "timer.h"
template <class T>
class List
{
private:
	template<class T>
	class Node
	{
	public:
		Node(T data = T(), Node *pNext = nullptr, Node *pPrev = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
			this->pPrev = pPrev;
		}
		T data;
		Node *pNext;
		Node*pPrev;
	};

public:
	int size;
	Node<T> * head;
	Node<T> * tail;

	List();
	~List();
	void push_back(T data);
	void push_front(T data);
	void insert(T data, int index);
	T& operator[](const int index);
	int GetSize();
	void pop_front();
	void pop_back();
	void removeAt(int index);
	void clear();
	void OutputList();
};

template<class T>
List<T>::List()
{
	T data = 0;
	tail = nullptr;
	head = nullptr;
}

template<class T>
void List<T>::push_back(T data)
{
	if (size == 0)
	{
		head = tail = new Node<T>(data);
	}
	else
	{
		Node<T>*current = head;
		tail = new Node<T>(data, nullptr, tail);
		for (int i = 0; i < size - 1; i++)
		{
			current = current->pNext;
		}
		current->pNext = tail;
		size++;
	}
}

///input data on front
template <class T>
void List<T>::push_front(T data)
{
	if (size == 0)
	{
		head = tail = new Node<T>(data);
	}
	else
	{
		Node<T>*Tcurrent = tail;
		head = new Node<T>(data, head, nullptr);
		while (Tcurrent->pPrev != nullptr)
		{
			Tcurrent = Tcurrent->pPrev;
		}
		Tcurrent->pPrev = head;
	}
	size++;
}

template<class T>
void List<T>::insert(T data, int index)
{
	cout << "insert value : " << data << " into " << index << "th position" << endl;
	bool change = false;
	if (index == 0) { push_front(data);	change = true; }
	if (index == size && change == false) { push_back(data); change = true; }
	if (index != 0 && index != size && change == false)
	{
		Node<T> *current = head;
		Node<T> *Tcurrent = tail;
		int Ncount = 1;
		int Pcount = 1;

		while (Ncount != index)
		{
			current = current->pNext;
			Ncount++;
		}
		Tcurrent = current->pNext;
		current->pNext = Tcurrent->pPrev = new Node<T>(data, current->pNext, Tcurrent->pPrev); 
		size++;
	}
}

template<class T>
T & List<T>::operator[](const int index)
{
	int Ncount = 0;
	int Pcount = size;
	if (index == 0)
	{
		return head->data;
	}
	if (index == size)
	{
		return tail->data;
	}
	if (size / 2 >= index)
	{
		Node<T> *current = head;
		while (Ncount != index)
		{
			current = current->pNext;
			Ncount++;
		}
		return current->data;
	}
	else
	{
		Node<T> *Tcurrent = tail;
		while (Pcount != index + 1)
		{
			Tcurrent = Tcurrent->pPrev;
			Pcount--;
		}
		return Tcurrent->data;
	}
}

template<class T>
int List<T>::GetSize()
{
	return size;
}

template<class T>
void List<T>::pop_front()
{
	if (size != 0)
	{
		//Node<T>*temp = head;
		head = head->pNext;
		if (size != 1)
		{
			head->pPrev = nullptr;
		}
		//delete temp;
		size--;
	}
	if (size == 0)cout << "all element deleted!" << endl;
}
template<class T>
List<T>::~List()
{
	clear();
}
template<class T>
void List<T>::clear()
{
	timer tim;
	
	cout << "\tClear list " << endl;
	while (size) //приобразовавние инт в булл когда, сизу==0 станет фолс ,тогда выйдет из цикла
	{
		pop_front(); //здесь удаляется первый элемент и уменьшается сиз
	}
}

template<class T>
void List<T>::OutputList()
{
	timer t;
	Node<T>*current = head;  //копия списка для сохрана данных в списке при переприсваиваниях на слудующий элемент ->pNext
	for (int i = 0; i < size; i++)
	{
		cout << current->data << "\t";
		current = current->pNext;
	}
	cout << "\nsize of : " << size << endl << endl;
}

template<class T>
void List<T>::pop_back()
{
	cout << "delete from back " << endl;
	if (size != 1 && size != 0)
	{
		
		tail = tail->pPrev;
		tail->pNext = nullptr;
		
		size--;
	}
	else
		pop_front();
}

template<class T>
void List<T>::removeAt(int index)
{
	cout << "delete RemoveAt " << index << "th position" << endl;
	bool change = false;

	if (size < 2)
	{
		if (size == 0) { cout << "size of list : 0!" << endl; change = true; }
		if (index == 0) { pop_front();  change = true; }
	}
	else
	{
		if (index == size) { pop_back(); change = true; }
		if (index == 0 && change == false) { pop_front(); change = true; }
		if (index != 0 && index != size - 1 && change == false)
		{
			Node<T> *current = head;
			Node<T> *Tcurrent = tail;
			int Ncount = 1;
			int Pcount = 2;

			while (Ncount != index)
			{
				current = current->pNext;
				Ncount++;
			}
			
			Tcurrent = current->pPrev;
			current->pNext = Tcurrent;
			Tcurrent->pPrev = current;
			size--;
			change = true;
		}
	}
}
// вывод функцией, работает медленней, метода
/*
void output(List<char> & l)
{
	timer t;
	for (int i = 0; i < l.GetSize(); i++)
	{
		cout << l[i] << "\t";
	}
	cout << "\nsize of : " << l.GetSize() << endl << endl;
}
*/


int main()
{
	List<int> lst;
	/*
	lst.push_front(3);
	lst.push_front(2);
	lst.push_front(1);
	lst.push_front(0);
	lst.push_back(4);
	lst.push_back(5);
	lst.push_back(6);
	*/
	
	int size;
	cout << "Enter size of List" << endl;
	cin >> size;
	cout << endl;
	for (int i = 0; i < size; i++) 
	{
		lst.push_front( rand() % 100);
	}
	
	lst.OutputList();
	
	cout << endl;
	lst.OutputList();
	
	lst.insert(44, (lst.GetSize())/2);
	lst.insert(44, 0);
	lst.OutputList();
	
	cout << "delete from front " << endl;
	lst.pop_front();
	lst.OutputList();
	
	lst.pop_back();
	lst.OutputList();
	
	lst.removeAt(lst.GetSize());
	lst.OutputList();
	//output(lst);
	
}
