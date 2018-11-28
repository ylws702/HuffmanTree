#pragma once

#include <memory>

template<class T>
struct TreeNode
{
    // ����Ĭ�Ϲ��캯��
    TreeNode() = delete;
    // ��������ֵ����
    TreeNode(const T& t);
    // ��������ֵ����
    TreeNode(T&& t);
    // ���ø��ƹ��캯��
    TreeNode(TreeNode&) = delete;
    // �����ƶ����캯��
    TreeNode(TreeNode&&) = delete;
    // ʹ��Ĭ����������
    //virtual ~TreeNode() {}
    // ����һTreeNode����
    virtual void Swap(TreeNode& other);
    // �Ƿ�ΪҶ�ڵ�
    virtual bool IsLeaf()const;
    // �ڵ�����
    T content;
    // ����ָ��
    std::unique_ptr<TreeNode<T>> left = nullptr;
    // �Һ���ָ��
    std::unique_ptr<TreeNode<T>> right = nullptr;
};

//swap������������
template<class T>
void swap(TreeNode<T>& t1, TreeNode<T>& t2);

// ��������ֵ����
template<class T>
inline TreeNode<T>::TreeNode(const T& t)
{
    this->content = t;
}

// ��������ֵ����
template<class T>
TreeNode<T>::TreeNode(T && t)
{
    this->content = std::move(t);
}

// ����һTreeNode����
template<class T>
inline void TreeNode<T>::Swap(TreeNode & other)
{
    //������������
    std::swap(this->content, other.content);
    //��������
    this->left.swap(other.left);
    //�����Һ���
    this->right.swap(other.right);
}

// �Ƿ�ΪҶ�ڵ�
template<class T>
inline bool TreeNode<T>::IsLeaf() const
{
    //���Һ��Ӷ�Ϊ��
    return this->left == nullptr
        && this->right == nullptr;
}

//swap�������ض���
template<class T>
void swap(TreeNode<T>& t1, TreeNode<T>& t2)
{
    t1.Swap(t2);
}
