#ifndef BST_HPP_GUARD_
#define BST_HPP_GUARD_

#include <stdexcept>

namespace ds
{
    template <typename DataType>
    class BST
    {
    private:
        struct Node
        {
            DataType data;
            Node *left;
            Node *right;

            Node(const DataType &data)
                : data(data),
                  left(nullptr), right(nullptr) {}
        } * root;

    public:
        BST();

        BST(const BST &other); // TODO

        BST &operator=(const BST &other); // TODO

        void insert(const DataType &data);

        void remove(const DataType &data);

        bool contains(const DataType &data);

        ~BST();

        /* Helpers */
    private:
        Node *&find(Node *&root, const DataType &key);

        Node *&max(Node *&root);

        Node *&min(Node *&root);

        void copyFrom(Node *root); // TODO

        void freeTree(Node *root);
    };

    template <typename DataType>
    inline BST<DataType>::BST()
        : root(nullptr) {}

    template <typename DataType>
    inline BST<DataType>::BST(const BST &other)
    {
        copyFrom(other.root);
    }

    template <typename DataType>
    inline BST<DataType>::~BST()
    {
        freeTree(root);
    }

    template <typename DataType>
    inline void BST<DataType>::freeTree(Node *root)
    {
        if (root)
        {
            freeTree(root->left);
            freeTree(root->right);
            delete root;
        }
    }

    template <typename DataType>
    inline void BST<DataType>::insert(const DataType &data)
    {
        Node *&node = find(root, data);

        if (node)
        {
            throw std::logic_error("BST: A node with this data is already inserted!");
        }

        node = new Node(data);
    }

    template <typename DataType>
    typename BST<DataType>::Node *&BST<DataType>::max(Node *&root)
    {
        if (root == nullptr || root->right == nullptr)
            return root;

        return max(root->right);
    }

    template <typename DataType>
    inline typename BST<DataType>::Node *&BST<DataType>::min(Node *&root)
    {
        if (root == nullptr || root->left == nullptr)
            return root;

        return min(root->left);
    }

    template <typename DataType>
    inline void BST<DataType>::remove(const DataType &data)
    {
        Node *&node = find(root, data);

        if (!node->left && !node->right)
        {
            // The node to be removed is leaf
            delete node;
            node = nullptr;
        }
        else if (!node->left)
        {
            // The node to be removed has only one right child
            Node *right = node->right;
            delete node;
            node = right;
        }
        else if (!node->right)
        {
            // The node to be removed has only one left child
            Node *left = node->left;
            delete node;
            node = left;
        }
        else
        {
            // The node to be removed has both two children
            // Find the max record in the left subtree and swap with the node
            Node *&maxLeft = max(node->left);
            node->data = maxLeft->data;
            delete maxLeft;
            maxLeft = nullptr;
        }
    }

    template <typename DataType>
    inline bool BST<DataType>::contains(const DataType &data)
    {
        return find(root, data) != nullptr;
    }

    template <typename DataType>
    inline typename BST<DataType>::Node *&BST<DataType>::find(Node *&root, const DataType &key)
    {
        if (!root)
            return root;

        if (root->data == key)
            return root;

        if (key < root->data)
            return find(root->left, key);
        else
            return find(root->right, key);
    }
}

#endif // BST_HPP_GUARD_