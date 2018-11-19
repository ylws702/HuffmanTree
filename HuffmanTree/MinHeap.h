#pragma once
#include "TreeNode.h"
#include <vector>
template<typename T>
class MinHeap
{
public:
    MinHeap() {}
    MinHeap(const T* ts, int n);
    MinHeap(const std::vector<T>& ts) :
        MinHeap(ts.data(), (int)ts.size()) {}
    bool IsEmpty()const;
    void Insert(const T& t);
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

#include "HuffmanTree.h"
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