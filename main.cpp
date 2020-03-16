#include <iostream>
#include <chrono>
#include "huffman-code.cpp"

int main() {
    auto t1 = std::chrono::high_resolution_clock::now();
    std::string str=buildHuffmanTree();
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

    std::cout<<"first: " << duration;

    t1 = std::chrono::high_resolution_clock::now();
    decodeHuffman(str);
    t2 = std::chrono::high_resolution_clock::now();

    duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

    std::cout<<"second : " << duration;
    return 0;
}
