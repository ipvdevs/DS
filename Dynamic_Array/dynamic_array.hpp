#ifndef DYNAMIC_ARRAY_GUARD
#define DYNAMIC_ARRAY_GUARD

#include <iostream>         // Debug errors
#include <initializer_list> // C++ 11

#define INIT_CAPACITY 16

namespace ds
{
    template <class T>
    class dynamic_array
    {
    public:
        // Constructors, Destructors; Gang of Four

        // Default - Constructs an empty container with selected or default initial capacity
        explicit dynamic_array(unsigned int capacity = INIT_CAPACITY);

        // Fill Constructor
        explicit dynamic_array(unsigned int capacity, const T &element);

        // Constructs a container with a copy of each of the elements in il, in the same order.
        dynamic_array(const std::initializer_list<T> &i_list);

        // Constructs a container with a copy of each of the elements and keep the original order
        dynamic_array(const dynamic_array<T> &other);

        // Copy assignment operator (copy-and-swap idiom)
        dynamic_array<T> &operator=(dynamic_array<T> other);

        // Destructor
        ~dynamic_array();

        // Dynamic Array Basic Operations
        void push_back(const T &el);

        // Access operators
        const T &operator[](unsigned int index) const;
        T &operator[](unsigned int index);

        const T &at(unsigned int index) const;
        T &at(unsigned int index);

        // Remove operations
        void pop_back();

        void clear();

        // Debug info methods
    public:
        void printInfo(std::ostream &os) const;
        void printElements(std::ostream &os) const;

    private:
        T *data;
        unsigned int size, capacity;
        // iterator

        ///
        // Helpers
        void copyFrom(const dynamic_array<T> &src);
        friend void swap(dynamic_array &first, dynamic_array &second)
        {
            using std::swap;
            swap(first.data, second.data);         // Swaps data pointers
            swap(first.capacity, second.capacity); // Swaps capacity
            swap(first.size, second.size);         // Swaps size
        }
        void reserveSize();
    };

    /* one-definition rule (ODR) <=> inline */
    /* new T <=> throws bad_alloc if allocation functions report failure to allocate storage.*/

    template <class T>
    inline dynamic_array<T>::dynamic_array(unsigned int capacity)
        : capacity(capacity), size(0)
    {
        if (capacity == 0)
            throw std::invalid_argument("Invalid initial capacity!");

        data = new T[capacity];
    }

    template <class T>
    inline dynamic_array<T>::dynamic_array(unsigned int capacity, const T &element)
        : capacity(capacity), size(capacity)
    {
        if (capacity == 0)
            throw std::invalid_argument("Invalid initial capacity!");

        data = new T[capacity];
        // T::operator= might fail to copy and throw exception
        try
        {
            for (unsigned int i = 0; i < size; i++)
                data[i] = element;
        }
        catch (...)
        {
            std::cout << "Invalid object copy operation!" << std::endl;
            throw; // Rethrow the exception
        }
    }

    template <class T>
    inline dynamic_array<T>::dynamic_array(const std::initializer_list<T> &i_list)
        : dynamic_array(i_list.size())
    {
        // T::operator= might fail to copy and throw exception.
        // The size would track the successfully copied data.
        for (const T &el : i_list)
        {
            data[size] = el;
            ++size;
        }
    }

    template <class T>
    inline dynamic_array<T>::dynamic_array(const dynamic_array<T> &other)
    {
        this->copyFrom(other);
    }

    // Copy-And-Swap idiom
    // The copy-swap idiom provides exception-safe copying.
    // It requires that a correct copy ctor and swap are implemented.
    // https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
    template <class T>
    inline dynamic_array<T> &dynamic_array<T>::operator=(dynamic_array<T> other)
    {
        swap(*this, other);

        return *this;
    }

    template <class T>
    inline dynamic_array<T>::~dynamic_array()
    {
        this->clear();
    }

    // Default Dynamic Array Operations

    template <class T>
    inline void dynamic_array<T>::push_back(const T &el)
    {
        if (size >= capacity)
        {
            reserveSize();
        }

        data[size] = el;
        ++size;
    }

    template <class T>
    inline void dynamic_array<T>::pop_back()
    {
        if (size == 0)
            throw std::logic_error("Invalid opration: Cannot pop from empty array!");

        --size;
    }

    template <class T>
    inline void dynamic_array<T>::clear()
    {
        delete[] data;
        data = nullptr;
        size = 0;
        capacity = 0;
    }

    // Helpers
    template <class T>
    inline void dynamic_array<T>::copyFrom(const dynamic_array<T> &src)
    {
        capacity = src.capacity;
        data = new T[capacity];
        for (unsigned int i = 0; i < src.size; i++)
        {
            data[i] = src.data[i];
        }

        size = src.size;
    }

    template <class T>
    inline void dynamic_array<T>::reserveSize()
    {
        unsigned int newCapacity = capacity ? capacity * 2 : INIT_CAPACITY;
        T *temp = new T[newCapacity];

        for (unsigned int i = 0; i < size; i++)
        {
            temp[i] = data[i];
        }

        delete[] data;
        data = temp;

        capacity = newCapacity;
    }

    // Access operations (operator [], front, back, at)
    template <typename T>
    inline const T &dynamic_array<T>::operator[](unsigned int index) const
    {
        if (index >= size)
            throw std::out_of_range("Invalid index!");

        return data[index];
    }

    template <typename T>
    inline T &dynamic_array<T>::operator[](unsigned int index)
    {
        if (index >= size)
            throw std::out_of_range("Invalid index!");

        return data[index];
    }

    template <typename T>
    inline const T &dynamic_array<T>::at(unsigned int index) const
    {
        return this->operator[](index);
    }

    template <typename T>
    inline T &dynamic_array<T>::at(unsigned int index)
    {
        return this->operator[](index);
    }

    // Debug Info
    template <typename T>
    inline void dynamic_array<T>::printInfo(std::ostream &os) const
    {
        os << "Obj at : 0x" << this << "\nBuffer on address 0x" << data << "\nSize: " << size << "\nCapacity: " << capacity << std::endl;
    }

    template <typename T>
    inline void dynamic_array<T>::printElements(std::ostream &os) const
    {
        if (size == 0)
        {
            os << "[]" << std::endl;
            return;
        }

        if (size == 1)
        {
            os << '[' << data[0] << ']' << std::endl;
            return;
        }

        os << "[ ";
        for (size_t i = 0; i < size - 1; i++)
            os << data[i] << ", ";
        os << data[size - 1] << " ]" << std::endl;
    }

};

#endif // DYNAMIC_ARRAY_GUARD