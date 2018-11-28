#pragma once

#include <memory>

template<class T>
struct TreeNode
{
    // 禁用默认构造函数
    TreeNode() = delete;
    // 以内容左值构造
    TreeNode(const T& t);
    // 以内容右值构造
    TreeNode(T&& t);
    // 禁用复制构造函数
    TreeNode(TreeNode&) = delete;
    // 禁用移动构造函数
    TreeNode(TreeNode&&) = delete;
    // 使用默认析构函数
    //virtual ~TreeNode() {}
    // 与另一TreeNode交换
    virtual void Swap(TreeNode& other);
    // 是否为叶节点
    virtual bool IsLeaf()const;
    // 节点内容
    T content;
    // 左孩子指针
    std::unique_ptr<TreeNode<T>> left = nullptr;
    // 右孩子指针
    std::unique_ptr<TreeNode<T>> right = nullptr;
};

//swap函数重载声明
template<class T>
void swap(TreeNode<T>& t1, TreeNode<T>& t2);

// 以内容左值构造
template<class T>
inline TreeNode<T>::TreeNode(const T& t)
{
    this->content = t;
}

// 以内容右值构造
template<class T>
TreeNode<T>::TreeNode(T && t)
{
    this->content = std::move(t);
}

// 与另一TreeNode交换
template<class T>
inline void TreeNode<T>::Swap(TreeNode & other)
{
    //交换数据内容
    std::swap(this->content, other.content);
    //交换左孩子
    this->left.swap(other.left);
    //交换右孩子
    this->right.swap(other.right);
}

// 是否为叶节点
template<class T>
inline bool TreeNode<T>::IsLeaf() const
{
    //左右孩子都为空
    return this->left == nullptr
        && this->right == nullptr;
}

//swap函数重载定义
template<class T>
void swap(TreeNode<T>& t1, TreeNode<T>& t2)
{
    t1.Swap(t2);
}
