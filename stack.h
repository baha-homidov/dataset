// Homidov Mirzobakhtiyor
// khamidov.mirzo@gmail.com
// stack.h
#include <iostream>
#include <stdexcept>

namespace ds
{
    template <typename Elem>
    class stack
    {
    private:
        struct Node
        {
            Node *next = nullptr;
            Elem data;
        };

        Node *top = nullptr;

    public:
        stack();
        stack(const stack<Elem> &source)
        {
            deep_copy(source);
        }
        stack &operator=(const stack<Elem> &source);
        ~stack();
        void deep_copy(const stack &source);
        void push(const Elem &val);
        Elem pop();
        bool empty() const { return (top == nullptr); };
        int size();
        Elem peek();
        void clear();
    };

    //--------------------------------------------------------------------------------

    template <typename Elem>
    stack<Elem>::stack() : top{nullptr}
    {
    }

    //--------------------------------------------------------------------------------

    template <typename Elem>
    stack<Elem>::~stack()
    {
        Node *ptr = top;
        Node *tail;

        while (ptr != nullptr)
        {
            tail = ptr;
            ptr = ptr->next;
            delete tail;
        }
        top = nullptr;
    }

    //--------------------------------------------------------------------------------

    template <typename Elem>
    void stack<Elem>::push(const Elem &val)
    {
        Node *temp = new Node;
        temp->data = val;
        temp->next = top;
        top = temp;
    }

    //--------------------------------------------------------------------------------

    template <typename Elem>
    Elem stack<Elem>::pop()
    {
        if (this->empty())
            throw std::invalid_argument("Stack is empty\n");

        Elem val = top->data;

        Node *temp = top;
        top = top->next;
        delete temp;
        return val;
    }

    //--------------------------------------------------------------------------------

    template <typename Elem>
    Elem stack<Elem>::peek()
    {
        if (this->empty())
            throw std::invalid_argument("Stack is empty\n");

        return top->data;
    }

    //--------------------------------------------------------------------------------

    template <typename Elem>
    int stack<Elem>::size()
    {
        Node *ptr = top;
        int size = 0;

        while (ptr != nullptr)
        {
            size++;
            ptr = ptr->next;
        }

        return size;
    }

    template <typename Elem>
    void stack<Elem>::deep_copy(const stack<Elem> &source)
    {
        this->~stack();
        if (source.empty())
            return;
        Node *ptr = source.top;

        Node *temp = new Node;
        temp->next = nullptr;
        temp->data = ptr->data;
        top = temp;

        ptr = ptr->next;
        while (ptr)
        {
            Node *t = new Node;
            t->data = ptr->data;
            t->next = nullptr;
            temp->next = t;
            temp = t;
            ptr = ptr->next;
        }
    }

    //--------------------------------------------------------------------------------

    template <class Elem>
    stack<Elem> &stack<Elem>::operator=(const stack<Elem> &source)
    {
        if(this!=&source)
        {
            deep_copy(source);
        }
        return *this;
    }
}
