#ifndef FORWARD_LIST_HPP_GUARD_
#define FORWARD_LIST_HPP_GUARD_

#include <initializer_list>
#include <cassert>
#include <stdexcept>
#include <iostream>

namespace ds
{
    template <typename ValueType>
    class forward_list
    {
    public:
        // Public Methods (Interface)

        /* Constructors;
         * Gang of Three (Four with assignement operator)
         */

        // Default: constructs an empty container.
        forward_list();

        // Fill ctor: constructs a container with n elements with given value
        forward_list(unsigned int n, const ValueType &val);

        // IL ctor: constructs a container with the elements from the il
        forward_list(const std::initializer_list<ValueType> &il);

        // Copy ctor:
        forward_list(const forward_list<ValueType> &other);

        // Assignement operator
        forward_list<ValueType> &operator=(const forward_list<ValueType> &other);

        ~forward_list() { clear(); };

        /* Insert methods */

        // Add new element at the begining (head)
        void push_front(const ValueType &el);

        // Add new element at the end (tail)
        void push_back(const ValueType &el);

        /* Remove methods */

        // Remove the element at the begining
        void pop_front();

        // Clear the container contet
        void clear();

        /* Element access methods */

        const ValueType &front() const;
        ValueType &front();

        /* Information methods */

        // Check if the container is empty
        bool empty() const;

        // Return the size (count of elements) in the container
        unsigned int size() const;

        // Print the forward_list to a given stream
        // The ValueType must have predefined operator <<
        void print(std::ostream &out) const;

        /* Algorithms */
        void reverse();

        /* Helpers */
    private:
        void copy(const forward_list<ValueType> &other);

    private:
        struct Node
        {
            Node(const ValueType &data, Node *pNext = nullptr)
                : data(data), pNext(pNext) {}

            ValueType data;
            Node *pNext;
        };

        Node *head;
        Node *tail;
        unsigned int m_size;
    };

    /* One-definition rule (ODR) <=> inline */

    template <typename ValueType>
    inline forward_list<ValueType>::forward_list()
        : head(nullptr), tail(nullptr), m_size(0) {}

    template <typename ValueType>
    inline forward_list<ValueType>::forward_list(unsigned int n, const ValueType &val)
        : head(nullptr), tail(nullptr), m_size(0)
    {
        for (int i = 0; i < n; i++)
            push_back(val);
    }

    template <typename ValueType>
    inline forward_list<ValueType>::forward_list(const std::initializer_list<ValueType> &il)
        : head(nullptr), tail(nullptr), m_size(0)
    {
        for (const ValueType &val : il)
            push_back(val);
    }

    template <typename ValueType>
    inline forward_list<ValueType>::forward_list(const forward_list<ValueType> &other)
        : head(nullptr), tail(nullptr), m_size(0)
    {
        if (other.m_size) 
        {
        copy(other);
        }
    }

    template <typename ValueType>
    inline forward_list<ValueType> &forward_list<ValueType>::operator=(const forward_list<ValueType> &other)
    {
        if (this != &other)
        {
            clear();
            copy(other);
        }

        return *this;
    }

    template <typename ValueType>
    inline void forward_list<ValueType>::copy(const forward_list<ValueType> &other)
    {
        try
        {
            head = new Node(other.head->data);
            tail = head;
            ++m_size;

            Node *toCopy = other.head;

            while (toCopy->pNext) // != nullptr
            {
                toCopy = toCopy->pNext;

                tail->pNext = new Node(toCopy->data);
                tail = tail->pNext;
                ++m_size;
            }
        }
        catch (...)
        {
            this->clear();
            throw;
        }
    }

    template <typename ValueType>
    inline void forward_list<ValueType>::clear()
    {
        while (!empty())
        {
            pop_front();
        }

        head = nullptr;
        tail = nullptr;
        m_size = 0;
    }

    template <typename ValueType>
    inline void forward_list<ValueType>::pop_front()
    {
        if (empty())
        {
            throw std::logic_error("Cannot perform pop_front : list is empty!");
        }

        Node *toDestroy = head;
        head = head->pNext;
        delete toDestroy;
        --m_size;

        // Otherwise tail would be a dangling pointer
        if (head == nullptr)
        {
            assert(size() == 0);
            tail = nullptr;
        }
    }

    template <typename ValueType>
    inline void forward_list<ValueType>::push_front(const ValueType &el)
    {
        head = new Node(el, head);
        if (size() == 0)
        {
            tail = head;
        }

        ++m_size;
    }

    template <typename ValueType>
    inline void forward_list<ValueType>::push_back(const ValueType &el)
    {
        if (empty())
        {
            assert(head == nullptr);
            assert(tail == nullptr);

            push_front(el);
        }
        else
        {
            tail->pNext = new Node(el);
            tail = tail->pNext;

            ++m_size;
        }
    }

    template <typename ValueType>
    inline bool forward_list<ValueType>::empty() const
    {
        return m_size == 0;
    }

    template <typename ValueType>
    inline unsigned int forward_list<ValueType>::size() const
    {
        return m_size;
    }

    template <typename ValueType>
    inline ValueType &forward_list<ValueType>::front()
    {
        assert(head != nullptr);

        if (!empty())
        {
            return head->data;
        }

        throw std::logic_error("Cannot access element: list is empty!");
    }

    template <typename ValueType>
    inline const ValueType &forward_list<ValueType>::front() const
    {
        return const_cast<forward_list &>(*this).front();
    }

    template <typename ValueType>
    void forward_list<ValueType>::print(std::ostream &out) const
    {
        try
        {
            // TODO: Write and use iterators.
            Node *toPrint = head;
            while (toPrint)
            {
                out << toPrint->data << " "; // Error-prone (operator<< is necessary)
                toPrint = toPrint = toPrint->pNext;
            }

            out << std::endl;
        }
        catch (...)
        {
            std::cerr << "Printing error occurred!" << std::endl;
            throw;
        }
    }

    template <typename ValueType>
    inline void forward_list<ValueType>::reverse()
    {
        Node *cur = head;
        if (head == nullptr || head == tail)
        {
            return;
        }

        Node *lastNode = nullptr;
        Node *next = cur->pNext;
        while (cur != tail)
        {
            cur->pNext = lastNode;
            lastNode = cur;
            cur = next;
            next = cur->pNext;
        }

        std::swap(head, tail);
        head->pNext = lastNode;
    }

} // namespace ds

#endif // FORWARD_LIST_HPP_GUARD_
