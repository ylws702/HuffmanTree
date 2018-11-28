#pragma once

#include "MinHeap.h"
#include "TreeNode.h"
#include <functional>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

// 哈夫曼树类模板
// CharType:字符类型
// WeightType:计数变量类型
template <class CharType, class WeightType>
class HuffmanTree
{
protected:
    // 哈夫曼树节点包含内容结构体
    struct HuffmanTreeNodeContent;
    // 哈夫曼树节点结构体
    struct HuffmanTreeNode;
    // 根节点指针
    // ps:使用std::unique_ptr<HuffmanTreeNode>会导致root与子节点类型不同
    std::unique_ptr<TreeNode<HuffmanTreeNodeContent>> root;
    // 字符编码映射
    std::map<CharType, std::string> codes;
    // 生成字符编码
    void MakeCodes(decltype(&root) current, std::string & code);
public:
    // 哈夫曼树方法声明及重载编译系统默认方法声明:
    // 由字符,权值和字符个数构造哈夫曼树
    HuffmanTree(const CharType ch[], const WeightType w[], int n);
    // 由字符,权值和字符个数构造哈夫曼树
    //HuffmanTree(const CharType ch[], const WeightType w[], int n);
    // 由字符,权值向量构造哈夫曼树
    HuffmanTree(const std::vector<CharType>& chars,
        const std::vector<WeightType>& weights) :
        // 调用已有构造函数
        HuffmanTree(chars.data(), weights.data(), (int)chars.size())
    {}
    // 移动构造函数模板
    HuffmanTree(HuffmanTree &&other) :
        //移动字符编码映射
        codes(std::move(other.codes)),
        //移动根节点指针
        root(std::move(other.root))
    {}
    // 使用默认析构函数模板
    //virtual ~HuffmanTree();
    // 编码字符
    std::string Encode(CharType ch)const;
    // 使用左值编码字符向量
    std::string Encode(const std::vector<CharType>& chars)const;
    // 使用右值编码字符向量
    std::string Encode(std::vector<CharType>&& chars)const;
    //使用函数f遍历字符编码
    //函数f接受CharType和std::string型const引用,无返回值
    void Traverse(const std::function<void(CharType,const std::string&)>f)const;
    // 译码字符串
    std::vector<CharType> Decode(const std::string& strCode)const;
    // 重载移动赋值运算符
    HuffmanTree &operator=(HuffmanTree&& copy);
};

// 哈夫曼树节点包含内容结构体
template <class CharType, class WeightType>
struct HuffmanTree<CharType, WeightType>::HuffmanTreeNodeContent
{
    //字符
    CharType ch;
    //字符权重
    WeightType weight;

    //重载小于等于运算符
    bool operator<=(const HuffmanTreeNodeContent& other)const
    {
        //依据权重比较
        return this->weight <= other.weight;
    }

    //重载小于运算符
    bool operator<(const HuffmanTreeNodeContent& other)const
    {
        //依据权重比较
        return this->weight < other.weight;
    }

    //重载大于运算符
    bool operator>(const HuffmanTreeNodeContent& other)const
    {
        //依据权重比较
        return this->weight > other.weight;
    }
};

