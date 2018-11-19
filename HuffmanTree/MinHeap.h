#pragma once
#include "TreeNode.h"
#include <vector>
template<typename T>
class MinHeap
{
public:
    MinHeap() {}
    //构造小顶堆,时间复杂度为O(NlogN)
    MinHeap(const T* ts, int n);
    //使用std::vector构造
    MinHeap(const std::vector<T>& ts) :
        MinHeap(ts.data(), (int)ts.size()) {}
    //是否为空,时间复杂度为O(1)
    bool IsEmpty()const;
    //元素数目,时间复杂度为O(1)
    int Size()const;
    //插入元素左值,时间复杂度为O(logN)
    void Insert(const T& t);
    //插入元素右值,时间复杂度为O(logN)
    void Insert(T&& t);
    //删除并返回最小元素,时间复杂度为O(logN)
    T RemoveMin();
protected:
    std::vector<T> data;
};


template<typename T>
MinHeap<T>::MinHeap(const T * ts, int n)
{
    for (int i = 0; i < n; ++i)
    {
        this->Insert(ts[i]);
    }
}

template<typename T>
inline bool MinHeap<T>::IsEmpty() const
{
    return this->data.empty();
}

template<typename T>
inline int MinHeap<T>::Size() const
{
    return (int)this->data.size();
}

template<typename T>
inline void MinHeap<T>::Insert(const T & t)
{
    int position = (int)this->data.size();
    int parent;
    data.emplace_back(t);
    while (position != 0)
    {
        parent = (position + 1) / 2 - 1;
        if (this->data[parent] <= this->data[position])
        {
            return;
        }
        std::iter_swap(&this->data[parent], &this->data[position]);
        position = parent;
    }
}

template<typename T>
inline void MinHeap<T>::Insert(T && t)
{
    int position = (int)this->data.size();
    int parent;
    data.emplace_back(std::move(t));
    while (position != 0)
    {
        parent = (position + 1) / 2 - 1;
        if (this->data[parent] <= this->data[position])
        {
            return;
        }
        std::iter_swap(&this->data[parent], &this->data[position]);
        position = parent;
    }
}

template<typename T>
T MinHeap<T>::RemoveMin()
{
    if (this->data.empty())
    {
        throw std::exception("heap is empty!");
    }
    T result = std::move(this->data.front());
    this->data.front() = std::move(this->data.back());
    this->data.pop_back();
    int position = 0;
    int sub;
    while (position < this->data.size() / 4)
    {
        sub = this->data[position * 2 + 1] < this->data[position * 2 + 2] ?
            position * 2 + 1 :
            position * 2 + 2;
        if (this->data[position] <= this->data[sub])
        {
            return result;
        }
        std::iter_swap(&this->data[position], &this->data[sub]);
        position = sub;
    }
    if (position < this->data.size() / 2)
    {
        if (this->data.size() % 2 == 0 && position == this->data.size() / 2 - 1)
        {
            sub = position * 2 + 1;
        }
        else
        {
            sub = this->data[position * 2 + 1] < this->data[position * 2 + 2] ?
                position * 2 + 1 :
                position * 2 + 2;
        }
        if (this->data[position] > this->data[sub])
        {
            std::iter_swap(&this->data[position], &this->data[sub]);
        }
    }
    return result;
}