#pragma once

#include "MinHeap.h"
#include "TreeNode.h"
#include <functional>
#include <map>
#include <string>
#include <vector>

// ����������ģ��
// CharType:�ַ�����
// WeightType:������������
template <class CharType, class WeightType>
class HuffmanTree
{
protected:
    // ���������ڵ�������ݽṹ��
    struct HuffmanTreeNodeContent;
    // ���������ڵ�ṹ��
    struct HuffmanTreeNode;
    // ���ڵ�ָ��
    // ps:ʹ��std::unique_ptr<HuffmanTreeNode>�ᵼ��root���ӽڵ����Ͳ�ͬ
    std::unique_ptr<TreeNode<HuffmanTreeNodeContent>> root;
    // �ַ�����ӳ��
    std::map<CharType, std::string> codes;
    // �����ַ�����
    void MakeCodes(decltype(&root) current, std::string & code);
public:
    // ���������������������ر���ϵͳĬ�Ϸ�������:
    // ���ַ�,Ȩֵ���ַ����������������
    HuffmanTree(const CharType ch[], const WeightType w[], int n);
    // ���ַ�,Ȩֵ���ַ����������������
    //HuffmanTree(const CharType ch[], const WeightType w[], int n);
    // ���ַ�,Ȩֵ���������������
    HuffmanTree(const std::vector<CharType>& chars, const std::vector<WeightType>& weights) :
        // �������й��캯��
        HuffmanTree(chars.data(), weights.data(), (int)chars.size())
    {}
    // �ƶ����캯��ģ��
    HuffmanTree(HuffmanTree &&other) :
        codes(std::move(other.codes)),
        root(std::move(other.root))
    {}
    // ʹ��Ĭ����������ģ��
    //virtual ~HuffmanTree();
    // �����ַ�
    std::string Encode(CharType ch);
    // �����ַ�����
    std::string Encode(std::vector<CharType> chars);
    // �����ַ���
    std::vector<CharType> Decode(const std::string& strCode);
    // �����ƶ���ֵ�����
    HuffmanTree &operator=(HuffmanTree&& copy);
};

// ���������ڵ�������ݽṹ��
template <class CharType, class WeightType>
struct HuffmanTree<CharType, WeightType>::HuffmanTreeNodeContent
{
    //�ַ�
    CharType ch;
    //�ַ�Ȩ��
    WeightType weight;

    //����С�ڵ��������
    bool operator<=(const HuffmanTreeNodeContent& other)
    {
        //����Ȩ�رȽ�
        return this->weight <= other.weight;
    }

    //����С�������
    bool operator<(const HuffmanTreeNodeContent& other)
    {
        //����Ȩ�رȽ�
        return this->weight < other.weight;
    }

    //���ش��������
    bool operator>(const HuffmanTreeNodeContent& other)
    {
        //����Ȩ�رȽ�
        return this->weight > other.weight;
    }
};

// ���������ڵ�ṹ��
template <class CharType, class WeightType>
struct HuffmanTree<CharType, WeightType>::HuffmanTreeNode :
    // �̳�TreeNode<HuffmanTreeNodeContent>
    // �ṹ��Ĭ��public�̳�
    TreeNode<HuffmanTreeNodeContent>
{
    // Ĭ�Ϲ��캯��
    HuffmanTreeNode() {}

    // ���ø��ƹ��캯��
    HuffmanTreeNode(HuffmanTreeNode&) = delete;

    // �ƶ����캯��
    HuffmanTreeNode(HuffmanTreeNode&& other)noexcept
    {
        // �ƶ�����
        this->content = std::move(other.content);
        // �ƶ�����
        this->left = std::move(other.left);
        // �ƶ��Һ���
        this->right = std::move(other.right);
    }

    //ͨ��������Ҷ�ڵ�Ȩֵ����
    HuffmanTreeNode(WeightType weight)
    {
        this->content.weight = weight;
    }

    // ͨ��������Ҷ�ڵ���ֵ����
    HuffmanTreeNode(const HuffmanTreeNodeContent& content)
    {
        // ��������
        this->content = content;
    }

    // ͨ��������Ҷ�ڵ���ֵ����
    HuffmanTreeNode(HuffmanTreeNodeContent&& content)
    {
        // �ƶ�����
        this->content = std::move(content);
    }

    // �����ƶ���ֵ�����
    HuffmanTreeNode& operator=(HuffmanTreeNode&& other)noexcept
    {
        // �Ը�ֵ�ж�
        if (this != &other)
        {
            //�ƶ�����
            this->content = std::move(other.content);
            //�ƶ�����
            this->left = std::move(other.left);
            //�ƶ��Һ���
            this->right = std::move(other.right);
        }
        //������������
        return *this;
    }

    //����С�ڵ��������
    bool operator<=(const HuffmanTreeNode& other)
    {
        //����Ȩ�رȽ�
        return this->content.weight <= other.content.weight;
    }

    //����С�������
    bool operator<(const HuffmanTreeNode& other)
    {
        //����Ȩ�رȽ�
        return this->content.weight < other.content.weight;
    }

    //���ش��������
    bool operator>(const HuffmanTreeNode& other)
    {
        //����Ȩ�رȽ�
        return this->content.weight > other.content.weight;
    }
};

// �����ַ�����
template<class CharType, class WeightType>
inline void HuffmanTree<CharType, WeightType>::
MakeCodes(decltype(&root) current, std::string & code)
{
    //������Ϊ��,˵���ýڵ�ΪҶ�ӽڵ�
    if ((*current)->left == nullptr)
    {
        //�����ַ�����
        this->codes.insert({ (*current)->content.ch,code });
        //�����ݹ�
        return;
    }
    //�����ַ���ĩ������0
    code.push_back('0');
    //�ٵݹ��������
    this->MakeCodes(&(*current)->left, code);
    //�����ַ���ĩ�˻���1
    code.back() = '1';
    //�ٵݹ�����Һ���
    this->MakeCodes(&(*current)->right, code);
    //ȥ��ĩβ��1
    code.pop_back();
    //�����ݹ�
}