// 哈夫曼树节点结构体
template <class CharType, class WeightType>
struct HuffmanTree<CharType, WeightType>::HuffmanTreeNode :
    // 继承TreeNode<HuffmanTreeNodeContent>
    // 结构体默认public继承
    TreeNode<HuffmanTreeNodeContent>
{
    // 禁用默认构造函数
    HuffmanTreeNode() = delete;

    // 禁用复制构造函数
    HuffmanTreeNode(HuffmanTreeNode&) = delete;

    // 移动构造函数
    HuffmanTreeNode(HuffmanTreeNode&& other)noexcept :
        //调用父类构造函数
        TreeNode<HuffmanTreeNodeContent>(HuffmanTreeNodeContent())
    {
        // 移动内容
        this->content = std::move(other.content);
        // 移动左孩子
        this->left = std::move(other.left);
        // 移动右孩子
        this->right = std::move(other.right);
    }

    //通过哈夫曼叶节点权值构造
    HuffmanTreeNode(WeightType weight) :
        //调用父类构造函数
        TreeNode<HuffmanTreeNodeContent>(HuffmanTreeNodeContent())
    {
        this->content.weight = weight;
    }

    // 通过哈夫曼叶节点左值构造
    HuffmanTreeNode(const HuffmanTreeNodeContent& content) :
        //调用父类构造函数
        TreeNode<HuffmanTreeNodeContent>(HuffmanTreeNodeContent())
    {
        // 复制内容
        this->content = content;
    }

    // 通过哈夫曼叶节点右值构造
    HuffmanTreeNode(HuffmanTreeNodeContent&& content) :
        // 移动内容,调用父类构造函数
        TreeNode<HuffmanTreeNodeContent>(std::move(content))
    {}

    // 重载移动赋值运算符
    HuffmanTreeNode& operator=(HuffmanTreeNode&& other)noexcept
    {
        // 自赋值判定
        if (this != &other)
        {
            //移动内容
            this->content = std::move(other.content);
            //移动左孩子
            this->left = std::move(other.left);
            //移动右孩子
            this->right = std::move(other.right);
        }
        //返回自身引用
        return *this;
    }

    //重载小于等于运算符
    bool operator<=(const HuffmanTreeNode& other)const
    {
        //依据权重比较
        return this->content.weight <= other.content.weight;
    }

    //重载小于运算符
    bool operator<(const HuffmanTreeNode& other)const
    {
        //依据权重比较
        return this->content.weight < other.content.weight;
    }

    //重载大于运算符
    bool operator>(const HuffmanTreeNode& other)const
    {
        //依据权重比较
        return this->content.weight > other.content.weight;
    }
};

// 生成字符编码
template<class CharType, class WeightType>
inline void HuffmanTree<CharType, WeightType>::
MakeCodes(decltype(&root) current, std::string & code)
{
    //若左孩子为空,说明该节点为叶子节点
    if ((*current)->left == nullptr)
    {
        //插入字符编码
        this->codes.insert({ (*current)->content.ch,code });
        //结束递归
        return;
    }
    //编码字符串末端先添0
    code.push_back('0');
    //再递归访问左孩子
    this->MakeCodes(&(*current)->left, code);
    //编码字符串末端换成1
    code.back() = '1';
    //再递归访问右孩子
    this->MakeCodes(&(*current)->right, code);
    //去掉末尾的1
    code.pop_back();
    //结束递归
}

//由字符,权值和字符个数构造哈夫曼树
template<class CharType, class WeightType>
inline HuffmanTree<CharType, WeightType>::
HuffmanTree(const CharType ch[], const WeightType w[], int n)
{
    //错误的字符种类个数
    if (n <= 0)
    {
        return;
    }
    //只有一种字符
    if (n == 1)
    {
        //直接将其编码为0
        this->codes.insert({ *ch,"0" });
        //放在根节点上
        this->root =
            std::make_unique<HuffmanTreeNode>(HuffmanTreeNodeContent{ *ch,*w });
        return;
    }
    //创建小顶堆
    MinHeap<HuffmanTreeNode> minHeap;
    //向小顶堆依次插入带权值字符节点
    for (int i = 0; i < n; ++i)
    {
        minHeap.Insert(HuffmanTreeNode({ ch[i],w[i] }));
    }
    //构造哈夫曼树
    while (minHeap.Size() >= 2)
    {
        //获取最小元素
        auto&&min1 = minHeap.RemoveMin();
        //获取第二小元素
        auto&&min2 = minHeap.RemoveMin();
        //生成其父哈夫曼树节点,权值为最小元素与第二小元素权值之和
        HuffmanTreeNode parent(min1.content.weight + min2.content.weight);
        //将最小元素移动到左孩子
        parent.left = std::make_unique<HuffmanTreeNode>(std::move(min1));
        //将第二小元素移动到右孩子
        parent.right = std::make_unique<HuffmanTreeNode>(std::move(min2));
        //将父节点插入小顶堆
        minHeap.Insert(std::move(parent));
    }
    //处理最后一个节点
    if (!minHeap.IsEmpty())
    {
        //移到根节点
        this->root = std::make_unique<HuffmanTreeNode>(minHeap.RemoveMin());
    }
    //提供一个左值的临时变量
    std::string code;
    //递归生成字符编码
    this->MakeCodes(&this->root, code);
}

