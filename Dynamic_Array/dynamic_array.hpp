#ifndef DYNAMIC_ARRAY_GUARD
#define DYNAMIC_ARRAY_GUARD

/*   
 *  Random access sequence container (array)
 *  that can automatically handle its size when needed.
*/

#include <iostream>         // Debugging
#include <initializer_list> // C++ 11

namespace ds
{

#define INIT_CAPACITY 16
#define GROWTH_RATE 2

    template <class T>
    class dynamic_array
    {
    public:
        // Constructors, Destructors; Gang of Four

        // Default - Constructs an empty container with selected or default initial m_capacity
        explicit dynamic_array(unsigned int m_capacity = INIT_CAPACITY);

        // Fill Constructor
        explicit dynamic_array(unsigned int m_capacity, const T &element);

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

        ///
        // Access operators
        const T &operator[](unsigned int index) const;
        T &operator[](unsigned int index);

        const T &at(unsigned int index) const;
        T &at(unsigned int index);

        // Access first element
        const T &front() const;
        T &front();

        // Access last element
        const T &back() const;
        T &back();

        ///
        // Remove operations
        void pop_back();

        void clear();

        ///
        // Information methods
        unsigned int size() const;

        unsigned int capacity() const;

        bool empty() const;

        int find() const;

        // Debug info methods
    public:
        void printInfo(std::ostream &os) const;

    private:
        T *data;
        unsigned int m_size, m_capacity;

        ///
        // Helpers
    private:
        void copyFrom(const dynamic_array<T> &src);
        friend void swap(dynamic_array &first, dynamic_array &second)
        {
            using std::swap;
            swap(first.data, second.data);             // Swaps data pointers
            swap(first.m_capacity, second.m_capacity); // Swaps m_capacity
            swap(first.m_size, second.m_size);         // Swaps m_size
        }
        void reserve_size();
    };

    /* one-definition rule (ODR) <=> inline */
    /* new T <=> throws bad_alloc if allocation functions report failure to allocate storage.*/

    template <class T>
    inline dynamic_array<T>::dynamic_array(unsigned int m_capacity)
        : m_capacity(m_capacity), m_size(0)
    {
        if (m_capacity == 0)
            throw std::invalid_argument("Invalid initial m_capacity!");

        data = new T[m_capacity];
    }

    template <class T>
    inline dynamic_array<T>::dynamic_array(unsigned int m_capacity, const T &element)
        : m_capacity(m_capacity), m_size(m_capacity)
    {
        if (m_capacity == 0)
            throw std::invalid_argument("Invalid initial m_capacity!");

        data = new T[m_capacity];
        // T::operator= might fail to copy and throw exception
        try
        {
            for (unsigned int i = 0; i < m_size; i++)
                data[i] = element;
        }
        catch (...)
        {
            std::cerr << "Invalid object copy operation!" << std::endl;
            throw; // Rethrow the exception
        }
    }

    template <class T>
    inline dynamic_array<T>::dynamic_array(const std::initializer_list<T> &i_list)
        : dynamic_array(i_list.size())
    {
        // T::operator= might fail to copy and throw exception.
        // The m_size would track the successfully copied data.
        for (const T &el : i_list)
        {
            data[m_size] = el;
            ++m_size;
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

    // Amortized constant complexity O(1)
    template <class T>
    inline void dynamic_array<T>::push_back(const T &el)
    {
        if (m_size >= m_capacity)
        {
            reserve_size();
        }

        data[m_size] = el;
        ++m_size;
    }

    // O(1) - Constant time
    template <class T>
    inline void dynamic_array<T>::pop_back()
    {
        if (m_size == 0)
            throw std::logic_error("Invalid opration: Cannot pop from empty array!");

        --m_size;
    }

    // O(1) - Constant time
    template <class T>
    inline void dynamic_array<T>::clear()
    {
        delete[] data;
        data = nullptr;
        m_size = 0;
        m_capacity = 0;
    }

    // Helpers

    // O(n) - Linear time
    template <class T>
    inline void dynamic_array<T>::copyFrom(const dynamic_array<T> &src)
    {
        m_capacity = src.m_capacity;
        data = new T[m_capacity]; // Might throw bad_alloc
        for (unsigned int i = 0; i < src.m_size; i++)
        {
            data[i] = src.data[i];
        }

        // Sets m_size after successfully assignment of the data
        m_size = src.m_size;
    }

    template <class T>
    inline void dynamic_array<T>::reserve_size()
    {
        unsigned int new_capacity = m_capacity ? m_capacity * GROWTH_RATE : INIT_CAPACITY;
        T *temp = new T[new_capacity];

        for (unsigned int i = 0; i < m_size; i++)
            temp[i] = data[i];

        delete[] data;
        data = temp;

        m_capacity = new_capacity;
    }

    // Random access operations (operator [], front, back, at)

    // O(1) - Constant time
    template <class T>
    inline const T &dynamic_array<T>::operator[](unsigned int index) const
    {
        if (index >= m_size)
            throw std::out_of_range("Invalid index!");

        return data[index];
    }

    // O(1) - Constant time
    template <class T>
    inline T &dynamic_array<T>::operator[](unsigned int index)
    {
        if (index >= m_size)
            throw std::out_of_range("Invalid index!");

        return data[index];
    }

    // O(1) - Constant time
    template <class T>
    inline const T &dynamic_array<T>::at(unsigned int index) const
    {
        return this->operator[](index);
    }

    // O(1) - Constant time
    template <class T>
    inline T &dynamic_array<T>::at(unsigned int index)
    {
        return this->operator[](index);
    }

    // O(1) - Constant time
    template <class T>
    inline T &dynamic_array<T>::front()
    {
        if (m_size == 0)
            throw std::logic_error("Invalid opration: empty array!");

        return data[0];
    }

    // O(1) - Constant time
    template <class T>
    inline const T &dynamic_array<T>::front() const
    {
        if (m_size == 0)
            throw std::logic_error("Invalid opration: empty array!");

        return data[0];
    }

    // O(1) - Constant time
    template <class T>
    inline T &dynamic_array<T>::back()
    {
        if (m_size == 0)
            throw std::logic_error("Invalid opration: empty array!");

        return data[m_size - 1];
    }

    // O(1) - Constant time
    template <class T>
    inline const T &dynamic_array<T>::back() const
    {
        if (m_size == 0)
            throw std::logic_error("Invalid opration: empty array!");

        return data[m_size - 1];
    }

    // O(1) - Constant time
    template <class T>
    inline unsigned int dynamic_array<T>::size() const
    {
        return m_size;
    }

    template <class T>
    inline unsigned int dynamic_array<T>::capacity() const
    {
        return m_capacity;
    }

    // O(1) - Constant time
    template <class T>
    inline bool dynamic_array<T>::empty() const
    {
        return m_size == 0;
    }

    // Debug Info
    template <typename T>
    inline void dynamic_array<T>::printInfo(std::ostream &os) const
    {
        os << "Address: 0x" << this << "\nBuffer Address 0x" << data << "\nm_size: " << m_size << "\nm_capacity: " << m_capacity << std::endl;
    }
};

#endif // DYNAMIC_ARRAY_GUARD