cmake_minimum_required(VERSION 3.10)
project(huffman_p4)

set(CMAKE_CXX_STANDARD 17)

add_executable(compress compress.cpp binaryTree.cpp huffmanTree.cpp)
add_executable(decompress decompress.cpp binaryTree.cpp huffmanTree.cpp)