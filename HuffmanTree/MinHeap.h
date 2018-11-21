#pragma once

#include <vector>

// С������
// T:С����Ԫ������
template<class T>
class MinHeap
{
public:
    // Ĭ�Ϲ��캯��
    MinHeap() {}
    // ����С����,ʱ�临�Ӷ�ΪO(NlogN)
    MinHeap(const T* ts, int n);
    // ʹ��std::vector����
    MinHeap(const std::vector<T>& ts) :
        MinHeap(ts.data(), (int)ts.size()) {}
    // �Ƿ�Ϊ��,ʱ�临�Ӷ�ΪO(1)
    bool IsEmpty()const;
    // Ԫ����Ŀ,ʱ�临�Ӷ�ΪO(1)
    int Size()const;
    // ����Ԫ����ֵ,ʱ�临�Ӷ�ΪO(logN)
    void Insert(const T& t);
    // ����Ԫ����ֵ,ʱ�临�Ӷ�ΪO(logN)
    void Insert(T&& t);
    // ɾ����������СԪ��,ʱ�临�Ӷ�ΪO(logN)
    T RemoveMin();
protected:
    // С������������
    std::vector<T> data;
};

// ʹ�������Ԫ����Ŀ����С����,ʱ�临�Ӷ�ΪO(NlogN)
template<class T>
MinHeap<T>::MinHeap(const T * ts, int n)
{
    for (int i = 0; i < n; ++i)
    {
        this->Insert(ts[i]);
    }
}

// �Ƿ�Ϊ��,ʱ�临�Ӷ�ΪO(1)
template<class T>
inline bool MinHeap<T>::IsEmpty() const
{
    return this->data.empty();
}

// Ԫ����Ŀ,ʱ�临�Ӷ�ΪO(1)
template<class T>
inline int MinHeap<T>::Size() const
{
    return (int)this->data.size();
}

// ����Ԫ����ֵ,ʱ�临�Ӷ�ΪO(logN)
template<class T>
inline void MinHeap<T>::Insert(const T & t)
{
    // ��ǰ����λ��ƫ����
    int position = (int)this->data.size();
    // ˫��λ��ƫ����
    int parent;
    // ��������������Ԫ��
    data.emplace_back(t);
    // ����С����
    while (position != 0)
    {
        // ˫��λ��ƫ����
        parent = (position + 1) / 2 - 1;
        // ˫�ױȵ�ǰ����Ԫ��С
        if (this->data[parent] <= this->data[position])
        {
            //��������
            return;
        }
        // ˫�ױȵ�ǰ����Ԫ�ش�,��������,�����TreeNode.h�����ص�ȫ��swap����
        std::iter_swap(&this->data[parent], &this->data[position]);
        // ��λ����˫��
        position = parent;
    }
}

// ����Ԫ����ֵ,ʱ�临�Ӷ�ΪO(logN)
template<class T>
inline void MinHeap<T>::Insert(T && t)
{
    // ��ǰ����λ��ƫ����
    int position = (int)this->data.size();
    // ˫��λ��ƫ����
    int parent;
    // ��������������Ԫ�ص���ֵ,���Ƶ���ֵ����
    data.emplace_back(std::move(t));
    // ����С����
    while (position != 0)
    {
        // ˫��λ��ƫ����
        parent = (position + 1) / 2 - 1;
        // ˫�ױȵ�ǰ����Ԫ��С
        if (this->data[parent] <= this->data[position])
        {
            //��������
            return;
        }
        // ˫�ױȵ�ǰ����Ԫ�ش�,��������,�����TreeNode.h�����ص�ȫ��swap����
        std::iter_swap(&this->data[parent], &this->data[position]);
        // ��λ����˫��
        position = parent;
    }
}

// ɾ����������СԪ��,ʱ�临�Ӷ�ΪO(logN)
template<class T>
T MinHeap<T>::RemoveMin()
{
    // ������Ԫ��,�׳��쳣
    if (this->data.empty())
    {
        throw std::exception("heap is empty!");
    }
    // ���صĽ��
    T result = std::move(this->data.front());
    // ������Ԫ���Ƶ���ǰ��,����������Ϊ��Ԫ��
    this->data.front() = std::move(this->data.back());
    // �������Ŀ�Ԫ��
    this->data.pop_back();
    // ����λ��ƫ����
    int position = 0;
    // ����ƫ����
    int sub;
    // �Ȳ�������������
    while (position < this->data.size() / 4)
    {
        // �����С��һ�����ӽڵ�ƫ����
        sub = this->data[position * 2 + 1] <
            this->data[position * 2 + 2] ?
            position * 2 + 1 :
            position * 2 + 2;
        // ������ӽڵ���ڵ��ڵ�ǰ�ڵ�
        if (this->data[position] <= this->data[sub])
        {
            //��������
            return result;
        }
        // �������ӽڵ��뵱ǰ�ڵ�����
        std::iter_swap(&this->data[position], &this->data[sub]);
        // ���ŵ������ӽڵ�
        position = sub;
    }
    //�����������
    if (position < this->data.size() / 2)
    {
        // ��Ԫ����ĿΪż��
        // �����ڵ����ֵܽ��
        if (this->data.size() % 2 == 0
            // ���Ҳ���λ��Ϊ���Ľ���˫�׽ڵ�
            && position == this->data.size() / 2 - 1)
        {
            // ���㺢�ӽڵ�
            sub = position * 2 + 1;
        }
        else
        {
            // �����С��һ�����ӽڵ�ƫ����
            sub = this->data[position * 2 + 1] <
                this->data[position * 2 + 2] ?
                position * 2 + 1 :
                position * 2 + 2;
        }
        // ������ӽڵ�С�ڵ�ǰ�ڵ�
        if (this->data[position] > this->data[sub])
        {
            // �������ӽڵ��뵱ǰ�ڵ�����
            std::iter_swap(&this->data[position], &this->data[sub]);
        }
    }
    //���ؽ��
    return result;
}