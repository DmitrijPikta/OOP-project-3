
## Vector mrthods
### int size() const
Method do not take anything and return size value like integer. Const - garantee that size value is not changing in the size() method

### int capacity() const
Method do not take anything and return capacity value like integer. Const - garantee that capacity value is not changing in the capacity() method

### void push_back(const T &value)
Method take T value like reference. It add value in the back of already exiting values in Vector. After adding new value size of Vector is growing by 1. Const garantee that value is not changing in the method. push_method do not return anything.

### void pop_back()
Method delete one element of Vector at the back. pop_back do not take anything and do not return anything.  

### bool empty() const
Method return true or false value depending on where are no elements in Vector or where are. So if size of Vector is 0, method empty() return true, if not, return false. Method do not take anything. Const garantee that Vector object is not changing in the method.

Size      |Standart vector |Custom vector
----------|----------------|--------------
10000     |0.0004309       |0.0004674
100000    |0.0018539       |0.0023244
1000000   |0.0094705       |0.0094142 
10000000  |0.070172        |0.11686
100000000 |0.647181        |0.971497

Result: standart vector container works faster

Reallocations number are equal. In case of 100000000 size both vectors have reallocated 27 times. 











