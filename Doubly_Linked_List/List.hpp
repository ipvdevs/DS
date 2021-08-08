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

                return *ptr;
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
                if (ptr != head)
                    ptr = ptr->prev;

                return *ptr;
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

        void insert();

        // Appends the given element value to the end (tail) of the list.
        void push_back(const ValueType &);

        /* Information methods */

        size_t size() const;

        bool empty() const;

    private:
        // Concealing the Node class from the user.
        // The List class is responsible for nodes.
        class Node
        {
        public:
            Node(const ValueType &data, Node *prev = nullptr, Node *next = nullptr)
                : data(data), prev(prev), next(next) {}

        private:
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
    inline void List<ValueType>::push_back(const ValueType &value)
    {
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