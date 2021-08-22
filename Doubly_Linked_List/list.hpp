#ifndef LIST_HPP_GUARD_
#define LIST_HPP_GUARD_

/* Exception handling */
#include <cassert>
#include <stdexcept>

/* Initializer list */
#include <initializer_list>

namespace ds
{
    template <typename ValueType>
    class List
    {
        // Forward declaration
        class Node;

    public:
        /* Constructors & Destructor & Rule of three (four) */

        // Default constructor
        // Constructs an empty doubly linked list
        List();

        // Fill constructor
        // Constructs a doubly linked list with count copies of elements with given value
        List(size_t count, const ValueType &value);

        // Initializer list constructor
        // Constructs a list with the elements from the il
        List(const std::initializer_list<ValueType> &il);

        // Copy constructor (rule of three)
        // Constructs a list - clone of a given source list
        List(const List &other);

        // Assignment operator (rule of four)
        // Replaces the contents of the list with a copy of the contents of another list
        // Using the copy-swap idiom (copy epsilon version)
        List<ValueType> &operator=(List other);

        // Exchanges the contents of two lists
        // Size may differ
        void swap(List &other); // nothrow

        ~List() { clear(); };

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

        // Returns an iterator to the first element (head) of the list
        // If the list is empty begin() is equal to end()
        Iterator begin() const { return Iterator(head); };

        // Returns iterator pointing to the past tail element
        Iterator end() const { return Iterator(); };

        /* Access methods */

        // Returns a reference to the first (head) element in the list
        ValueType &front();
        const ValueType &front() const;

        // Returns a reference to the last (tail) element in the list
        ValueType &back();
        const ValueType &back() const;

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

        // Remove methods

        // Removes value at given position (pos)
        // Time complexity: O(1)
        Iterator erase(Iterator pos);

        // Removes the element at the beginning (head) of the list
        // Time complexity: O(1)
        void pop_front();

        // Removes the element before the end (tail) of the list
        // Time complexity: O(1)
        void pop_back();

        // Removes all elements from the list, leaving the container empty
        // Time complexity: O(n)
        void clear();

        /* Information methods */

        // Retrieve the current count of the elements in the list.
        // Time complexity: O(1)
        size_t size() const;

        // Check if the list is currently empty.
        // Time complexity: O(1)
        bool empty() const;

        /* Operations */

        // Transfer elements from given list, inserting them at a selected position.
        // Time complexity: Up to O(m), where m is the size of the transferred list
        void splice(Iterator position, const List &src);

        // Transfer elements from given list range [first, last),
        // inserting them at a selected position.
        // Time complexity: Up to O(m), where m is the size of the transferred list
        void splice(Iterator position, const List &src, Iterator first, Iterator last);

        // Remove all elements from the list with a specified value
        // Time complexity: O(n)
        void remove(const ValueType &val);

        // Helpers
    private:
        void copyFrom(const List &src);

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
    inline List<ValueType>::List(const std::initializer_list<ValueType> &il)
        : List()
    {
        for (const ValueType &el : il)
            push_back(el);
    }

    template <typename ValueType>
    inline List<ValueType>::List(const List &other)
        : List()
    {
        copyFrom(other);
    }

    template <typename ValueType>
    inline List<ValueType> &List<ValueType>::operator=(List other)
    {
        other.swap(*this); // Non-throwing swap

        return *this;
    }

    template <typename ValueType>
    void List<ValueType>::swap(List &other) // nothrow
    {
        using std::swap;
        swap(this->m_size, other.m_size);
        swap(this->head, other.head);
        swap(this->tail, other.tail);
    }

    template <typename ValueType>
    void List<ValueType>::clear()
    {
        while (!empty())
            pop_front();
    }

    template <typename ValueType>
    void List<ValueType>::copyFrom(const List &src)
    {
        if (src.empty())
            return;

        // This method is meant to copyFrom from another list source,
        // but is not responsible for freeing the occupied memory
        // of the current list, consequently if it is not used on an
        // empty list, memory leaks are possible.

        head = new Node(src.head->data);
        tail = head;
        ++m_size;

        Node *toCopy = src.head->next;
        while (toCopy)
        {
            tail->next = new Node(toCopy->data, tail);
            tail = tail->next;
            ++m_size;

            toCopy = toCopy->next;
        }
    }

    template <typename ValueType>
    inline typename List<ValueType>::Iterator List<ValueType>::insert(Iterator pos, const ValueType &value)
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
        if (empty())
        {
            // List is empty.
            // Regardless of the given pos, create a list with one element with
            // the specified value.

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
    inline typename List<ValueType>::Iterator List<ValueType>::erase(Iterator pos)
    {
        if (empty() || pos.ptr == nullptr)
            return end();

        Node *toRemove = nullptr;

        if (pos.ptr == head)
        {
            toRemove = head;

            head = head->next;
            if (head)
            {
                head->prev = nullptr;
            }
            else
            {
                tail = nullptr;
            }

            delete toRemove;
            --m_size;

            return begin();
        }
        else if (pos.ptr == tail)
        {
            toRemove = tail;

            tail = tail->prev;

            if (tail)
            {
                tail->next = nullptr;
            }
            else
            {
                head = nullptr;
            }

            delete toRemove;
            --m_size;

            return end();
        }
        else
        {
            Node *prev = pos.ptr->prev, *next = pos.ptr->next;

            toRemove = pos.ptr;
            prev->next = pos.ptr->next;
            next->prev = pos.ptr->prev;
            pos.ptr = pos.ptr->next;

            delete toRemove;
            --m_size;

            return Iterator(pos.ptr);
        }
    }

    template <typename ValueType>
    inline void List<ValueType>::pop_front()
    {
        if (empty())
        {
            throw std::logic_error("pop_front(): Cannot perform pop. The list is empty!");
        }

        erase(begin());
    }

    template <typename ValueType>
    inline void List<ValueType>::pop_back()
    {
        if (empty())
        {
            throw std::logic_error("pop_back(): Cannot perform pop. The list is empty!");
        }

        erase(Iterator(tail));
    }

    template <typename ValueType>
    inline ValueType &List<ValueType>::front()
    {
        if (empty())
        {
            throw std::logic_error("front(): Cannot access an element. The list is empty!");
        }

        return head->data;
    }

    template <typename ValueType>
    inline const ValueType &List<ValueType>::front() const
    {
        return const_cast<List<ValueType> &>(*this).front();
    }

    template <typename ValueType>
    inline ValueType &List<ValueType>::back()
    {
        if (empty())
        {
            throw std::logic_error("back(): Cannot access an element. The list is empty!");
        }

        return tail->data;
    }

    template <typename ValueType>
    inline const ValueType &List<ValueType>::back() const
    {
        return const_cast<List<ValueType> &>(*this).back();
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

    template <typename ValueType>
    inline void List<ValueType>::splice(Iterator position, const List<ValueType> &src)
    {
        splice(position, src, src.begin(), src.end());
    }

    template <typename ValueType>
    inline void List<ValueType>::splice(Iterator position, const List &src, Iterator first, Iterator last)
    {
        for (Iterator itr = first; itr != last; ++itr)
            insert(position, *itr);
    }

    template <typename ValueType>
    inline void List<ValueType>::remove(const ValueType &val)
    {
        Iterator itr = begin();

        while (itr != end())
        {
            if (*itr == val)
            {
                itr = erase(itr);
            }
            else
            {
                ++itr;
            }
        }
    }

} // namespace ds

#endif // LIST_HPP_GUARD_