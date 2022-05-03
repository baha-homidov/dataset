#pragma once
#include <stdexcept>
#include <functional>
namespace ds
{
    template <typename T>
    class array
    {
    private:
        int arr_size;
        int arr_capacity;
        T *arr;

        int partition(T *array, int low, int high);
        void quick_sort(T *array, int low, int high);
        void deep_copy(const array &source);
    public:
        
        array();
        array(const int &sz);
        array(const array &source)
        {
            deep_copy(source);
        }
        array &operator=(const array &source);

        void push_back(const T &elem);
        void pop_back();
        T get(const int &index);
        void set(const int &index, const T &val);
        T &operator[](int index);
        T front();
        T back();

        void erase(const int &index);
        // erases all the elements for which predicate returns true
        void erase_if(std::function<bool(T)> const &predicate);
        int find(const T &val);
        int find_if(std::function<bool(T)> const &predicate);
        int bin_search(const T &val);
        void reverse();

        int size() { return this->arr_size; };
        int capacity() { return this->arr_capacity; };
        void sort();
        bool sorted();
        bool empty() { return arr_size == 0; }
        
        void reserve(const int &val); // resize the capacity

        ~array();
    };

    template <class T>
    void swap(T *a, T *b)
    {
        T t = *a;
        *a = *b;
        *b = t;
    }

}

//--------------------------------------------------------------------------------

template <typename T>
ds::array<T>::array(const int &sz)
{
    arr = new T[sz];
    arr_size = sz;
    arr_capacity = sz;
}

//--------------------------------------------------------------------------------

template <typename T>
ds::array<T>::array()
{
    arr_size = arr_capacity = 0;
    arr = nullptr;
}

//--------------------------------------------------------------------------------

template <typename T>
ds::array<T>::~array()
{
    delete[] arr;
}

//--------------------------------------------------------------------------------

template <typename T>
void ds::array<T>::push_back(const T &elem)
{
    if (arr_size == 0 && arr_capacity == 0)
    {
        const int alloc_size = 2;
        arr = new T[alloc_size];
        arr[arr_size] = elem;
        arr_size++;
        arr_capacity = alloc_size;
    }
    else
    {
        if (arr_size == arr_capacity)
        { // if current array is already filled
            // make a new array with 2x bigger then old array
            // copy all the elements and push the new element
            const int alloc_size = arr_size * 2;
            T *new_arr = new T[alloc_size];

            for (int i = 0; i < arr_size; i++)
            {
                new_arr[i] = arr[i];
            }

            new_arr[arr_size] = elem;
            arr_size++;
            arr_capacity = alloc_size;
            delete[] arr;
            arr = new_arr;
        }
        else
        {
            arr[arr_size] = elem;
            arr_size++;
        }
    }
}

//--------------------------------------------------------------------------------

template <class T>
void ds::array<T>::pop_back()
{
    if (arr_size == 0)
        return;

    arr_size--;
}

//--------------------------------------------------------------------------------

template <class T>
void ds::array<T>::erase(const int &index)
{
    if (index < 0 || index >= arr_size)
        return;
    if (index == arr_size - 1)
    {
        arr_size--;
    }
    else
    {
        for (int i = index; i < arr_size - 1; i++)
            arr[i] = arr[i + 1];

        arr_size--;
    }
}

//--------------------------------------------------------------------------------
template <class T>

void ds::array<T>::erase_if(std::function<bool(T)> const &predicate)
{
    if (arr_size == 0)
        return;

    int i = 0;
    while (i < this->arr_size)
    {
        if (predicate(this->get(i)))
            this->erase(i);
        else
            i++;
    }
}
//--------------------------------------------------------------------------------

template <typename T>
T ds::array<T>::get(const int &index)
{
    if (index < 0 || index >= arr_size)
        throw std::invalid_argument("Invalid index\n");

    return arr[index];
}

//--------------------------------------------------------------------------------

template <class T>
T &ds::array<T>::operator[](int index)
{
    if (index < 0 || index >= arr_size)
        throw std::invalid_argument("Invalid index\n");
    return arr[index];
}

//--------------------------------------------------------------------------------

template <class T>
void ds::array<T>::set(const int &index, const T &val)
{
    if (index < 0 || index >= arr_size || arr_size == 0)
        throw std::invalid_argument("Invalid index\n");

    arr[index] = val;
}

