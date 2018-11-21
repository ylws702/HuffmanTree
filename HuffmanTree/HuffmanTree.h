#pragma once

#include "MinHeap.h"
#include "TreeNode.h"
#include <list>
#include <map>
#include <stack>
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
        bool operator<=(const HuffmanTreeNodeContent& other)
        {
            return this->weight <= other.weight;
        }
        bool operator<(const HuffmanTreeNodeContent& other)
        {
            return this->weight < other.weight;
        }
        bool operator>(const HuffmanTreeNodeContent& other)
        {
            return this->weight > other.weight;
        }
    };
    struct HuffmanTreeNode :
        TreeNode<HuffmanTreeNodeContent>
    {
        HuffmanTreeNode() {}
        HuffmanTreeNode(HuffmanTreeNode&) = delete;
        HuffmanTreeNode(HuffmanTreeNode&& other)noexcept
        {
            this->content = std::move(other.content);
            this->left = std::move(other.left);
            this->right = std::move(other.right);
        }
        HuffmanTreeNode(const HuffmanTreeNodeContent& content)
        {
            this->content = content;
        }
        HuffmanTreeNode(WeightType weight)
        {
            this->content.weight = weight;
        }
        HuffmanTreeNode(HuffmanTreeNodeContent&& content)
        {
            this->content = std::move(content);
        }
        HuffmanTreeNode& operator=(HuffmanTreeNode&& other)noexcept
        {
            if (this != &other)
            {
                this->content = std::move(other.content);
                this->left = std::move(other.left);
                this->right = std::move(other.right);
            }
            return *this;
        }
        bool operator<=(const HuffmanTreeNode& other)
        {
            return this->content.weight <= other.content.weight;
        }
        bool operator<(const HuffmanTreeNode& other)
        {
            return this->content.weight < other.content.weight;
        }
        bool operator>(const HuffmanTreeNode& other)
        {
            return this->content.weight > other.content.weight;
        }
    };
    //使用std::unique_ptr<HuffmanTreeNode>会导致root与子节点类型不同
    std::unique_ptr<TreeNode<HuffmanTreeNodeContent>> root;
    std::map<CharType, std::string> codes;
    void MakeCodes(decltype(&root) current, std::string& code);
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
inline void HuffmanTree<CharType, WeightType>::MakeCodes(decltype(&root) current, std::string & code)
{
    if ((*current)->IsLeaf())
    {
        this->codes.insert({ (*current)->content.ch,code });
        return;
    }
    if ((*current)->left != nullptr)
    {
        code.push_back('0');
        this->MakeCodes(&(*current)->left, code);
        code.pop_back();
    }
    if ((*current)->right != nullptr)
    {
        code.push_back('1');
        this->MakeCodes(&(*current)->right, code);
        code.pop_back();
    }
}

template<class CharType, class WeightType>
inline HuffmanTree<CharType, WeightType>::HuffmanTree(const CharType ch[], const WeightType w[], int n)
{
    if (n <= 0)
    {
        return;
    }
    if (n == 1)
    {
        this->codes.insert({ *ch,"0" });
        this->root = std::make_unique<HuffmanTreeNode>(HuffmanTreeNodeContent{ *ch,*w });
        return;
    }
    MinHeap<HuffmanTreeNode> minHeap;
    for (int i = 0; i < n; ++i)
    {
        minHeap.Insert(HuffmanTreeNode({ ch[i],w[i] }));
    }
    while (minHeap.Size() >= 2)
    {
        auto&&min1 = minHeap.RemoveMin();
        auto&&min2 = minHeap.RemoveMin();
        HuffmanTreeNode parent(min1.content.weight + min2.content.weight);
        parent.left = std::make_unique<HuffmanTreeNode>(std::move(min1));
        parent.right = std::make_unique<HuffmanTreeNode>(std::move(min2));
        minHeap.Insert(std::move(parent));
    }
    if (!minHeap.IsEmpty())
    {
        this->root = std::make_unique<HuffmanTreeNode>(minHeap.RemoveMin());
    }
    std::string code;
    this->MakeCodes(&root, code);
}

template<class CharType, class WeightType>
std::string HuffmanTree<CharType, WeightType>::Encode(std::vector<CharType> chars)
{
    return std::string();
}

template<class CharType, class WeightType>
inline std::list<CharType> HuffmanTree<CharType, WeightType>::Decode(const std::string & strCode)
{
    for (auto it = strCode.cbegin(); it != strCode.cend(); ++it)
    {

    }
}
