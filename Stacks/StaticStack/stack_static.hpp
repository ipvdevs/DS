/**
 * @file stack_static.hpp
 * @author Ivan Penev
 * @version 0.1
 * @date 2021-11-07
 * 
 */

#ifndef STATIC_STACK_HPP_GUARD_
#define STATIC_STACK_HPP_GUARD_

#include <stdexcept>

/**
 * @brief An implementation of stack with fixed size
 * @param ValueType The type of the elements in the stack
 * @param MAX_SIZE The maximum capacity of the stack
 */
template <typename ValueType, const int MAX_SIZE>
class StaticStack
{
private:
    ValueType stack[MAX_SIZE];

    int tos = -1; /*!< Top Of Stack */

public:
    /**
     * @brief Insert element at the top
     * 
     * @param val The element to be inserted at the top
     * @throws std::overflow_error when the stack is full
     */
    void push(const ValueType &val)
    {
        if (tos >= MAX_SIZE - 1)
        {
            throw std::overflow_error("StaticStack: Stack overflow!");
        }

        stack[++tos] = val;
    }

    /**
     * @brief Removes the top element in the container
     * 
     * @throws std::underflow_error when container is empty
     */
    void pop()
    {
        if (isEmpty())
        {
            throw std::underflow_error("StaticStack: Stack is empty!");
        }

        --tos;
    }

    /**
     * @brief Returns the top of container
     * 
     * @throws std::underflow_error when container is empty
     * @return ValueType The element at the top of container
     */
    ValueType top() const
    {
        if (isEmpty())
        {
            throw std::underflow_error("StaticStack: Stack is empty!");
        }

        return stack[tos];
    }

    /**
     * @brief Returns the maximum size of the container
     * 
     * @return size_t The maximum size of the container
     */
    size_t maxSize() const {
        return MAX_SIZE;
    }

    /**
     * @brief Checks whether the container is empty
     */
    bool isEmpty() const
    {
        return tos == -1;
    }

    /**
     * @brief Returns the number of elements stored in the container
     * 
     * @return size_t The number of elements stored in the container
     */
    size_t size() const
    {
        return tos + 1;
    }
};

#endif // STATIC_STACK_HPP_GUARD_
