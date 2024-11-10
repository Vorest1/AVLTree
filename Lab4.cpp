#include<iostream>

#include "Test.h"
#include "Heap.h"
#include "AVLtree.h"

int main() {
    std::cout << "Insert Object type:\n"
        "1. Heap\n"
        "2. AvlTree\n"
        "3. Test ALL\n";
    int type;
    std::cin >> type;
    if (type == 1) {
        Heap<int, int> heap;
        while (true) {
            std::cout <<
                "Choose option:\n"
                "1. Insert \n"
                "2. Check top\n"
                "3. Erase\n"
                "4. Check Size\n"
                "5. Test\n"
                "6. Exit\n";
            std::cin >> type;
            if (type == 1) {
                std::cout << "insert key\n";
                int key;
                std::cin >> key;
                std::cout << "insert value\n";
                int value;
                std::cin >> value;
                heap.Push(key, value);
                continue;
            }
            if (type == 2) {
                std::cout << heap.Top().first << " " << heap.Top().second << std::endl;
                continue;
            }
            if (type == 3) {
                heap.Pop();
                continue;
            }
            if (type == 4) {
                std::cout << "Size is: " << heap.Size() << std::endl;
                continue;
            }
            if (type == 5) {
                HeapTest();
                continue;
            }
            if (type == 6) {
                return 0;
            }
        }
    }
    else if (type == 2) {
        AVLtree<int, int> avl_tree;
        while (true) {
            std::cout <<
                "Choose option:\n"
                "1. Insert \n"
                "2. Find\n"
                "3. Erase\n"
                "4. Check Size\n"
                "5. Format output\n"
                "6. SubTree\n"
                "7. Test\n"
                "8. Exit\n";
            std::cin >> type;
            if (type == 1) {
                std::cout << "insert key\n";
                int key;
                std::cin >> key;
                std::cout << "insert value\n";
                int value;
                std::cin >> value;
                avl_tree.Insert(key, value);
                continue;
            }
            if (type == 2) {
                std::cout << "insert key\n";
                int key;
                std::cin >> key;
                if (!avl_tree.Find(key)) {
                    std::cout << "No such key\n";
                    continue;
                }
                std::cout << "Value: " << avl_tree[key] << std::endl;
                continue;
            }
            if (type == 3) {
                std::cout << "insert key\n";
                int key;
                std::cin >> key;
                avl_tree.Erase(key);
                continue;
            }
            if (type == 4) {
                std::cout << "Size is: " << avl_tree.Size() << std::endl;
                continue;
            }
            if (type == 5) {
                std::cout << "insert format\n";
                std::string format;
                std::cin >> format;
                std::cout << avl_tree.GoThrough(format) << std::endl;
                continue;
            }
            if (type == 6) {
                std::cout << "insert key\n";
                int key;
                std::cin >> key;
                auto sub_tree = avl_tree.SubTree(key);
                std::cout << sub_tree.GoThrough("[L][C][R]") << std::endl;
                continue;
            }
            if (type == 7) {
                AVLTest();
                continue;
            }
            if (type == 8) {
                return 0;
            }
        }
    }
    else {
        Test();
    }

}