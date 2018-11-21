#pragma once

#include <vector>

// 小顶堆类
// T:小顶堆元素类型
template<class T>
class MinHeap
{
public:
    // 默认构造函数
    MinHeap() {}
    // 构造小顶堆,时间复杂度为O(NlogN)
    MinHeap(const T* ts, int n);
    // 使用std::vector构造
    MinHeap(const std::vector<T>& ts) :
        MinHeap(ts.data(), (int)ts.size()) {}
    // 是否为空,时间复杂度为O(1)
    bool IsEmpty()const;
    // 元素数目,时间复杂度为O(1)
    int Size()const;
    // 插入元素左值,时间复杂度为O(logN)
    void Insert(const T& t);
    // 插入元素右值,时间复杂度为O(logN)
    void Insert(T&& t);
    // 删除并返回最小元素,时间复杂度为O(logN)
    T RemoveMin();
protected:
    // 小顶堆数据容器
    std::vector<T> data;
};

// 使用数组和元素数目构造小顶堆,时间复杂度为O(NlogN)
template<class T>
MinHeap<T>::MinHeap(const T * ts, int n)
{
    for (int i = 0; i < n; ++i)
    {
        this->Insert(ts[i]);
    }
}

// 是否为空,时间复杂度为O(1)
template<class T>
inline bool MinHeap<T>::IsEmpty() const
{
    return this->data.empty();
}

// 元素数目,时间复杂度为O(1)
template<class T>
inline int MinHeap<T>::Size() const
{
    return (int)this->data.size();
}

// 插入元素左值,时间复杂度为O(logN)
template<class T>
inline void MinHeap<T>::Insert(const T & t)
{
    // 当前操作位置偏移量
    int position = (int)this->data.size();
    // 双亲位置偏移量
    int parent;
    // 向容器加入插入的元素
    data.emplace_back(t);
    // 调整小顶堆
    while (position != 0)
    {
        // 双亲位置偏移量
        parent = (position + 1) / 2 - 1;
        // 双亲比当前操作元素小
        if (this->data[parent] <= this->data[position])
        {
            //结束调整
            return;
        }
        // 双亲比当前操作元素大,互换内容,会调用TreeNode.h中重载的全局swap函数
        std::iter_swap(&this->data[parent], &this->data[position]);
        // 换位操作双亲
        position = parent;
    }
}

// 插入元素右值,时间复杂度为O(logN)
template<class T>
inline void MinHeap<T>::Insert(T && t)
{
    // 当前操作位置偏移量
    int position = (int)this->data.size();
    // 双亲位置偏移量
    int parent;
    // 向容器加入插入的元素的右值,会移掉右值内容
    data.emplace_back(std::move(t));
    // 调整小顶堆
    while (position != 0)
    {
        // 双亲位置偏移量
        parent = (position + 1) / 2 - 1;
        // 双亲比当前操作元素小
        if (this->data[parent] <= this->data[position])
        {
            //结束调整
            return;
        }
        // 双亲比当前操作元素大,互换内容,会调用TreeNode.h中重载的全局swap函数
        std::iter_swap(&this->data[parent], &this->data[position]);
        // 换位操作双亲
        position = parent;
    }
}

// 删除并返回最小元素,时间复杂度为O(logN)
template<class T>
T MinHeap<T>::RemoveMin()
{
    // 堆中无元素,抛出异常
    if (this->data.empty())
    {
        throw std::exception("heap is empty!");
    }
    // 返回的结果
    T result = std::move(this->data.front());
    // 将最后的元素移到最前面,容器最后面变为空元素
    this->data.front() = std::move(this->data.back());
    // 弹出最后的空元素
    this->data.pop_back();
    // 操作位置偏移量
    int position = 0;
    // 孩子偏移量
    int sub;
    // 先不调整最下两层
    while (position < this->data.size() / 4)
    {
        // 计算较小的一个孩子节点偏移量
        sub = this->data[position * 2 + 1] <
            this->data[position * 2 + 2] ?
            position * 2 + 1 :
            position * 2 + 2;
        // 如果孩子节点大于等于当前节点
        if (this->data[position] <= this->data[sub])
        {
            //结束调整
            return result;
        }
        // 交换孩子节点与当前节点内容
        std::iter_swap(&this->data[position], &this->data[sub]);
        // 接着调整孩子节点
        position = sub;
    }
    //调整最后两层
    if (position < this->data.size() / 2)
    {
        // 堆元素数目为偶数
        // 则最后节点无兄弟结点
        if (this->data.size() % 2 == 0
            // 而且操作位置为最后的结点的双亲节点
            && position == this->data.size() / 2 - 1)
        {
            // 计算孩子节点
            sub = position * 2 + 1;
        }
        else
        {
            // 计算较小的一个孩子节点偏移量
            sub = this->data[position * 2 + 1] <
                this->data[position * 2 + 2] ?
                position * 2 + 1 :
                position * 2 + 2;
        }
        // 如果孩子节点小于当前节点
        if (this->data[position] > this->data[sub])
        {
            // 交换孩子节点与当前节点内容
            std::iter_swap(&this->data[position], &this->data[sub]);
        }
    }
    //返回结果
    return result;
}