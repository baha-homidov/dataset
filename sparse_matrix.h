#include <iostream>
#include <type_traits>
#include <iostream>
// Representation of Sparse Matrices in C++
// Mirzobakhtiyor Homidov

namespace ds
{

    template <typename T>
    class sparse_matrix
    {
        //chech if T is a the right type
        static_assert(std::is_arithmetic<T>::value, "Only arithmetic types are allowed");

    private:
        template <typename U>
        class Element
        {
        public:
            int row;
            int col;
            U val;
        };

        int row_num;
        int col_num;
        int elem_num;

        Element<T> *elems;

    public:
        sparse_matrix(int m, int n, int num)
        {
            this->row_num = m;
            this->col_num = n;
            this->elem_num = num;
            elems = new Element<T>[this->elem_num];
        }
        ~sparse_matrix()
        {
            delete[] elems;
        }

        sparse_matrix operator+(sparse_matrix &s);

        template <typename U>
        friend std::istream &operator>>(std::istream &is, sparse_matrix<U> &s);
        template <typename U>
        friend std::ostream &operator<<(std::ostream &os, sparse_matrix<U> &s);
    };


//--------------------------------------------------------------------------------

    template <class T>
    ds::sparse_matrix<T> ds::sparse_matrix<T>::operator+(ds::sparse_matrix<T> &s)
    {
        int i, j, k;
        if (row_num != s.row_num || col_num != s.col_num)
            throw std::invalid_argument("received matrices with different dimensions\n");
        sparse_matrix *sum = new sparse_matrix(row_num, col_num, elem_num + s.elem_num);
        i = j = k = 0;
        while (i < elem_num && j < s.elem_num)
        {
            if (elems[i].row < s.elems[j].row)
                sum->elems[k++] = elems[i++];
            else if (elems[i].row > s.elems[j].row)
                sum->elems[k++] = s.elems[j++];
            else
            {
                if (elems[i].col < s.elems[j].col)
                    sum->elems[k++] = elems[i++];
                else if (elems[i].col > s.elems[j].col)
                    sum->elems[k++] = s.elems[j++];
                else
                {
                    sum->elems[k] = elems[i];
                    sum->elems[k++].val = elems[i++].val + s.elems[j++].val;
                }
            }
        }
        for (; i < elem_num; i++)
            sum->elems[k++] = elems[i];

        for (; j < s.elem_num; j++)
            sum->elems[k++] = s.elems[j];

        sum->elem_num = k;
        return *sum;
    }


//--------------------------------------------------------------------------------



    template <typename T>
    std::__1::istream &operator>>(std::__1::istream &is, ds::sparse_matrix<T> &s)
    {
        std::cout << "Enter non-zero elements\n"
                  << "[row]   [collumn]   [value]\n";
        for (int i = 0; i < s.elem_num; i++)
        {
            is >> s.elems[i].row >> s.elems[i].col >> s.elems[i].val;
        }
        return is;
    }

    template <class T>
    std::ostream &operator<<(std::ostream &os, ds::sparse_matrix<T> &s)
    {
        int k = 0;
        for (int i = 0; i < s.row_num; i++)
        {

            for (int j = 0; j < s.col_num; j++)
            {
                if (s.elems[k].row == i && s.elems[k].col == j)
                    std::cout << s.elems[k++].val << " ";
                else
                    std::cout << "0 ";
            }
            std::cout << '\n';
        }
        return os;
    }

}