
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

    void push_back(const T &value)
    {
        if (size_ == capacity_)
        {
            T *new_arr = new T[capacity_ * 2];
            for (int i = 0; i < size_; i++)
            {
                new_arr[i] = arr_[i];
            }
            delete[] arr_;
            arr_ = new_arr;
            capacity_ *= 2;
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
                T *new_arr = new T[count];
                for (int i = 0; i < size_; i++)
                {
                    new_arr[i] = arr_[i];
                }
                delete[] arr_;
                arr_ = new_arr;
                capacity_ = count;
            }
            for (int i = size_; i < count; i++)
            {
                arr_[i] = value;
            }
            size_ = count;
        }
    }
};