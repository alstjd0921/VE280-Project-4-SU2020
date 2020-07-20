#include "binaryTree.h"
#include "huffmanTree.h"
#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char *argv[]) {
    if (argc < 3 || argc > 3) {
        std::cout << "Wrong number of argument!" << std::endl;
        return 0;
    }

    std::string file1 = argv[1];
    std::string file2 = argv[2];

    HuffmanTree tree(file1);

    std::ifstream file;
    file.open(file2);

    std::string code;
    bool flag = true;
    while (getline(file, code, ' ') && flag == 1) {
        flag = false;
        if (code == tree.findPath(" ")) {
            std::cout << " ";
            flag = true;
            continue;
        } else if (code == tree.findPath("\n")) {
            std::cout << std::endl;
            flag = true;
            continue;
        } else {
            for (int i = 0; i < 26; i++) {
                if (code == tree.findPath(std::string(1, i + 'a'))) {
                    std::cout << std::string(1, i + 'a');
                    flag = true;
                    break;
                }
            }
            continue;
        }
    }
    if (!flag) {
        std::cout << "No matching character for the binary code!" << std::endl;
    }
    file.close();

    return 0;
}