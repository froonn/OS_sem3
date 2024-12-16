//
// Created by froonn on 15/12/24.
//

#include "file_system.h"

FileSystem::FileSystem(int size) {
    this->mm_ = MemoryManager(size);
}

FileSystem::FileSystem(const FileSystem &fs) {
    this->mm_ = MemoryManager(fs.mm_);
    for (auto &f : fs.files_) {
        File file;
        file.name = (char *) this->mm_.write(f.name, strlen(f.name));
        file.content = (char *) this->mm_.write(f.content, strlen(f.content));
        file.size = f.size;

        this->files_.push_back(file);
    }
}

bool FileSystem::createFile(char *name, char *content) {
    File file;

    file.name = (char *) this->mm_.write((void *) name, strlen(name) + 1);
    file.content = (char *) this->mm_.write((void *) content, strlen(content) + 1);
    file.size = strlen(content) + 1;

    this->files_.push_back(file);

    this->mm_.getStatus();
}

bool FileSystem::createFile(char *name, int size) {
    File file;


    char* str = new char[size + 1];
    std::fill(str, str + size, '\0');

    file.name = (char *) this->mm_.write(name, strlen(name));
    file.content = (char *) this->mm_.write(str, size);
    file.size = size;

    this->files_.push_back(file);

    this->mm_.getStatus();
}
