// HuffmanTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "HuffmanTree.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>

int main()
{
    //可能抛出异常的代码
    try
    {
        //要编码的字符串
        std::string str;
        std::cout << "输入一个字符串:";
        //获取整行,包括空格
        std::getline(std::cin, str);
        //计数映射
        std::map<char,unsigned> charCount;
        //遍历字符串字符
        for (const auto ch : str)
        {
            //在计数映射中查找ch的位置
            auto it = charCount.find(ch);
            //如果没有找到
            if (it==charCount.cend())
            {
                //新插入一个,数目为1
                charCount.insert({ ch,1 });
                //继续循环
                continue;
            }
            //ch的数目加1
            ++it->second;
        }
        //字符集
        std::vector<char> charSet;
        //字符计数集
        std::vector<unsigned> charCountSet;
        std::cout << "字符串计数结果:\n";
        //打印计数结果
        //使用C++17的结构化绑定
        for (auto[ch, count] : charCount)
        {
            //打印
            std::cout << ch << ':' << count << "个\n";
            //字符放入字符集
            charSet.push_back(ch);
            //字符计数放入字符计数集
            charCountSet.push_back(count);
        }
        //构造哈夫曼树
        HuffmanTree tree(charSet, charCountSet);
        std::cout << "字符编码映射:\n";
        //遍历哈夫曼树输出各字符编码
        tree.Traverse([](auto ch, auto&code)
        {
            std::cout << ch << ':' << code << '\n';
        });
        //编码后的01串
        auto encodedString = tree.Encode(std::vector(str.cbegin(), str.cend()));
        std::cout << "字符串编码结果:" << encodedString<<'\n';
        std::cout << "字符串编码解码结果:";
        //解码01串并遍历打印结果
        for (auto ch : tree.Decode(encodedString))
        {
            //打印遍历的字符
            std::cout << ch;
        }
        std::cout << '\n';
    }
    //捕获异常
    catch (const std::exception& e)
    {
        //打印异常信息
        std::cout << e.what() << '\n';
    }
    // main函数默认返回0
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
