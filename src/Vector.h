
template <typename T>
class Vector
{
private:
    T *arr_;
    int capacity_;
    int size_;

public:
    Vector()
    {
        arr_ = new T[1];
        capacity_ = 1;
        size_ = 0;
    }

    ~Vector()
    {
        delete[] arr_;
    }

    int size()
    {
        return size_;
    }

    int capacity()
    {
        return capacity_;
    }

    void reserve(size_t new_capacity)
    {
        T *new_arr = new T[new_capacity];
        for (int i = 0; i < size_; i++)
        {
            new_arr[i] = arr_[i];
        }
        delete[] arr_;
        arr_ = new_arr;
        capacity_ = new_capacity;
    }

    void push_back(const T &value)
    {
        if (size_ == capacity_)
        {
            reserve(capacity_ * 2);
        }
        arr_[size_++] = value;
    }

    void pop_back()
    {
        if (size_ > 0)
        {
            size_--;
        }
    }

    T *end()
    {
        return arr_ + size_;
    }

    T *begin()
    {
        return arr_;
    }

    T &front()
    {
        if (size_ > 0)
        {
            return arr_[0];
        }
        throw std::out_of_range("Vector is empty");
    }

    T &back()
    {
        if (size_ > 0)
        {
            return arr_[size_ - 1];
        }
        throw std::out_of_range("Vector is empty");
    }

    void resize(int count, const T &value = T())
    {
        if (count < 0)
        {
            throw std::out_of_range("Size of vector can not be negative");
        }
        if (count == size_)
        {
            return;
        }
        else if (count < size_)
        {
            size_ = count;
            capacity_ = count;
        }
        else
        {
            if (count > capacity_)
            {
                reserve(count);
            }
            for (int i = size_; i < count; i++)
            {
                arr_[i] = value;
            }
            size_ = count;
        }
    }

    void insert(int index, const T &value)
    {
        if (index < 0 || index > size_)
        {
            throw std::out_of_range("Index out of range");
        }

        if (size_ == capacity_)
        {
            reserve(capacity_ * 2);
        }

        for (int i = size_; i > index; i--)
        {
            arr_[i] = arr_[i - 1];
        }
        arr_[index] = value;
        size_++;
    }

    bool empty()
    {
        return size_ == 0;
    }

    void shrink_to_fit()
    {
        if (capacity_ > size_)
        {
            reserve(size_);
        }
    }

    void clear()
    {
        size_ = 0;
    }

    void erase(int index)
    {
        if (index < 0 || index >= size_)
        {
            throw std::out_of_range("Index out of range");
        }

        for (int i = index; i < size_ - 1; i++)
        {
            arr_[i] = arr_[i + 1];
        }
        size_--;
    }

    T &operator[](int index)
    {
        if (index < 0 || index >= size_)
        {
            throw std::out_of_range("Index out of range");
        }
        return arr_[index];
    }

    const T &operator[](int index) const
    {
        if (index < 0 || index >= size_)
        {
            throw std::out_of_range("Index out of range");
        }
        return arr_[index];
    }

    bool operator==(const Vector &other) const
    {
        if (size_ != other.size_)
        {
            return false;
        }

        for (int i = 0; i < size_; i++)
        {
            if (arr_[i] != other[i])
            {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const Vector &other) const
    {
        return !(*this == other);
    }

    void swap(Vector &other)
    {
        std::swap(arr_, other.arr_);
        std::swap(capacity_, other.capacity_);
        std::swap(size_, other.size_);
    }

    void assign(const size_t count, const T &value)
    {
        if (count < 0)
        {
            throw std::out_of_range("Size of vector can not be negative");
        }

        if (count > capacity_)
        {
            reserve(count);
        }

        for (int i = 0; i < count; i++)
        {
            arr_[i] = value;
        }
        size_ = count;
    }
};