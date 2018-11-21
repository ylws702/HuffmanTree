#pragma once

#include "MinHeap.h"
#include "TreeNode.h"
#include <chrono>
#include <map>
#include <numeric>
#include <ratio>
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
    void MakeCodes(decltype(&root) current, std::string & code);
public:
    // 哈夫曼树方法声明及重载编译系统默认方法声明:
    // 由字符,权值和字符个数构造哈夫曼树
    HuffmanTree(const CharType ch[], const WeightType w[], int n);
    // 由字符,权值向量构造哈夫曼树
    HuffmanTree(const std::vector<CharType>& chars, const std::vector<WeightType>& weights) :
        // 调用已有构造函数
        HuffmanTree(chars.data(), weights.data(), (int)chars.size())
    {}
    // 移动构造函数模板
    HuffmanTree(HuffmanTree &&other) :
        codes(std::move(other.codes)), 
        root(std::move(other.root)) 
    {}
    // 使用默认析构函数模板
    //virtual ~HuffmanTree();
    // 编码字符
    std::string Encode(CharType ch); 
    // 编码字符串
    std::string Encode(std::vector<CharType> chars);
    // 译码
    std::vector<CharType> Decode(const std::string& strCode);
    // 重载移动赋值运算符
    HuffmanTree &operator=(HuffmanTree&& copy);
};



template<class CharType, class WeightType>
inline void HuffmanTree<CharType, WeightType>::MakeCodes(decltype(&root) current, std::string & code)
{
    if ((*current)->left == nullptr)
    {
        this->codes.insert({ (*current)->content.ch,code });
        return;
    }
    code.push_back('0');
    this->MakeCodes(&(*current)->left, code);
    code.back() = '1';
    this->MakeCodes(&(*current)->right, code);
    code.pop_back();
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


    const auto time0 = std::chrono::high_resolution_clock::now();

    /*std::thread t1, t2, t3, t4;
    std::string code1("00"), code2("01"),code3("10"), code4("11");
    if (root->left->left != nullptr)
    {
        t1 = std::thread(&HuffmanTree::MakeCodes, this, &root->left->left, std::ref(code1));
        t2 = std::thread(&HuffmanTree::MakeCodes, this, &root->left->right, std::ref(code2));
    }
    if (root->right->left != nullptr)
    {
        t3 = std::thread(&HuffmanTree::MakeCodes, this, &root->right->left, std::ref(code3));
        t4 = std::thread(&HuffmanTree::MakeCodes, this, &root->right->right, std::ref(code4));
    }
    t1.join();
    t2.join();
    t3.join();
    t4.join();*/
    /*std::string code1("0"), code2("1");
    std::thread t1(&HuffmanTree::MakeCodes, this, &root->left, std::ref(code1));
    std::thread t2(&HuffmanTree::MakeCodes, this, &root->right, std::ref(code2));
    t1.join();
    t2.join();*/
    std::string code;
    this->MakeCodes(&this->root, code);

    const auto time1 = std::chrono::high_resolution_clock::now();
    std::cout <<"MakeCodes: "<<
        std::chrono::duration_cast<std::chrono::duration<double, std::milli>>
        (time1 - time0).count() << "(ms)\n";

}

template<class CharType, class WeightType>
inline std::string HuffmanTree<CharType, WeightType>::Encode(CharType ch)
{
    return this->codes.find(ch)->second;
}

template<class CharType, class WeightType>
std::string HuffmanTree<CharType, WeightType>::Encode(std::vector<CharType> chars)
{
    std::string codedString;
    for (const auto& ch : chars)
    {
        codedString.append(this->codes.find(ch)->second);
    }
    return codedString;
}

template<class CharType, class WeightType>
inline std::vector<CharType> HuffmanTree<CharType, WeightType>::Decode(const std::string & strCode)
{
    std::vector<CharType> decodedList;
    auto current = &this->root;
    //如果哈夫曼树是空的
    if ((*current)->left == nullptr)
    {
        return decodedList;
    }
    for (auto it = strCode.cbegin(); it != strCode.cend(); ++it)
    {
        if ((*current)->left==nullptr)
        {
            decodedList.push_back((*current)->content.ch);
            current = &this->root;
            --it;
            continue;
        }
        if (*it=='0')
        {
            current = &(*current)->left;
            continue;
        }
        current = &(*current)->right;
    }
    //处理最后一位
    if ((*current)->left == nullptr)
    {
        decodedList.push_back((*current)->content.ch);
    }
    return decodedList;
}

template<class CharType, class WeightType>
inline HuffmanTree<CharType,WeightType> & HuffmanTree<CharType, WeightType>::operator=(HuffmanTree && other)
{
    if (this!=&other)
    {
        this->codes = std::move(other.codes);
        this->root = std::move(other.root);
    }
    return *this;
}

