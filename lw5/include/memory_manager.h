//
// Created by froonn on 15/12/24.
//

#ifndef FILE_H
#define FILE_H

#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>


struct Node {
    void *ptr = nullptr;
    int size;
};

class MemoryManager {
public:
    explicit MemoryManager(int size = 4096);
    MemoryManager(const MemoryManager &mm);
    ~MemoryManager();

    void * write(const void *src, int size);

    bool free(const void *ptr);

    [[nodiscard]] std::pair<int, int> fragmentation() const;
    [[nodiscard]] int getSize() const { return size_; }

    void getStatus() const;

private:
    void * findFree(int size);
    
    int size_;
    std::vector<Node> nodes_;
    void *memory_;
      
};

#endif //FILE_H
