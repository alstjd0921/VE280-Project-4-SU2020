#include "binaryTree.h"
#include "huffmanTree.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

int min_freq(Node **node, const int *arr) {
    int min = 0;
    int num = -1;
    for (int i = 0; i < 55; i++) {
        if (arr[i] == 0) {
            continue;
        } else {
            if (min == 0) {
                min = arr[i];
                num = i;
                continue;
            }
            if (arr[i] < min || (arr[i] == min && node[i]->getstr() < node[num]->getstr())) {
                min = arr[i];
                num = i;
            }
        }
    }

    return num;
}

Node *mergeNode(Node *leftNode, Node *rightNode) {
    return new Node(leftNode->getstr() + rightNode->getstr(), leftNode->getnum() + rightNode->getnum(), leftNode,
                    rightNode);
}

int main(int argc, char *argv[]) {
    int count = 0, freq[55];
    Node *node[55];
    char buffer;
    bool flag;

    std::fill_n(freq, 55, 0);

    flag = argc == 3;

    std::string name = argv[argc - 1];
    std::ifstream file;
    file.open(name);

    while (file.get(buffer)) {
        if (buffer == ' ') {
            freq[26]++;
        } else if (buffer == '\n') {
            freq[27]++;
        } else {
            freq[buffer - 'a']++;
        }
    }

    for (int i = 0; i < 26; i++) {
        if (freq[i] != 0) {
            count++;
            node[i] = new Node(std::string(1, char(i + 'a')), freq[i]);
        }
    }

    if (freq[26] != 0) {
        node[26] = new Node(" ", freq[26]);
        count++;
    }
    if (freq[27] != 0) {
        node[27] = new Node("\n", freq[27]);
        count++;
    }

    int index = 28;
    while (count > 1) {
        int right = min_freq(node, freq);
        freq[right] = 0;
        int left = min_freq(node, freq);
        freq[left] = 0;

        node[index] = mergeNode(node[left], node[right]);
        freq[index] = node[index]->getnum();
        index++;
        count--;
    }

    HuffmanTree tree(node[index - 1]);

    if (flag) {
        tree.printTree();
    } else {
        file.close();
        file.open(name);
        while (file.get(buffer)) {
            std::cout << tree.findPath(std::string(1, buffer)) << " ";
        }
    }
    file.close();

    return 0;
}