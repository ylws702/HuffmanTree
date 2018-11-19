#pragma once

#include <memory>
template<typename T>
struct TreeNode
{
    TreeNode() {}
    TreeNode(T& t);
    TreeNode(T&& t);
    TreeNode(TreeNode&) = delete;
    TreeNode(TreeNode&&) = delete;
    virtual ~TreeNode() {}
    virtual void Swap(TreeNode& other);
    virtual bool IsLeaf()const;
    T content;
    std::unique_ptr<TreeNode<T>> left = nullptr;
    std::unique_ptr<TreeNode<T>> right = nullptr;
};
template<typename T>
void swap(TreeNode<T>& t1, TreeNode<T>& t2);

template<typename T>
inline TreeNode<T>::TreeNode(T& t)
{
    this->content = t;
}

template<typename T>
TreeNode<T>::TreeNode(T && t)
{
    this->content = std::move(t);
}

template<typename T>
inline void TreeNode<T>::Swap(TreeNode & other)
{
    std::swap(this->content, other.content);
    this->left.swap(other.left);
    this->right.swap(other.right);
}

template<typename T>
inline bool TreeNode<T>::IsLeaf() const
{
    return this->left == nullptr
        && this->right == nullptr;
}

template<typename T>
void swap(TreeNode<T>& t1, TreeNode<T>& t2)
{
    t1.Swap(t2);
}