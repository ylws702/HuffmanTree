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
    constexpr auto charSetSize = 1'0000;
    for (int i = 0; i < 5; i++)
    {
        std::random_device randomDevice;
        std::vector<char16_t> charSet(charSetSize);
        std::vector<unsigned> charCountSet(charSetSize);
        for (auto&i : charCountSet)
        {
            i = randomDevice() % 100;
        }
        std::iota(charSet.begin(), charSet.end(), 1);
        const auto t0 = std::chrono::high_resolution_clock::now();
        //C++ 17 类模板模板参数自动推导
        HuffmanTree tree(charSet.data(), charCountSet.data(), charSet.size());
        //std::cout << tree.root->content.weight << '\n';
        const auto t1 = std::chrono::high_resolution_clock::now();
        std::cout <<
            std::chrono::duration_cast<std::chrono::duration<double, std::milli>>
            (t1 - t0).count() << "(ms)\n";
    }
    //main函数默认返回0
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
