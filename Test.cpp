#include<iostream>
#include<cassert>
#include<vector>

#include "Heap.h"
#include "AVLtree.h"
#include "Test.h"


class Counter {
public:
    Counter();
    Counter(const Counter& other);
    ~Counter();
    static size_t GetCount();
private:
    static size_t _count;
};

size_t Counter::_count = 0;

Counter::Counter() {
    ++_count;
}

Counter::Counter(const Counter& other) {
    ++_count;
}


Counter::~Counter() {
    --_count;
}

size_t Counter::GetCount() {
    return _count;
}

bool operator<(const Counter& first, const Counter& second) {
    return &first < &second;
}

void Test() {
    HeapTest();
    AVLTest();
}

void HeapTest() {
    std::cout << "Heap tests." << std::endl << std::endl;

    std::cout << "Test1. memory test: ";
    {
        Heap<Counter, int> heap;
        heap.Push(Counter(), 0);
        heap.Push(Counter(), 0);
        heap.Pop();
        heap.Push(Counter(), 0);
    }
    assert(Counter::GetCount() == 0);
    std::cout << "Done" << std::endl;

    std::cout << "Test2. Default comporator test: ";
    {
        Heap<int, int> heap;
        heap.Push(3, 1);
        assert(heap.Top().first == 3);
        assert(heap.Top().second == 1);
        heap.Push(5, 2);
        heap.Pop();
        heap.Push(8, 3);
        assert(heap.Top().first == 5);
        assert(heap.Top().second == 2);
        heap.Push(4, 0);
        assert(heap.Top().first == 4);
        assert(heap.Top().second == 0);
    }
    std::cout << "Done" << std::endl;

    std::cout << "Test3. Greater comporator test: ";
    {
        Heap<int, int, std::greater<int>> heap;
        heap.Push(3, 1);
        assert(heap.Top().first == 3);
        assert(heap.Top().second == 1);
        heap.Push(5, 2);
        heap.Pop();
        heap.Push(8, 3);
        assert(heap.Top().first == 8);
        assert(heap.Top().second == 3);
        heap.Push(4, 0);
        assert(heap.Top().first == 8);
        assert(heap.Top().second == 3);
    }
    std::cout << "Done" << std::endl;

    std::cout << "Test4. Heap sort test: ";
    {
        std::vector<int> vec = { 4, 2, 8, 1, 7 , 9 , 2 };
        std::vector<int> sorted = { 1, 2, 2, 4, 7, 8, 9 };
        Heap<int, int> heap;
        for (size_t i = 0; i < vec.size(); ++i) {
            heap.Push(vec[i], vec[i]);
        }
        for (size_t i = 0; i < vec.size(); ++i) {
            vec[i] = heap.Top().first;
            heap.Pop();
        }
        for (size_t i = 0; i < vec.size(); ++i) {
            assert(vec[i] == sorted[i]);
        }
    }
    std::cout << "Done" << std::endl;
}

void AVLTest() {
    std::cout << "AVL tests." << std::endl << std::endl;

    std::cout << "Test1. memory test: ";
    {
        AVLtree<Counter, int> avl;
        avl.Insert(Counter(), 2);
        avl.Insert(Counter(), 5);
        avl.Insert(Counter(), 7);
        avl.Erase(Counter());
        avl.Insert(Counter(), 0);
    }
    assert(Counter::GetCount() == 0);
    std::cout << "Done" << std::endl;

    std::cout << "Test2. Insert and Find test: ";
    {
        AVLtree<int, int> avl;
        avl.Insert(3, 1);
        avl.Insert(5, 1);
        avl.Insert(2, 1);
        assert(avl.Find(5));
        assert(!avl.Find(8));
        assert(avl.Size() == 3);
        avl.Insert(-5, 1);
        avl.Insert(12, 1);
        assert(avl.Find(12));
        assert(!avl.Find(7));
        assert(avl.Size() == 5);
        avl.Insert(2, 17);
        assert(avl.Size() == 5);
    }
    std::cout << "Done" << std::endl;

    std::cout << "Test3. Operator[] test: ";
    {
        AVLtree<int, int> avl;
        avl.Insert(3, 1);
        avl.Insert(5, 8);
        avl.Insert(2, 15);
        assert(avl.Size() == 3);
        assert(avl[5] == 8);
        assert(avl[10] == 0);
        assert(avl.Find(10));
        assert(avl.Size() == 4);
        avl.Insert(-5, 1);
        avl.Insert(12, 1);
        avl[12] = 20;
        assert(avl[12] == 20);
        assert(!avl.Find(7));
        assert(avl.Size() == 6);
        avl.Insert(2, 17);
        assert(avl.Size() == 6);
        assert(avl[2] == 17);
    }
    std::cout << "Done" << std::endl;

    std::cout << "Test4. Erase test: ";
    {
        AVLtree<int, int> avl;
        avl.Insert(3, 1);
        avl.Insert(5, 8);
        avl.Insert(2, 15);
        avl.Erase(5);
        avl.Erase(10);
        assert(avl.Size() == 2);
        assert(!avl.Find(5));
        assert(avl.Find(3));
    }
    std::cout << "Done" << std::endl;

    std::cout << "Test5. StringFormat test: ";
    {
        AVLtree<int, int> avl;
        avl.Insert(3, 1);
        avl.Insert(5, 8);
        avl.Insert(2, 15);
        avl.Insert(10, 1);
        avl.Insert(-5, 8);
        avl.Insert(6, 15);
        auto res = avl.GoThrough("[L]<C>{R}");
        assert(res == "[[<-5 , 8>]<2 , 15>]<3 , 1>{[<5 , 8>]<6 , 15>{<10 , 1>}}");
        avl.Erase(10);
        res = avl.GoThrough("[L]<C>{R}");
        assert(res == "[[<-5 , 8>]<2 , 15>]<3 , 1>{[<5 , 8>]<6 , 15>}");
        res = avl.GoThrough("[R]<L>{C}");
        assert(res == "[<{5 , 8}>{6 , 15}]<<{-5 , 8}>{2 , 15}>{3 , 1}");
    }
    std::cout << "Done" << std::endl;

    std::cout << "Test6. SubTree test: ";
    {
        AVLtree<int, int> avl;
        avl.Insert(3, 1);
        avl.Insert(5, 8);
        avl.Insert(2, 15);
        avl.Insert(10, 1);
        avl.Insert(-5, 8);
        avl.Insert(6, 15);
        auto sub_tree = avl.SubTree(6);
        assert(sub_tree.GoThrough("[L]<C>{R}") == "[<5 , 8>]<6 , 15>{<10 , 1>}");
    }
    std::cout << "Done" << std::endl;
}