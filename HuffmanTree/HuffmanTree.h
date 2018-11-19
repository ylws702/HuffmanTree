#pragma once

#include "MinHeap.h"
#include "TreeNode.h"
#include <list>
#include <map>
#include <string>
#include <vector>

// ����������ģ��
template <class CharType, class WeightType>
class HuffmanTree
{
public:
    struct HuffmanTreeNodeContent
    {
        CharType ch;
        WeightType weight;
    };
    struct HuffmanTreeNode :
        TreeNode<HuffmanTreeNodeContent>
    {
        HuffmanTreeNode() {}
        HuffmanTreeNode(HuffmanTreeNode&) = delete;
        HuffmanTreeNode(HuffmanTreeNode&&) = delete;
        HuffmanTreeNode(const HuffmanTreeNodeContent& content)
        {
            this->content = content;
        }
        HuffmanTreeNode(HuffmanTreeNodeContent&& content)
        {
            this->content = std::move(content);
        }
        bool operator<=(const HuffmanTreeNode& h)
        {
            return this->content.weight <= h.content.weight;
        }
    };
    HuffmanTreeNode root;
    std::map<CharType, std::string> codes;
public:
    //  ���������������������ر���ϵͳĬ�Ϸ�������:
    HuffmanTree(const CharType ch[], const WeightType w[], int n);  // ���ַ�,Ȩֵ���ַ����������������
    HuffmanTree(const std::vector<CharType>& chars, const std::vector<WeightType>& weights) :
        HuffmanTree(chars.data(), weights.data(), (int)chars.size()) {}
    //virtual ~HuffmanTree();                          // ��������ģ��
    std::string Encode(CharType ch);                 // ����
    std::string Encode(std::vector<CharType> chars);                 // ����
    std::list<CharType> Decode(const std::string& strCode);  // ����
    HuffmanTree(const HuffmanTree<CharType, WeightType> &copy); // ���ƹ��캯��ģ��
    HuffmanTree<CharType, WeightType> &operator=(const HuffmanTree<CharType,
        WeightType>& copy);                     // ���ظ�ֵ�����
};


template<class CharType, class WeightType>
inline HuffmanTree<CharType, WeightType>::HuffmanTree(const CharType ch[], const WeightType w[], int n)
{
    MinHeap<HuffmanTreeNode> minHeap;
    for (int i = 0; i < n; ++i)
    {
        HuffmanTreeNode a(HuffmanTreeNodeContent{ ch[i],w[i] });
        minHeap.Insert(a);
    }
    auto& rLeaf = this->root;
}

template<class CharType, class WeightType>
std::string HuffmanTree<CharType, WeightType>::Encode(std::vector<CharType> chars)
{
    return std::string();
}
