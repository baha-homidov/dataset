//Mirzobakhtiyor Homidov
//khamidov.mirzo@gmail.com
//string.h

#pragma once
#include <stdexcept>
#include <iostream>

namespace ds
{
    class string
    {
    private:
        char *arr = nullptr;
        int arr_size;
        int arr_capacity;
        void deep_copy(const string &source); // deep copy for copy constructor and assignment operator

    public:
        string(const char *source = "");
        string(const string &source)
        {
            deep_copy(source);
        }
        ~string()
        {
            delete[] arr;
        }
        string &operator=(const string &source);
        char &operator[](int index);
        char operator[](int index) const;
        void push_back(char ch);
        void pop_back();
        char front(); 
        char back();
        bool empty() { return (arr_size == 0); }
        int find(char ch);
        void reverse();

        int size() const { return arr_size; }
        friend std::ostream &operator<<(std::ostream &os, const string &str);
        friend bool operator==(const string &left, const string &right);
        friend bool operator<(const string &left, const string &right);
        friend bool operator>(const string &left, const string &right);
        friend string operator+(const string &str_a, const string &str_b);
        string &operator+=(const string &right);


        void reserve(int alloc_size); // pre-alloctes memore for string
        int capacity() { return this->arr_capacity; };  // returns size of memory allocated by array
        void clear();
        void erase(int pos);
        void replace(int pos, int pos_count, string str); // replaces ([pos]...[pos+pos_count]) part of the string with a give string
        void replace(int pos, int pos_count, char str[]); // overload which takes c-style string instead of ds::string
        string substr(int pos, int pos_count); 
    };


//--------------------------------------------------------------------------------

string::string(const char *source)
{

    int source_len = 0;

    for (int i = 0; source[i] != '\0'; i++)
    {
        source_len++;
    }

    arr_size = source_len;
    arr_capacity = arr_size + 1;
    arr = new char[arr_capacity];

    for (int i = 0; i < arr_size; i++)
    {
        arr[i] = source[i];
    }
    arr[arr_size] = '\0';
}

//--------------------------------------------------------------------------------

void string::deep_copy(const string &source)
{
    delete[] arr;
    arr_size = source.arr_size;
    arr_capacity = source.arr_capacity;

    arr = new char[arr_capacity];
    for (int i = 0; i < arr_size; i++)
    {
        arr[i] = source.arr[i];
    }

    arr[arr_size] = '\0';
}
//--------------------------------------------------------------------------------

std::ostream &operator<<(std::ostream &os, const string &str)
{
    os << str.arr;
    return os;
}

//--------------------------------------------------------------------------------

string &string::operator=(const string &source)
{
    if (this != &source)
    {
        deep_copy(source);
    }
    return *this;
}

//--------------------------------------------------------------------------------

bool operator==(const string &left, const string &right)
{
    int i;
    for (i = 0; i < left.size() && i < right.arr_size; i++)
    {
        if (left[i] != right[i])
            return false;
    }
    if (i == left.size() && i == right.size())
        return true;
    else
        return false;
}

//--------------------------------------------------------------------------------

char &string::operator[](int index)
{
    if (index < 0 || index >= arr_size)
        throw std::invalid_argument("Invalid index\n");
    return arr[index];
}

//--------------------------------------------------------------------------------

char string::operator[](int index) const
{
    if (index < 0 || index >= arr_size)
        throw std::invalid_argument("Invalid index\n");
    return arr[index];
}

//--------------------------------------------------------------------------------

bool operator<(const string &left, const string &right)
{
    int i;
    for (i = 0; i < left.size() && i < right.size(); i++)
    {
        if (left[i] != right[i])
        {
            if (left[i] < right[i])
                return true;
            else
                return false;
        }
    }

    if (i == left.size() && i == right.size())
    {
        return false;
    }
    else
    {
        if (i < left.size())
            return false;
        else
            return true;
    }
}

//--------------------------------------------------------------------------------

bool operator>(const string &left, const string &right)
{
    int i;
    for (i = 0; i < left.size() && i < right.size(); i++)
    {
        if (left[i] != right[i])
        {
            if (left[i] > right[i])
                return true;
            else
                return false;
        }
    }

    if (i == left.size() && i == right.size())
    {
        return false;
    }
    else
    {
        if (i < left.size())
            return true;
        else
            return false;
    }
}

//--------------------------------------------------------------------------------

string operator+(const string &str_a, const string &str_b)
{
    string result;
    result.reserve(str_a.arr_size + str_b.arr_size + 1); // make room for the new string

    int i;
    for (i = 0; i < str_a.size(); i++)
    {
        result.arr[i] = str_a[i];
    }

    for (int j = 0; j < str_b.size(); j++, i++)
    {
        result.arr[i] = str_b[j];
    }
    result.arr[i] = '\n';
    result.arr_size = str_a.arr_size + str_b.arr_size;
    return result;
}

//--------------------------------------------------------------------------------

void string::reserve(int alloc_size)
{
    if (alloc_size <= this->arr_capacity)
        return;

    char *new_arr = new char[alloc_size];

    for (int i = 0; i < this->arr_size; i++)
    {
        new_arr[i] = arr[i];
    }

    delete[] arr;
    arr = new_arr;
    arr_capacity = alloc_size;
}

//--------------------------------------------------------------------------------

string &string::operator+=(const string &right)
{
    this->reserve(this->arr_size + right.arr_size + 1);
    for (int i = this->arr_size, j = 0; j < right.arr_size; i++, j++)
    {
        this->arr[i] = right.arr[j];
    }
    this->arr_size = this->arr_size + right.arr_size;
    this->arr[this->arr_size] = '\0';
    return *this;
}

//--------------------------------------------------------------------------------

void string::push_back(char ch)
{
    if (arr_size == 0 && arr_capacity == 1)
    {
        const int alloc_size = 2;
        delete[] arr;
        arr = new char[alloc_size];
        arr[arr_size] = ch;
        arr_size++;
        arr[arr_size] = '\0';
        arr_capacity = alloc_size;
    }
    else if (arr_capacity == arr_size + 1)
    {
        const int alloc_size = arr_size * 2 + 1;
        char *new_arr = new char[alloc_size];

        for (int i = 0; i < arr_size; i++)
        {
            new_arr[i] = arr[i];
        }
        delete[] arr;
        arr = new_arr;
        arr[arr_size] = ch;
        arr_size++;
        arr[arr_size] = '\0';
        arr_capacity = alloc_size;
    }
    else
    {
        arr[arr_size] = ch;
        arr_size++;
        arr[arr_size] = '\0';
    }
}

//--------------------------------------------------------------------------------

void string::pop_back()
{
    if (arr_size == 0)
        return;
    arr[arr_size - 1] = '\0';
    arr_size--;
}

//--------------------------------------------------------------------------------

void string::clear()
{
    arr_size = 0;
    arr[arr_size] = '\0';
}

//--------------------------------------------------------------------------------

void string::erase(int index)
{
    if (index < 0 || index >= arr_size)
        return;

    if (index == arr_size - 1)
    {
        this->pop_back();
    }

    else
    {
        for (int i = index; i < arr_size - 1; i++)
            arr[i] = arr[i + 1];

        arr_size--;
        arr[arr_size] = '\0';
    }
}

//--------------------------------------------------------------------------------

void string::replace(int pos, int count, string str)
{
    if (pos < 0)
        throw std::invalid_argument("Invalid index\n");
    int pos_end = pos + count;
    string result;
    for (int i = 0; i < pos && (*this)[i] != '\0'; i++)
    {
        result.push_back((*this)[i]);
    }

    for (int i = 0; i < str.size(); i++)
    {
        result.push_back(str[i]);
    }

    for (int i = pos_end; i < (*this).size() && (*this)[i] != '\0'; i++)
    {
        result.push_back((*this)[i]);
    }
    *this = result;
}

//--------------------------------------------------------------------------------

void string::replace(int pos, int count, char *str)
{
    if (pos < 0)
        throw std::invalid_argument("Invalid index\n");
    int pos_end = pos + count;

    string result;
    int str_len = strlen(str);

    for (int i = 0; i < pos && (*this)[i] != '\0'; i++)
    {
        result.push_back((*this)[i]);
    }

    for (int i = 0; i < str_len; i++)
    {
        result.push_back(str[i]);
    }

    for (int i = pos_end; i < (*this).size() && (*this)[i] != '\0'; i++)
    {
        result.push_back((*this)[i]);
    }
    *this = result;
}

string string::substr(int pos, int count)
{
    if (pos < 0 || pos > arr_size)
        throw std::invalid_argument("Invalid index\n");
    int pos_end = pos + count;

    string result;

    for (int i = pos; i < pos_end && i < this->size(); i++)
    {
        result.push_back((*this)[i]);
    }
    return result;
}

//--------------------------------------------------------------------------------

char string::front()
{
    if (this->empty())
        throw std::invalid_argument("String is empty\n");
    return arr[0];
}

//--------------------------------------------------------------------------------

char string::back()
{
    if (this->empty())
        throw std::invalid_argument("String is empty\n");
    return arr[arr_size - 1];
}

//--------------------------------------------------------------------------------

int string::find(char ch)
{
    if (this->empty())
        return -1;

    for (int i = 0; i < this->arr_size; i++)
    {
        if (arr[i] == ch)
            return i;
    }
    return -1;
}

//--------------------------------------------------------------------------------

void string::reverse()
{
    if (arr_size <= 1)
        return;

    for (int i = 0, j = arr_size - 1; i < j; i++, j--)
    // swap elements from two ends of an array until the centre is reached
    {
        swap(&arr[i], &arr[j]);
    }
}

//--------------------------------------------------------------------------------

std::istream &operator>>(std::istream &in, string &value)
{
    const int MAX = 1024;
    char buff[MAX];
    in >> buff;
    string result(buff);
    std::cout << "REsult: " << result<<'\n';
    value = result;
    return in;
}


}