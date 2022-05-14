#include <iostream>
#include <stdexcept>

namespace ds
{
    template <typename Elem>
    class queue
    {
    private:
        struct Node
        {
            Node *next;
            Elem data;
        };

        Node *front = nullptr;

        Node *rear = nullptr;

        void deep_copy(const queue<Elem> &source); // deep copy for copy constructor and assignment operator
    public:
        queue() : front{nullptr}, rear{nullptr} {};
        queue(const queue &source)
        {
            deep_copy(source);
        }
        queue &operator=(const queue &source);
        ~queue();
        void enqueu(const Elem &val);
        Elem dequeue();
        Elem peek();
        int size() const;
        bool empty() const { return (front == nullptr); };
        void clear();
        void display()
        {
            Node *ptr = front;
            while (ptr)
            {
                std::cout << ptr->data << " ";
                ptr = ptr->next;
            }
        }
    };

    //--------------------------------------------------------------------------------

    template <typename Elem>
    void queue<Elem>::enqueu(const Elem &val)
    {
        Node *temp = new Node;
        temp->next = nullptr;
        temp->data = val;

        if (this->empty())
            front = rear = temp;
        else
        {
            rear->next = temp;
            rear = temp;
        }
    }

    //--------------------------------------------------------------------------------
    template <typename Elem>
    Elem queue<Elem>::dequeue()
    {
        if (this->empty())
            throw std::invalid_argument("Queue is empty\n");
        else
        {
            Elem deq_val = front->data;
            Node *temp = front;
            front = front->next;
            delete temp;
            return deq_val;
        }
    }

    //--------------------------------------------------------------------------------

    template <typename Elem>
    Elem queue<Elem>::peek()
    {
        if (this->empty())
            throw std::invalid_argument("Queue is empty\n");
        else
            return front->data;
    }

    //--------------------------------------------------------------------------------

    template <typename Elem>
    queue<Elem>::~queue()
    {
        Node *temp = front, *tail;
        while (temp)
        {
            tail = temp;
            temp = temp->next;
            delete tail;
        }
        front = rear = nullptr;
    }

    //--------------------------------------------------------------------------------
    template <typename Elem>
    int queue<Elem>::size() const
    {
        int sz = 0;
        Node *temp = front;
        while (temp)
        {
            sz++;
            temp = temp->next;
        }

        return sz;
    }

    //--------------------------------------------------------------------------------
    template <typename Elem>
    void queue<Elem>::clear()
    {
        this->~queue();
    }

    //--------------------------------------------------------------------------------
    template <typename Elem>
    void queue<Elem>::deep_copy(const ds::queue<Elem> &source)
    {
        this->~queue();
        if (source.empty())
            return;

        Node *ptr = source.front;

        Node *temp = new Node;

        temp->next = nullptr;
        temp->data = ptr->data;

        front = rear = temp;

        ptr = ptr->next;
        while (ptr)
        {
            Node *t = new Node;
            t->data = ptr->data;
            t->next = nullptr;
            rear->next = t;
            rear = t;
            ptr = ptr->next;
        }
    }

    //--------------------------------------------------------------------------------
    template <typename Elem>
    queue<Elem> &queue<Elem>::operator=(const queue<Elem> &source)
    {
        if(this!=&source)
        {
            deep_copy(source);
        }
        return *this;
    }
}