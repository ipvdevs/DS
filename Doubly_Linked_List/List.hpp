#ifndef LIST_HPP_GUARD_
#define LIST_HPP_GUARD_

/* Exception handling */
#include <cassert>
#include <stdexcept>

namespace ds
{
    template <typename ValueType>
    class List
    {
        // Forward declaration
        class Node;

    public:
        /* Constructors & Destructor & Rule of three (four) */

        // Default constructor.
        // Constructs an empty doubly linked list
        List();

        // Fill constructor.
        // Constructs a doubly linked list with count copies of elements with given value.
        List(size_t count, const ValueType &value);

        /* Bidirectional iterator */
        class Iterator
        {
            // A friend class is allowed to access any private member.
            // Giving List such access to control the iterator.
            friend List;

        public:
            typedef ValueType &reference;
            typedef ValueType *pointer;

            // This operator allows modify access to the data of each node
            reference operator*() const { return ptr->data; }
            pointer operator->() { return &ptr->data; };

            // Prefix increment - increment only if end is not reached
            Iterator &operator++()
            {
                if (ptr)
                    ptr = ptr->next;

                return *this;
            }

            // Postfix increment
            Iterator operator++(int)
            {
                Iterator copy(*this); // Defaul copy constructor is called.
                ++(*this);            // Calling the prefix increment with
                                      // the nullptr check gurantee.
                return copy;
            }

            // Prefix decrement - decrement only if it is not pointng the begining
            Iterator &operator--()
            {
                if (ptr)
                    ptr = ptr->prev;

                return *this;
            }

            // Postfix decrement
            Iterator operator--(int)
            {
                Iterator copy(*this); // Defaul copy constructor is called.
                --(*this);            // Calling the prefix decrement with
                                      // the begin check gurantee.

                return copy;
            }

            // Comparison operators
            bool operator==(const Iterator &rhs) const { return ptr == rhs.ptr; }
            bool operator!=(const Iterator &rhs) const { return !(*this == rhs); }

        private:
            // Concealing the Iterator constructor from the user.
            Iterator(Node *ptr = nullptr)
                : ptr(ptr) {}

            Node *ptr;
        };

        // Returns an iterator to the first element (head) of the list.
        // If the list is empty begin() is equal to end().
        Iterator begin() const { return Iterator(head); };

        // Returns iterator pointing to the past tail element.
        Iterator end() const { return Iterator(); };

        /* Modifiers */

        // Insert methods

        // Inserts value before given position (pos)
        // Time complexity: O(1)
        Iterator insert(Iterator pos, const ValueType &value);

        // Appends the given element value to the end (tail) of the list.
        // Time complexity: O(1)
        void push_back(const ValueType &);

        // Add new element at the begining (head) of the list
        // Time complexity: O(1)
        void push_front(const ValueType &);

        /* Information methods */

        // Retrieve the current count of the elements in the list.
        // Time complexity: O(1)
        size_t size() const;

        // Check if the list is currently empty.
        // Time complexity: O(1)
        bool empty() const;

    private:
        struct Node
        {
            Node(const ValueType &data, Node *prev = nullptr, Node *next = nullptr)
                : data(data), prev(prev), next(next) {}

            ValueType data;
            Node *prev;
            Node *next;
        };

        Node *head;
        Node *tail;
        size_t m_size;
    };

    template <typename ValueType>
    inline List<ValueType>::List()
        : head(nullptr), tail(nullptr), m_size(0) {}

    template <typename ValueType>
    inline List<ValueType>::List(size_t count, const ValueType &value)
        : List()
    {
        for (size_t i = 0; i < count; i++)
            push_back(value);
    }

    template <typename ValueType>
    typename List<ValueType>::Iterator List<ValueType>::insert(Iterator pos, const ValueType &value)
    {
        if (pos == nullptr)
        {
            push_back(value);
            return Iterator(tail);
        }
        else if (pos.ptr == head)
        {
            head->prev = new Node(value, nullptr, head);
            head = head->prev;
            ++m_size;

            return Iterator(head);
        }
        else
        {
            Node *prev = pos.ptr->prev;
            pos.ptr->prev = new Node(value, prev, pos.ptr);
            prev->next = pos.ptr->prev;

            ++m_size;
            return Iterator(pos.ptr->prev);
        }
    }

    template <typename ValueType>
    inline void List<ValueType>::push_back(const ValueType &value)
    {
        if (m_size == 0)
        {
            assert(head == nullptr);
            assert(tail == nullptr);

            head = new Node(value);
            tail = head;
        }
        else
        {
            tail->next = new Node(value, tail);
            tail = tail->next;
        }

        ++m_size;
    }

    template <typename ValueType>
    inline void List<ValueType>::push_front(const ValueType &value)
    {
        insert(Iterator(head), value);
    }

    template <typename ValueType>
    inline size_t List<ValueType>::size() const
    {
        return m_size;
    }

    template <typename ValueType>
    inline bool List<ValueType>::empty() const
    {
        return m_size == 0;
    }

} // namespace ds

#endif // LIST_HPP_GUARD_
