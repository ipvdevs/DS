#ifndef STACK_LINKED_GUARD
#define STACK_LINKED_GUARD

#include <stdexcept>

/* Basic LIFO - last-in first-out - linked stack */

namespace ds
{
    template <class DataType>
    class Stack
    {
    public:
        // Big Three (Four - Operator=)

        // Default ctor
        Stack() : tos(nullptr), m_size(0) {}

        // Copy ctor
        Stack(const Stack &other);

        // Assignment operator
        Stack &operator=(const Stack &other);

        // Destructor
        ~Stack();

        // Add new element to the top of the stack
        // Complexity: O(1) Constant
        void push(const DataType &element);

        // Remove the last element in the stack
        // Note: If DataType is too heavy VOID might be a better option
        // Complexity: O(1) Constant
        DataType pop();

        // Retrieve the size (count of elements) of the stack
        unsigned int size() const;

        // Check if the stack is currently empty
        bool empty() const;

        // Access the top element of the stack
        // Complexity: O(1) Constant
        DataType &top();

        // Access the top element of the stack
        // Complexity: O(1) Constant
        const DataType &top() const;

    private:
        struct Node
        {
            Node(const DataType &m_data, Node *link = nullptr)
                : m_data(m_data), link(link) {}

            DataType m_data;
            Node *link;
        };

        Node *tos = nullptr;     // top of stack
        unsigned int m_size = 0; // size of stack

        ///
        // Helpers
    private:
        void copyFrom(const Stack &src);
        void clear();
    };

    template <class DataType>
    inline Stack<DataType>::Stack(const Stack &other)
    {
        copyFrom(other);
    }

    template <class DataType>
    inline void Stack<DataType>::copyFrom(const Stack &src)
    {
        // New throws bad_alloc if allocation functions
        // report failure to allocate storage.

        Node *srcTos = src.tos;

        // Check if tos is not pointing to nullptr
        if (srcTos)
        {
            tos = new Node(srcTos->m_data);
            ++m_size;
            srcTos = srcTos->link;

            Node *prev = tos;

            // srcTos != nullptr
            while (srcTos)
            {
                prev->link = new Node(srcTos->m_data);
                ++m_size;

                prev = prev->link;
                srcTos = srcTos->link;
            }
        }
    }

    template <class DataType>
    inline Stack<DataType> &Stack<DataType>::operator=(const Stack &other)
    {
        if (this != &other)
        {
            this->clear();
            this->copyFrom(other);
        }

        return *this;
    }

    template <class DataType>
    inline Stack<DataType>::~Stack()
    {
        clear();
    }

    template <class DataType>
    inline void Stack<DataType>::clear()
    {
        while (!this->empty())
            this->pop();
    }

    template <class DataType>
    inline void Stack<DataType>::push(const DataType &element)
    {
        /* throws bad_alloc if allocation functions report failure to allocate storage. */
        Node *newNode = new Node(element, tos);
        tos = newNode;
        ++m_size;
    }

    template <class DataType>
    inline DataType Stack<DataType>::pop()
    {
        if (this->empty())
        {
            throw std::underflow_error("Invalid Operation: Cannot pop from empty stack!");
        }

        Node *toRemove = tos;
        tos = toRemove->link;
        DataType dataCopy = toRemove->m_data;
        delete toRemove;
        --m_size;

        return dataCopy;
    }

    template <class DataType>
    inline bool Stack<DataType>::empty() const
    {
        return tos == nullptr;
    }

    template <class DataType>
    inline unsigned int Stack<DataType>::size() const
    {
        return m_size;
    }

    template <class DataType>
    inline DataType &Stack<DataType>::top()
    {
        if (this->empty())
        {
            throw std::underflow_error("Invalid Operation: Cannot pop from empty stack!");
        }

        return tos->m_data;
    }

    template <class DataType>
    inline const DataType &Stack<DataType>::top() const
    {
        if (this->empty())
        {
            throw std::underflow_error("Invalid Operation: Cannot pop from empty stack!");
        }

        return tos->m_data;
    }
}

#endif // STACK_LINKED_GUARD