//
// Created by froonn on 15/12/24.
//

#include "memory_manager.h"

MemoryManager::MemoryManager(int size) {
    this->size_ = size;
    this->memory_ = malloc(size);
}

MemoryManager::MemoryManager(const MemoryManager &mm) {
    this->size_ = mm.size_;
    this->memory_ = malloc(size_);
    memcpy(this->memory_, mm.memory_, size_);
    this->nodes_ = mm.nodes_;
}

MemoryManager::~MemoryManager() {
    ::free(this->memory_);
}

void *MemoryManager::write(const void *src, int size) {
    void *ptr = findFree(size);
    if (ptr == nullptr) { return nullptr; }
    memcpy(ptr, src, size);

    this->getStatus();

    return ptr;
}

bool MemoryManager::free(const void *ptr) {
    auto original_size = this->nodes_.size();
    this->nodes_.erase(std::remove_if(this->nodes_.begin(), this->nodes_.end(),
                                      [ptr](const Node &node) { return node.ptr == ptr; }), this->nodes_.end());
    return this->nodes_.size() != original_size;
}

std::pair<int, int> MemoryManager::fragmentation() const {
    int total_empty = 0, total_used = 0;
    if (this->nodes_.empty()) { return {0, 0}; }

    char *ptr = (char *) this->memory_;
    int size = 0;
    for (const auto &node: this->nodes_) {
        total_used += node.size;
        total_empty += (char *) node.ptr - size - ptr;

        ptr = (char *) node.ptr;
        size = node.size;
    }

    return {total_empty, total_used};
}

void MemoryManager::getStatus() const {
    for (int i = 0; i < this->size_; i += 1) {
        std::cout << static_cast<char *>(this->memory_)[i];
    }
    std::cout << std::endl;
    for (const auto &node: this->nodes_) {
        // if (node == this->nodes_.end()) { continue; }
        std::cout << node.ptr << " " << node.size << std::endl;
    }
}

void *MemoryManager::findFree(int size) {
    int tmp;

    if (size > this->size_) {
        return nullptr;
    }

    if (this->nodes_.empty()) {
        this->nodes_.push_back({this->memory_, size});
        return this->memory_;
    }

    auto node_old = nodes_.begin();

    auto tmp_ptr_1 = node_old->ptr, tmp_ptr_2 = this->memory_;

    if (tmp_ptr_1 != tmp_ptr_2) {
        if ((char *) node_old->ptr - (char *) this->memory_ >= size) {
            this->nodes_.insert(node_old, {this->memory_, size});
            return this->memory_;
        }
    }

    for (const auto &node: this->nodes_) {
        // if () { continue; }
        if (node_old->ptr == node.ptr) { continue; }

        tmp = (char *) node.ptr - (char *) node_old->ptr - node_old->size;
        if (tmp >= size) {
            this->nodes_.insert(node_old, {(char *) node_old->ptr + node_old->size, size});
            return (char *) node_old->ptr + node_old->size;
        }

        node_old++;
    }

    tmp = (char *) this->memory_ + this->size_ - (char *) node_old->ptr - node_old->size;
    if (tmp >= size) {
        this->nodes_.push_back({(char *) node_old->ptr + node_old->size, size});
        return (char *) node_old->ptr + node_old->size;
    }

    return nullptr;
}
