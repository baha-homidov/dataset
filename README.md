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
<p align="center"><img src="https://user-images.githubusercontent.com/96972109/205482341-f6019c1e-5783-4568-b429-a9a260085f43.png" width="400" /></p>


## `ds::string`
This datatype has basic functionality similar to std::string. Manages memory similar to ds::array  
<p align="center"><img src="https://user-images.githubusercontent.com/96972109/205482426-9f4cae07-c6cb-4157-a0c5-620c37691ac3.png" width="400" /></p>  



## `ds::list`
Doubly linked list with basic doubly lined list functionality.
<p align="center"><img src="https://user-images.githubusercontent.com/96972109/205482460-b07ecbd5-a505-4681-8b7c-7ef19961d5c7.png" width="700" /></p>


## `ds::stack`

Stack implemented by using singly linked list.  
<p align="center"><img src="https://github.com/baha-homidov/dataset/blob/media/stack.png" height="600" /></p>   

## `ds::queue`
Queue is implemented by using singly linked list.  
<p align="center"><img src="[https://github.com/baha-homidov/dataset/blob/media/queue.png](https://user-images.githubusercontent.com/96972109/205482471-e6b54229-720e-4a23-9383-76bb943574a7.png)" width="480" /></p>      




## `ds::sparse_matrix`
Sparse matrix is implemented using raw dynamic arrays. Only works with artithmetic datatypes
<p align="center"><img src="[https://github.com/baha-homidov/dataset/blob/media/sparse_matrix.png](https://user-images.githubusercontent.com/96972109/205482491-4dd5dfb2-dfb2-49e9-bb17-9a48e9756b71.png)" width="530" /></p>    




## `ds::map`
This data structure imitates the functionality of the std::map except iterators and some advanced functionalities. Just like std::map it uses key-value node. Operator **[]** with key used to access any value.  
<p align="center"><img src="https://user-images.githubusercontent.com/96972109/205482503-f76a30e9-5be1-4aad-80e6-44abd9be373d.png" width="480" /></p>







## `ds::graph`
Implementation of graph data structure by using adacency list. For dynamic array and linked list `std::vector` and `std::list` are used respectively.
<p align="center"><img src="https://user-images.githubusercontent.com/96972109/205482522-2b80cd56-2b1e-4a97-94dd-384ac5f6aab9.png" width="480" /></p>