//编码字符
template<class CharType, class WeightType>
inline std::string HuffmanTree<CharType, WeightType>::
Encode(CharType ch)const
{
    // 从字符编码映射中查到ch的字符编码
    // C++ 17:带初始化语句的if语句
    if (auto it = this->codes.find(ch);
        it != this->codes.end())
    {
        //返回字符编码
        return this->codes.find(ch)->second;
    }
    //未查找到字符,抛出异常
    throw std::runtime_error("char not found!");
}

template<class CharType, class WeightType>
inline std::string HuffmanTree<CharType, WeightType>::
Encode(const std::vector<CharType>& chars) const
{
    //编码的字符串
    std::string codedString;
    //依次查询字符编码
    for (const auto& ch : chars)
    {
        // 从字符编码映射中查到ch的字符编码
        // C++ 17:带初始化语句的if语句
        if (auto it = this->codes.find(ch);
            it != this->codes.end())
        {
            //添加字符编码到编码的字符串
            codedString.append(this->codes.find(ch)->second);
        }
        else
        {
            //未查找到字符,抛出异常
            throw std::range_error("chars contains undefined character!");
        }
    }
    //返回编码的字符串
    return codedString;
}

template<class CharType, class WeightType>
inline std::string HuffmanTree<CharType, WeightType>::
Encode(std::vector<CharType>&& chars) const
{
    //编码的字符串
    std::string codedString;
    //依次查询字符编码
    for (auto& ch : std::move(chars))
    {
        // 从字符编码映射中查到ch的字符编码
        // C++ 17:带初始化语句的if语句
        if (auto it = this->codes.find(ch);
            it != this->codes.end())
        {
            //添加字符编码到编码的字符串
            codedString.append(this->codes.find(ch)->second);
        }
        else
        {
            //未查找到字符,抛出异常
            throw std::range_error("chars contains undefined character!");
        }
    }
    //返回编码的字符串
    return codedString;
}


//使用函数f遍历字符编码
template<class CharType, class WeightType>
inline void HuffmanTree<CharType, WeightType>::
Traverse(const std::function<void(CharType, const std::string&)> f) const
{
    //C++ 17:结构化绑定
    for (const auto&[ch, code] : this->codes)
    {
        //依次对字符编码映射中的元素对调用函数f
        f(ch, code);
    }
}

//译码字符串
template<class CharType, class WeightType>
inline std::vector<CharType> HuffmanTree<CharType, WeightType>::
Decode(const std::string & strCode)const
{
    //译码结果
    std::vector<CharType> decodedList;
    //当前操作元素指针
    auto current = &this->root;
    //如果哈夫曼树是空的
    if ((*current)->left == nullptr)
    {
        //返回空向量
        return decodedList;
    }
    //遍历编码字符串
    for (auto it = strCode.cbegin(); it != strCode.cend(); ++it)
    {
        //如果当前节点左孩子为空
        //说明当前节点为叶子节点
        if ((*current)->left == nullptr)
        {
            //向结果中添入当前节点字符
            decodedList.push_back((*current)->content.ch);
            //重置当前指针
            current = &this->root;
            //退回前一字符
            --it;
            //继续遍历循环
            continue;
        }
        //如果当前字符为'0'
        if (*it == '0')
        {
            //当前指针指向左孩子
            current = &(*current)->left;
            //继续遍历循环
            continue;
        }
        //否则指向右孩子
        current = &(*current)->right;
    }
    //处理最后一位字符
    if ((*current)->left == nullptr)
    {
        //向结果添入最后一个译码的元素
        decodedList.push_back((*current)->content.ch);
    }
    //返回结果
    return decodedList;
}

// 重载移动赋值运算符
template<class CharType, class WeightType>
inline HuffmanTree<CharType, WeightType> & HuffmanTree<CharType, WeightType>::
operator=(HuffmanTree && other)
{
    // 自赋值判定
    if (this != &other)
    {
        //移动编码映射
        this->codes = std::move(other.codes);
        //移动根节点
        this->root = std::move(other.root);
    }
    //返回自身引用
    return *this;
}

