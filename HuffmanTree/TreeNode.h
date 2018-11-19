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
    T content;
    std::unique_ptr<TreeNode<T>> parent = nullptr;
    std::unique_ptr<TreeNode<T>> leftChild = nullptr;
    std::unique_ptr<TreeNode<T>> rightChild = nullptr;
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
    this->parent.swap(other.parent);
    this->leftChild.swap(other.leftChild);
    this->rightChild.swap(other.rightChild);
}

template<typename T>
void swap(TreeNode<T>& t1, TreeNode<T>& t2)
{
    t1.Swap(t2);
}