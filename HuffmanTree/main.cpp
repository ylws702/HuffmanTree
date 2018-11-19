// HuffmanTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "HuffmanTree.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

int main()
{
    std::random_device rd;
    std::vector<int> a(1'00);
    std::vector<char> b(1'00);
    for (auto&i : b)
    {
        i = rd() % 10;
    }
    std::iota(a.begin(), a.end(), 1);
    HuffmanTree<char, int> tree(b, a);
    std::cout << tree.root->content.weight << '\n';
    const auto t0 = std::chrono::high_resolution_clock::now();
    const auto t1 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration<double>(t1 - t0).count() << '\n';
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
