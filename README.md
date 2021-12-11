# Data Structures

The repository is a collection of own implementations of some popular data structures in C++. 

| Name               | Note                                                                                                                                                                                              | Source              | Unit Tests               |
| ------------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------- | ------------------------ |
| Dynamic Array      | Random-access sequence container (array) <br> that can automatically handle its size when needed.                                                                                                 | [dynamic_array.hpp] | [dyn_arr_tests.cpp]      |
| Stack (Linked)     | Linear data structure based on list which follows the LIFO principle.                                                                                                                             | [stack_linked.hpp]  | [stack_tests.cpp]        |
| Stack (Static)     | Linear data structure with fixed size which follows the LIFO principle.                                                                                                                           | [stack_static.hpp]  | [stack_static_tests.cpp] |
| Doubly linked list | The doubly linked list is a variation of a linked list (linear data structure) in which each node, apart from storing its data, has two links for the previous and the next node (bidirectional). | [list.hpp]          | [list_tests.cpp]         |
| Heap               | Binary-tree based data structure which is complete and satisfies the heap property set by internal or external comparison function.                                                               | [binary_heap.hpp]   |                          |
| Binary Search Tree | In progress                                                                                                                                                                                       | [BST.hpp]           |                          |


[dynamic_array.hpp]: ./DynamicArray/dynamic_array.hpp
[dyn_arr_tests.cpp]: ./DynamicArray/dyn_arr_tests.cpp
[stack_linked.hpp]: ./Stacks/StackLinked/stack_linked.hpp
[stack_tests.cpp]: ./Stacks/StackLinked/stack_tests.cpp
[list.hpp]: ./DoublyLinkedList/list.hpp
[list_tests.cpp]: ./DoublyLinkedList/list_tests.cpp
[stack_static.hpp]: ./Stacks/StaticStack/stack_static.hpp
[stack_static_tests.cpp]: ./Stacks/StaticStack/stack_static_tests.cpp
[binary_heap.hpp]: ./Heap/binary_heap.hpp
[BST.hpp]: ./BinarySerachTree/BST.hpp