//--------------------------------------------------------------------------------

template <class T>
int ds::array<T>::find(const T &val)
{
    for (int i = 0; i < this->arr_size; i++)
    {
        if (this->get(i) == val)
            return i;
    }
    return -1;
}

//--------------------------------------------------------------------------------

template <class T>
int ds::array<T>::find_if(const std::function<bool(T)> &predicate)
{
    for (int i = 0; i < this->arr_size; i++)
    {
        if (predicate(this->get(i)))
            return i;
    }
    return -1;
}

//--------------------------------------------------------------------------------

template <class T>
void ds::array<T>::sort()
{
    if (arr_size == 0 || arr_size == 1)
        return;
    this->quick_sort(this->arr, 0, this->arr_size - 1);
}

//--------------------------------------------------------------------------------

template <class T>
int ds::array<T>::partition(T *array, int low, int high)
{
    // select the rightmost element as pivot
    T pivot = array[high];

    // pointer for greater element
    int i = (low - 1);

    // traverse each element of the array
    // compare them with the pivot
    for (int j = low; j < high; j++)
    {
        if (array[j] <= pivot)
        {

            // if element smaller than pivot is found
            // swap it with the greater element pointed by i
            i++;

            // swap element at i with element at j
            ds::swap(&array[i], &array[j]);
        }
    }

    // swap pivot with the greater element at i
    ds::swap(&array[i + 1], &array[high]);

    // return the partition point
    return (i + 1);
}

//--------------------------------------------------------------------------------

template <class T>
void ds::array<T>::quick_sort(T *array, int low, int high)
{
    if (low < high)
    {

        // find the pivot element such that
        // elements smaller than pivot are on left of pivot
        // elements greater than pivot are on righ of pivot
        int pi = partition(array, low, high);

        // recursive call on the left of pivot
        quick_sort(array, low, pi - 1);

        // recursive call on the right of pivot
        quick_sort(array, pi + 1, high);
    }
}

//--------------------------------------------------------------------------------

template <class T>
int ds::array<T>::bin_search(const T &val)
{

    int low, mid, high;
    low = 0;
    high = arr_size - 1;

    while (low <= high)
    {
        mid = (low + high) / 2;
        if (val == arr[mid])
            return mid;
        else if (val < arr[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}

//--------------------------------------------------------------------------------

template <class T>
bool ds::array<T>::sorted()
{
    for (int i = 0; i < arr_size - 1; i++)
    {
        if (arr[i] > arr[i + 1])
            return false;
    }
    return true;
}

//--------------------------------------------------------------------------------

template <class T>
T ds::array<T>::front()
{
    if (this->empty())
        throw std::invalid_argument("array is empty\n");
    return arr[0];
}

//--------------------------------------------------------------------------------

template <class T>
T ds::array<T>::back()
{
    if (this->empty())
        throw std::invalid_argument("array is empty\n");
    return arr[arr_size - 1];
}

//--------------------------------------------------------------------------------

template <class T>
void ds::array<T>::deep_copy(const ds::array<T> &source)
{
    delete[] arr;
    arr_size = source.arr_size;
    arr_capacity = source.arr_capacity;
    if (source.arr)
    {
        arr = new T[arr_capacity];
        for (int i = 0; i < arr_size; i++)
            arr[i] = source.arr[i];
    }
    else
        arr = nullptr;
}

template <class T>
ds::array<T> &ds::array<T>::operator=(const ds::array<T> &source)
{
    if (this != &source)
    {
        deep_copy(source);
    }
    return *this;
}

template <class T>
void ds::array<T>::reverse()
{
    if (arr_size <= 1)
        return;

    for (int i = 0, j = arr_size - 1; i < j; i++, j--)
    // swap elements from two ends of an array until the centre is reached
    {
        ds::swap(&arr[i], &arr[j]);
    }
}

template <class T>
void ds::array<T>::reserve(const int &alloc_size)
{
    if (alloc_size <= this->arr_capacity)
        return;

    T *new_arr = new T[alloc_size];

    if (arr != nullptr)
    {
        for (int i = 0; i < this->arr_size; i++)
        {
            new_arr[i] = arr[i];
        }
    }

    delete[] arr;
    arr = new_arr;
    arr_capacity = alloc_size;
}