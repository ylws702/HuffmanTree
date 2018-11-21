// HuffmanTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "HuffmanTree.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <ratio>
#include <random>
#include <vector>

int main()
{
    // 字符集大小
    constexpr auto charSetSize = 50'000;
    for (int i = 0; i < 5; ++i)
    {
        // 随机数生成器
        std::random_device randomDevice;
        // char16_t 字符集
        std::vector<char16_t> charSet(charSetSize);
        // 字符集各字符数目
        std::vector<unsigned> charCountSet(charSetSize);
        // 基于范围的 for 循环
        // 字符数目随机设置为 1-100
        for (auto&i : charCountSet)
        {
            i = randomDevice() % 100 + 1;
        }
        // 顺序递增值填充字符集从 1 到 charSetSize
        std::iota(charSet.begin(), charSet.end(), 1);
        // 记录时间 t0
        const auto t0 = std::chrono::high_resolution_clock::now();
        // C++ 17 类模板实参推导
        // 构造哈夫曼树
        HuffmanTree tree(charSet.data(), charCountSet.data(), (int)charSet.size());
        // 记录时间 t1
        const auto t1 = std::chrono::high_resolution_clock::now();
        // 打印构造哈夫曼树耗时
        std::cout <<
            std::chrono::duration_cast<
                std::chrono::duration<double, std::milli>>
            (t1 - t0).count() << "(ms)\n";
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
