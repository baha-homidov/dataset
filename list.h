//Homidov Mirzobakhtiyor
//khamidov.mirzo@gmail.com
//list.h


#pragma once
#include <iostream>

namespace ds
{

    //--------------------------------------------------------------------------------

    template <typename Elem>
    class list
    {
        void deep_copy(const list<Elem> &source);

        template <typename T>
        class Node
        {
        public:
            Elem data;
            Node<T> *prev;
            Node<T> *next;
        };

        Node<Elem> *first = nullptr;
        Node<Elem> *last = nullptr;
    public:
        

        list() { first = last = nullptr; }
        list(Elem A[], int n); // constructor to inittialize list with and array of elements
        list(const list<Elem> &source)
        {
            deep_copy(source);
        }
        ~list();

        list<Elem> &operator=(const list<Elem> &source);
        void display();
        void rdisplay(); // display elements in reverse
        void insert(int index, Elem x);
        int erase(int index);
        void erase_if(std::function<bool(Elem)> const &predicate);
        void push_back(const Elem &elem);  // insert an element at the back
        void pop_back();                   // delete and element at the back
        void push_front(const Elem &elem); // insert an element at the front
        void pop_front();                  // delete and element at the front
        bool empty() const;
        bool sorted() const;
        void replace(int index, const Elem &val);

