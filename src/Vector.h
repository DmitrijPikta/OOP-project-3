#include <initializer_list>

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

    Vector(std::initializer_list<T> init)
    {
        size_ = static_cast<int>(init.size());
        capacity_ = size_ > 0 ? size_ : 1;
        arr_ = new T[capacity_];

        int i = 0;
        for (const auto &val : init)
        {
            arr_[i++] = val;
        }
    }

    Vector(const Vector &other)
    {
        capacity_ = other.capacity_;
        size_ = other.size_;
        arr_ = new T[capacity_];
        for (int i = 0; i < size_; i++)
        {
            arr_[i] = other.arr_[i];
        }
    }

    Vector(Vector &&other) noexcept : arr_(other.arr_), capacity_(other.capacity_), size_(other.size_)
    {
        other.arr_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
    }

    ~Vector()
    {
        clear();
        delete[] arr_;
    }

    int size() const
    {
        return size_;
    }

    int capacity() const
    {
        return capacity_;
    }

    void reserve(size_t new_capacity)
    {
        if (new_capacity <= capacity_)
            return;

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

    const T *end() const
    {
        return arr_ + size_;
    }

    T *begin()
    {
        return arr_;
    }

    const T *begin() const
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

    const T &front() const
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

    const T &back() const
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

    bool empty() const
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
        for (int i = 0; i < size_; i++)
        {
            arr_[i].~T();
        }
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

    T &at(int index)
    {
        if (index < 0 || index >= size_)
        {
            throw std::out_of_range("Index out of range");
        }
        return arr_[index];
    }

    const T &at(int index) const
    {
        if (index < 0 || index >= size_)
        {
            throw std::out_of_range("Index out of range");
        }
        return arr_[index];
    }

    Vector &operator=(const Vector &other)
    {
        if (this != &other)
        {
            delete[] arr_;
            capacity_ = other.capacity_;
            size_ = other.size_;
            arr_ = new T[capacity_];
            for (int i = 0; i < size_; i++)
            {
                arr_[i] = other.arr_[i];
            }
        }
        return *this;
    }

    Vector &operator=(Vector &&other) noexcept
    {
        if (this != &other)
        {
            delete[] arr_;
            arr_ = other.arr_;
            capacity_ = other.capacity_;
            size_ = other.size_;
            other.arr_ = nullptr;
            other.capacity_ = 0;
            other.size_ = 0;
        }
        return *this;
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

    bool operator>(const Vector &other) const
    {
        int min_size = (size_ < other.size_) ? size_ : other.size_;

        for (int i = 0; i < min_size; i++)
        {
            if (arr_[i] > other[i])
            {
                return true;
            }
            else if (arr_[i] < other[i])
            {
                return false;
            }
        }

        return size_ > other.size_;
    }

    bool operator<(const Vector &other) const
    {
        int min_size = (size_ < other.size_) ? size_ : other.size_;

        for (int i = 0; i < min_size; ++i)
        {
            if (arr_[i] < other[i])
            {
                return true;
            }
            if (arr_[i] > other[i])
            {
                return false;
            }
        }

        return size_ < other.size_;
    }

    bool operator>=(const Vector &other) const
    {
        return !(*this < other);
    }

    bool operator<=(const Vector &other) const
    {
        return !(*this > other);
    }

    void swap(Vector &other)
    {
        std::swap(arr_, other.arr_);
        std::swap(capacity_, other.capacity_);
        std::swap(size_, other.size_);
    }

    void assign(const size_t count, const T &value)
    {
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

    template <typename... Args>
    void emplace(int index, Args &&...args)
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

        arr_[index] = T(std::forward<Args>(args)...);
        size_++;
    }

    template <typename... Args>
    void emplace_back(Args &&...args)
    {
        if (size_ == capacity_)
        {
            reserve(capacity_ * 2);
        }

        arr_[size_] = T(std::forward<Args>(args)...);
        size_++;
    }
};