#pragma once

#include "MinHeap.h"
#include "TreeNode.h"
#include <list>
#include <map>
#include <string>
#include <vector>

// 哈夫曼树类模板
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
    //  哈夫曼树方法声明及重载编译系统默认方法声明:
    HuffmanTree(const CharType ch[], const WeightType w[], int n);  // 由字符,权值和字符个数构造哈夫曼树
    HuffmanTree(const std::vector<CharType>& chars, const std::vector<WeightType>& weights) :
        HuffmanTree(chars.data(), weights.data(), (int)chars.size()) {}
    //virtual ~HuffmanTree();                          // 析构函数模板
    std::string Encode(CharType ch);                 // 编码
    std::string Encode(std::vector<CharType> chars);                 // 编码
    std::list<CharType> Decode(const std::string& strCode);  // 译码
    HuffmanTree(const HuffmanTree<CharType, WeightType> &copy); // 复制构造函数模板
    HuffmanTree<CharType, WeightType> &operator=(const HuffmanTree<CharType,
        WeightType>& copy);                     // 重载赋值运算符
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
