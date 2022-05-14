# DataSet - abstract data types in C++

Set of header files which include the implementetion the common data structures

## Table of contents

- [General Info](#general-info)
- [Detailed info and graphic illustations](#detailed-info-and-graphic-illustations)

## General Info

This project was made to improve my understanding in topic "Data Structures And Algorithms" and get hands-on experience by implementing the data structures in C++.
In this project I try imitate the functionality of the STL library, by having similar member functions with similar behaviours. Though iterators are not implemented, member class pointer can be used for some operations. E.g.    `ds::list::node` for `ds::list::node`

**This project is written only for learning purposes and not intended to use in real-world applications!**

## Detailed info and graphic illustations

## `ds::array`
Dynamic Resizable array. Holds data by pre-allocating and re-allocating space according to the insertion and number of elements.  
<p align="center"><img src="https://github.com/baha-homidov/dataset/blob/media/array.png" width="400" /></p> 



## `ds::string`
This datatype has basic functionality similar to std::string. Manages memory similar to ds::array  
<p align="center"><img src="https://github.com/baha-homidov/dataset/blob/media/string.png" width="400" /></p>   



## `ds::list`
Doubly linked list with basic doubly lined list functionality.
<p align="center"><img src="https://github.com/baha-homidov/dataset/blob/media/linked_list.png" width="700" /></p>    

## `ds::stack`
Stack implemented by using singly linked list.  
<p align="center"><img src="https://github.com/baha-homidov/dataset/blob/media/stack.png" height="600" /></p>   

## `ds::queue`
Queue is implemented by using singly linked list.  
<p align="center"><img src="https://github.com/baha-homidov/dataset/blob/media/queue.png" width="480" /></p>      



## `ds::sparse_matrix`
Sparse matrix is implemented using raw dynamic arrays. Only works with artithmetic datatypes
<p align="center"><img src="https://github.com/baha-homidov/dataset/blob/media/sparse_matrix.png" width="530" /></p>    


## `ds::map`
This data structure imitates the functionality of the std::map except iterators and some advanced functionalities. Just like std::map it uses key-value node. Operator **[]** with key used to access any value.  
<p align="center"><img src="https://github.com/baha-homidov/dataset/blob/media/map.png" width="480" /></p>



## `ds::graph`
Implementation of graph data structure by using adacency list. For dynamic array and linked list `std::vector` and `std::list` are used respectively.
<p align="center"><img src="https://github.com/baha-homidov/dataset/blob/media/graph.png" width="480" /></p>