//���ַ�,Ȩֵ���ַ����������������
template<class CharType, class WeightType>
inline HuffmanTree<CharType, WeightType>::
HuffmanTree(const CharType ch[], const WeightType w[], int n)
{
    //������ַ��������
    if (n <= 0)
    {
        return;
    }
    //ֻ��һ���ַ�
    if (n == 1)
    {
        //ֱ�ӽ������Ϊ0
        this->codes.insert({ *ch,"0" });
        //���ڸ��ڵ���
        this->root = std::make_unique<HuffmanTreeNode>(HuffmanTreeNodeContent{ *ch,*w });
        return;
    }
    //����С����
    MinHeap<HuffmanTreeNode> minHeap;
    //��С�������β����Ȩֵ�ַ��ڵ�
    for (int i = 0; i < n; ++i)
    {
        minHeap.Insert(HuffmanTreeNode({ ch[i],w[i] }));
    }
    //�����������
    while (minHeap.Size() >= 2)
    {
        //��ȡ��СԪ��
        auto&&min1 = minHeap.RemoveMin();
        //��ȡ�ڶ�СԪ��
        auto&&min2 = minHeap.RemoveMin();
        //�����丸���������ڵ�,ȨֵΪ��СԪ����ڶ�СԪ��Ȩֵ֮��
        HuffmanTreeNode parent(min1.content.weight + min2.content.weight);
        //����СԪ���ƶ�������
        parent.left = std::make_unique<HuffmanTreeNode>(std::move(min1));
        //���ڶ�СԪ���ƶ����Һ���
        parent.right = std::make_unique<HuffmanTreeNode>(std::move(min2));
        //�����ڵ����С����
        minHeap.Insert(std::move(parent));
    }
    //�������һ���ڵ�
    if (!minHeap.IsEmpty())
    {
        //�Ƶ����ڵ�
        this->root = std::make_unique<HuffmanTreeNode>(minHeap.RemoveMin());
    }
    //�ṩһ����ֵ����ʱ����
    std::string code;
    //�ݹ������ַ�����
    this->MakeCodes(&this->root, code);
}

//�����ַ�
template<class CharType, class WeightType>
inline std::string HuffmanTree<CharType, WeightType>::Encode(CharType ch)
{
    // ���ַ�����ӳ���в鵽ch���ַ�����
    // C++ 17:����ʼ������if���
    if (auto it = this->codes.find(ch); 
        it != this->codes.end())
    {
        //�����ַ�����
        return this->codes.find(ch)->second;
    }
    //δ���ҵ��ַ�,�׳��쳣
    throw std::exception("char not found!");
}

//�����ַ�����
template<class CharType, class WeightType>
std::string HuffmanTree<CharType, WeightType>::
Encode(std::vector<CharType> chars)
{
    //������ַ���
    std::string codedString;
    //���β�ѯ�ַ�����
    for (const auto& ch : chars)
    {
        // ���ַ�����ӳ���в鵽ch���ַ�����
        // C++ 17:����ʼ������if���
        if (auto it = this->codes.find(ch);
            it != this->codes.end())
        {
            //����ַ����뵽������ַ���
            codedString.append(this->codes.find(ch)->second);
        }
        else
        {
            //δ���ҵ��ַ�,�׳��쳣
            throw std::exception("chars contains undefined character!");
        }
    }
    //���ر�����ַ���
    return codedString;
}

//�����ַ���
template<class CharType, class WeightType>
inline std::vector<CharType> HuffmanTree<CharType, WeightType>::
Decode(const std::string & strCode)
{
    //������
    std::vector<CharType> decodedList;
    //��ǰ����Ԫ��ָ��
    auto current = &this->root;
    //������������ǿյ�
    if ((*current)->left == nullptr)
    {
        //���ؿ�����
        return decodedList;
    }
    //���������ַ���
    for (auto it = strCode.cbegin(); it != strCode.cend(); ++it)
    {
        //�����ǰ�ڵ�����Ϊ��
        //˵����ǰ�ڵ�ΪҶ�ӽڵ�
        if ((*current)->left == nullptr)
        {
            //���������뵱ǰ�ڵ��ַ�
            decodedList.push_back((*current)->content.ch);
            //���õ�ǰָ��
            current = &this->root;
            //�˻�ǰһ�ַ�
            --it;
            //��������ѭ��
            continue;
        }
        //�����ǰ�ַ�Ϊ'0'
        if (*it == '0')
        {
            //��ǰָ��ָ������
            current = &(*current)->left;
            continue;
        }
        //����ָ���Һ���
        current = &(*current)->right;
    }
    //�������һλ�ַ�
    if ((*current)->left == nullptr)
    {
        //�����������һ�������Ԫ��
        decodedList.push_back((*current)->content.ch);
    }
    //���ؽ��
    return decodedList;
}

// �����ƶ���ֵ�����
template<class CharType, class WeightType>
inline HuffmanTree<CharType, WeightType> & HuffmanTree<CharType, WeightType>::operator=(HuffmanTree && other)
{
    // �Ը�ֵ�ж�
    if (this != &other)
    {
        //�ƶ�����ӳ��
        this->codes = std::move(other.codes);
        //�ƶ����ڵ�
        this->root = std::move(other.root);
    }
    //������������
    return *this;
}

