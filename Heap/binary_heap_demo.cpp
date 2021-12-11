#include <iostream>
#include <cassert>
#include <algorithm>

#include "binary_heap.hpp"

using Heap = ds::BinaryHeap<int>;

void testInsert()
{
    std::cout << "TEST INSERT" << std::endl;

    Heap heap(Heap::less);

    std::vector<int> v{1, 5, -1, 11, 23, 48, 73};

    for (auto it = v.begin(); it != v.end(); ++it)
    {
        heap.push(*it);
        assert(heap.top() == *std::min_element(v.begin(), it + 1));
    }

    std::cout << "TEST INSERT: PASSED" << std::endl;
}

void testRemove()
{
    std::cout << "TEST REMOVED" << std::endl;

    Heap heap(Heap::less);
    std::vector<int> v{1, 5, -1, 11, 23, 48, 73};

    for (auto it = v.begin(); it != v.end(); ++it)
        heap.push(*it);

    std::sort(v.begin(), v.end());

    for (auto it = v.begin(); it != v.end(); ++it)
    {
        assert(heap.top() == *it);
        heap.pop();
    }

    std::cout << "TEST REMOVE: PASSED" << std::endl;
}

//
// Driver
int main()
{
    // Demo
    Heap maxHeap(Heap::greater);

    auto customLess = [](const int &a, const int &b)
    {
        return a < b;
    };

    Heap minHeap(Heap::less);

    for (int i = 0; i <= 4; i++)
    {
        maxHeap.push(i);
    }

    testInsert();
    testRemove();

    return 0;
}