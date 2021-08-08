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
        private:
            // Concealing the Iterator constructor from the user.
            Iterator(Node *ptr = nullptr)
                : ptr(ptr) {}

            Node *ptr;
        };

        Iterator begin() const { return Iterator(head); };

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