
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

## std::vector VS Vector push_back() comparison

Size      |std::vector     |Vector
----------|----------------|--------------
10000     |0.0004309       |0.0004674
100000    |0.0018539       |0.0023244
1000000   |0.0094705       |0.0094142 
10000000  |0.070172        |0.11686
100000000 |0.647181        |0.971497

Result: standart vector container works faster

Reallocations number are equal. In case of 100000000 size both vectors have reallocated 27 times. 

## Program working time comparison with std::vector and Vector

### std::vector
Student number:       |100000|1000000|10000000         
----------------------|------|-------|--------
reading file          |0.177|1.686|16.536
cultulating final mark|0.043|0.324|3.010
sorting               |0.099|1.151|13.976
dividing              |0.037|0.259|2.862
writing               |0.397|3.769|37.880
suma                  |0.756|7.191|74.266

### Vector
Student number:       |100000|1000000|10000000         
----------------------|------|-------|--------
reading file          |0.161|1.358|14.298
cultulating final mark|0.022|0.173|1.719
sorting               |0.057|0.737|8.987
dividing              |0.028|0.229|2.287
writing               |0.348|3.750|39.447
suma                  |0.618|6.249|66.741

### Result: custom Vector works faster than std::vector container

## You can find setup file in branch v3.0_setup









