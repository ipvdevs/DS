/**
 * @file BinaryHeap.hpp
 * @author Ivan Penev
 * @brief Implementation of binary heap
 * @date 2021-11-28
 *
 */

#ifndef BINARY_HEAP_HPP_GUARD_
#define BINARY_HEAP_HPP_GUARD_

#include <cassert>   // Used to validate invariants
#include <stdexcept> // Exception handling
#include <vector>    // Used as main heap container

template <typename DataType>
class BinaryHeap
{
private:
    std::vector<DataType> container;
    bool (*cmp)(const DataType &lhs, const DataType &rhs);

public:
    /**
     * @brief A comparison function that checks whether lhs is less than rhs.
     *
     * @param lhs - left hand side
     * @param rhs - right hand side
     * @return true if the lhs is less than rhs.
     */
    static bool less(const DataType &lhs, const DataType &rhs)
    {
        return lhs < rhs;
    }

    /**
     * @brief A comparison function that checks whether lhs is greater than rhs.
     *
     * @param lhs - left hand side
     * @param rhs - right hand side
     * @return true if the lhs is greater than rhs.
     */
    static bool greater(const DataType &lhs, const DataType &rhs)
    {
        return lhs > rhs;
    }

    /**
     * @brief Constructs a new Binary Heap object with given comparison function
     *
     * @param cmp the comparison function used in the binary heap
     */
    BinaryHeap(bool (*cmp)(const DataType &lhs, const DataType &rhs))
    {
        this->cmp = cmp;
    }

    /**
     * @brief Inserts element into the heap and sorts using the comparison
     * function
     * @note Time complexity: O(logN)
     * @param element - The element to insert
     */
    void push(const DataType &element)
    {
        container.push_back(element);
        siftUp(container.size() - 1);
    }

    /**
     * @brief Removes the top element of the heap
     * @note Time complexity: O(logN)
     */
    void pop()
    {
        if (container.empty())
        {
            throw std::underflow_error("BinaryHeap: Heap is empty!");
        }

        std::swap(container.front(), container.back());
        container.pop_back();

        if (container.size() > 1)
        {
            siftDown(0);
        }
    }

    /**
     * @brief Accesses the top element of the heap
     * @note Time complexity: O(1)
     * @throws std::logic_error - when the heap is empty
     * @return const DataType& - a constant reference to the top element
     */

    const DataType &top() const
    {
        if (container.empty())
        {
            throw std::underflow_error("BinaryHeap: Heap is empty!");
        }

        return container.front();
    }

    /**
     * @brief Returns the number of elements in the heap
     *
     * @return const size_t - the number of elements
     */
    size_t size() const { return container.size(); }

    /**
     * @brief Checks if the heap is empty
     *
     * @return bool - true if empty, false otherwise
     */
    bool isEmpty() const { return container.isEmpty(); }

    //
    /* Helpers */
private:
    /**
     * @brief Moves the value up the tree in order to maintain the heap
     * invariants
     *
     * @param pos - Position of the sifted element
     */
    void siftUp(size_t pos)
    {
        while (pos > 0 && cmp(container[pos], container[parent(pos)]))
        {
            std::swap(container[pos], container[parent(pos)]);
            pos = parent(pos);
        }
    }

    /**
     * @brief Moves the value down the tree in order to maintain the heap
     * invariants
     *
     * @param pos - Position of the sifted element
     */
    void siftDown(size_t pos)
    {
        assert(pos >= 0);

        int left_i = leftChild(pos);
        int right_i = rightChild(pos);
        int swap_i;

        while (left_i < container.size())
        {
            swap_i = pos;

            swap_i = cmp(container[swap_i], container[left_i]) ? swap_i : left_i;

            if (right_i < container.size())
            {
                swap_i = cmp(container[swap_i], container[right_i]) ? swap_i : right_i;
            }

            // No changes have occurred
            if (pos == swap_i)
            {
                break;
            }

            std::swap(container[swap_i], container[pos]);
            pos = swap_i;
            left_i = leftChild(pos);
            right_i = rightChild(pos);
        }
    }

    /**
     * @brief Calculates the parent's index of container[i]
     *
     * @param i - The index of the element whose parent's position is
     * calculated.
     * @return int - The parent of container[i]
     */
    int parent(int i)
    {
        assert(i > 0);
        return (i - 1) / 2;
    }

    /**
     * @brief Calculates the left child index of container[i]
     *
     * @param i - The parent index of the element whose left child position is
     * calculated.
     * @return int - Index of the left child of container[i]
     */
    int leftChild(int i)
    {
        assert(i >= 0);
        return 2 * i + 1;
    }

    /**
     * @brief Calculates the right child index of container[i]
     *
     * @param i - The parent index of the element whose right child position is
     * calculated.
     * @return int - Index of the right child of container[i]
     */
    int rightChild(int i)
    {
        assert(i >= 0);
        return 2 * i + 2;
    }
};

#endif // BINARY_HEAP_HPP_GUARD_