        void sort();                          // insertion sort
        Elem sum();                           // sum of all elements
        Elem max();                           // max element in the list
        Elem min();                           // min element in the list
        void concat(const list<Elem> &list2); // concatonating second list to the current list
        int size();
        int find(const Elem &val);
        int find_if(std::function<bool(Elem)> const &predicate);
        void reverse();
    };

//------------------------------------------------------------------------------------------------------
template <typename Elem>
list<Elem>::list(Elem A[], int n)
{
    Node<Elem> *tail, *temp;
    first = new Node<Elem>;
    first->data = A[0];
    last = first;
    first->prev = nullptr;
    first->next = nullptr;
    tail = first;
    for (int i = 1; i < n; i++)
    {
        temp = new Node<Elem>;
        temp->data = A[i];
        temp->next = nullptr;
        temp->prev = tail;
        tail->next = temp;
        tail = temp;
        last = temp;
    }
}

template <typename Elem>
bool list<Elem>::empty() const
{
    if (this->begin() == this->end())
        return true;
    else
        return false;
}

//------------------------------------------------------------------------------------------------------

template <typename Elem>
list<Elem>::~list()
{
    Node<Elem> *p = first;
    while (first)
    {
        first = first->next;
        delete p;
        p = first;
    }
}

//------------------------------------------------------------------------------------------------------
template <typename Elem>
void list<Elem>::display()
{
    Node<Elem> *i = first;
    while (i != nullptr)
    {
        std::cout << i->data << ' ';
        i = i->next;
    }

    std::cout << '\n';
}

//--------------------------------------------

template <typename Elem>
void list<Elem>::rdisplay()
{
    Node<Elem> *ptr = this->last;
    while (ptr)
    {
        std::cout << ptr->data << " ";
        ptr = ptr->prev;
    }
    std::cout << '\n';
}

//------------------------------------------------------------------------------------------------------

template <typename Elem>
int list<Elem>::size()
{
    Node<Elem> *p = first;
    int len = 0;
    while (p)
    {
        len++;
        p = p->next;
    }
    return len;
}

//------------------------------------------------------------------------------------------------------

template <typename Elem>
void list<Elem>::insert(int index, Elem x)
{
    Node<Elem> *temp, *node_ptr = first;

    if (index < 0 || index > size())
        return;
    temp = new Node<Elem>;
    temp->data = x;
    temp->next = nullptr;
    temp->prev = nullptr;

    if (index == 0)
    {
        temp->next = first;
        first->prev = temp;
        temp->prev = nullptr;
        first = temp;
    }
    else
    {
        for (int i = 0; i < index - 1; i++)
            node_ptr = node_ptr->next;
        if (node_ptr == last)
        {
            last->next = temp;
            temp->prev = last;
            temp->next = nullptr;
            last = temp;
            return;
        }
        temp->next = node_ptr->next;
        node_ptr->next->prev = temp;
        node_ptr->next = temp;
        temp->prev = node_ptr;
    }
}

//------------------------------------------------------------------------------------------------------
template <typename Elem>
void list<Elem>::push_back(const Elem &val) // insert an element at the back
{
    Node<Elem> *temp = new Node<Elem>;
    temp->data = val;
    temp->prev = nullptr;
    temp->next = nullptr;

    if (this->size() == 0)
    {
        first = last = temp;
    }
    else
    {
        last->next = temp;
        temp->prev = last;
        last = temp;
    }
}

//------------------------------------------------------------------------------------------------------
template <typename Elem>
void list<Elem>::pop_back() // delete and element at the back
{
    if (this->size() == 0)
        return;
    else if (first == last)
    {
        delete first;
        first = last = nullptr;
    }
    else
    {
        Node<Elem> *temp = last->prev;
        temp->next = nullptr;
        delete last;
        last = temp;
    }
}

//------------------------------------------------------------------------------------------------------

template <typename Elem>
void list<Elem>::push_front(const Elem &val) // insert an element at the front
{
    Node<Elem> *temp = new Node<Elem>;
    temp->data = val;
    temp->next = temp->prev = nullptr;
    if (this->size() == 0)
    {
        first = last = temp;
    }
    else
    {
        first->prev = temp;
        temp->next = first;
        first = temp;
    }
}

//------------------------------------------------------------------------------------------------------

template <typename Elem> // delete and element at the front
void list<Elem>::pop_front()
{
    if (this->size() == 0)
        return;
    if (first == last) // if size == 1
    {
        delete first;
        first = last = nullptr;
    }
    else
    {
        Node<Elem> *temp = first->next;
        temp->prev = nullptr;
        delete first;
        first = temp;
    }
}
//------------------------------------------------------------------------------------------------------

template <typename Elem>
int list<Elem>::erase(int index)
{
    Node<Elem> *p, *q = nullptr;
    int x = -1;
    if (index < 0 || index >= size())
        return -1;
    if (index == 0)
    {
        p = first;
        first = first->next;
        first->prev = nullptr;
        x = p->data;
        delete p;
    }
    else
    {
        p = first;
        for (int i = 0; i < index; i++)
        {
            p = p->next;
        }

        p->prev->next = p->next;

        if (p->next)
            p->next->prev = p->prev;
        else
            last = p->prev;
        x = p->data;

        delete p;
    }
    return x;
}

//------------------------------------------------------------------------------------------------------
template <typename Elem>
void list<Elem>::sort() // insertion sort
{
    if (this->size() == 0 || this->size() == 1)
        return;
    Node<Elem> *marker, *current;
    double temp;
    for (marker = first->next; marker != nullptr; marker = marker->next)
    {
        temp = marker->data;
        current = marker;
        while (current->prev != nullptr && current->prev->data >= temp)
        {
            current->data = current->prev->data;
            current = current->prev;
        }
        current->data = temp;
    }
}

//------------------------------------------------------------------------------------------------------

// TODO
// FIND
// FIND_IF

//------------------------------------------------------------------------------------------------------

template <typename Elem>
Elem list<Elem>::sum() // sum of all elements

{
    Elem sum = 0;
    for (auto iter = this->begin(); iter != this->end(); ++iter)
    {
        sum += *iter;
    }
    return sum;
}

//------------------------------------------------------------------------------------------------------

template <typename Elem>
Elem list<Elem>::max() // max element in the list
{
    if (this->begin() == this->end())
        return 0;
    Elem max = *(this->begin());
    for (auto iter = this->begin(); iter != this->end(); ++iter)
    {
        if (*iter > max)
            max = *iter;
    }
    return max;
}

//------------------------------------------------------------------------------------------------------

template <typename Elem>
Elem list<Elem>::min() // min element in the list
{
    if (this->begin() == this->end())
        return 0;
    Elem min = *(this->begin());
    for (auto iter = this->begin(); iter != this->end(); ++iter)
    {
        if (*iter < min)
            min = *iter;
    }
    return min;
}

//------------------------------------------------------------------------------------------------------

template <typename Elem>
void list<Elem>::concat(const list<Elem> &list2) // concatonating second list to the current list
{
    if (list2.empty())
        return;

    for (auto iter = list2.begin(); iter != list2.end(); ++iter)
    {
        this->push_back(*iter);
    }
}

//------------------------------------------------------------------------------------------------------

template <typename Elem>
list<Elem> merge(const list<Elem> &ls1, const list<Elem> &ls2) // both lists should be sorted
{
    list<Elem> result;
    auto ls1_iter = ls1.begin();
    auto ls2_iter = ls2.begin();
    while (ls1_iter != ls1.end() && ls2_iter != ls2.end())
    {
        if (*ls1_iter <= *ls2_iter)
        {
            result.push_back(*ls1_iter);
            ++ls1_iter;
        }
        else
        {
            result.push_back(*ls2_iter);
            ++ls2_iter;
        }
    }

    while (ls1_iter != ls1.end())
    {
        result.push_back(*ls1_iter);
        ++ls1_iter;
    }

    while (ls2_iter != ls2.end())
    {
        result.push_back(*ls2_iter);
        ++ls2_iter;
    }

    return result;
}

//--------------------------------------------------------------------------------

template <class Elem>
void list<Elem>::deep_copy(const list<Elem> &source)
{

    Node<Elem> *p = first;
    while (first)
    {
        first = first->next;
        delete p;
        p = first;
    }

    first = last = nullptr; // re-set pointers to their default state

    Node<Elem> *node_ptr;

    node_ptr = source.first; // copy the new data
    while (node_ptr)
    {
        this->push_back(node_ptr->data);
        node_ptr = node_ptr->next;
    }
}

//--------------------------------------------------------------------------------

template <class Elem>
list<Elem> &list<Elem>::operator=(const list<Elem> &source)
{
    if (this != &source)
    {
        deep_copy(source);
    }
    return *this;
}

//--------------------------------------------------------------------------------

template <class Elem>
int list<Elem>::find(const Elem &val)
{
    int index = 0;
    Node<Elem> *ptr = first;
    while (ptr)
    {
        if (ptr->data == val)
            return index;
        else
        {
            ptr = ptr->next;
            index++;
        }
    }
    return -1;
}

//--------------------------------------------------------------------------------

template <class Elem>
int list<Elem>::find_if(const std::function<bool(Elem)> &predicate)
{
    int index = 0;
    Node<Elem> *ptr = first;
    while (ptr)
    {
        if (predicate(ptr->data))
            return index;
        else
        {
            ptr = ptr->next;
            index++;
        }
    }
    return -1;
}

//--------------------------------------------------------------------------------

template <class Elem>
void list<Elem>::erase_if(const std::function<bool(Elem)> &predicate)
{
    Node<Elem> *ptr = first;
    int index = 0;
    while (ptr)
    {
        if (predicate(ptr->data))
        {
            ptr = ptr->next;
            this->erase(index);
        }
        else
        {
            ptr = ptr->next;
            index++;
        }
    }
}

//--------------------------------------------------------------------------------

template <class Elem>
void list<Elem>::reverse()
{
    Node<Elem> *p = first, *q;
    while (p)
    {
        q = p;
        p = p->next;

        Node<Elem> *temp = q->prev;
        q->prev = q->next;
        q->next = temp;
    }
    Node<Elem> *temp = first;
    first = last;
    last = temp;
}

//--------------------------------------------------------------------------------

template <class Elem>
bool list<Elem>::sorted() const
{
    Node<Elem> *ptr = first;

    while (ptr->next)
    {
        if (ptr->data > ptr->next->data)
            return false;
        ptr = ptr->next;
    }
    return true;
}

//--------------------------------------------------------------------------------

template <class Elem>
void list<Elem>::replace(int index, const Elem &val)
{
    if (index < 0 || index >= size() || first == nullptr)
        return;
    Node<Elem> *ptr = first;
    for (int i = 0; i < index; i++)
    {
        ptr = ptr->next;
    }
    ptr->data = val;
}
//*******************************************************************************************************
//*******************************************************************************************************

}