//
// Created by froonn on 15/12/24.
//

#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <string>
#include <vector>
#include "memory_manager.h"

struct File {
    char *name;
    char *content;
    int size;
};

class FileSystem {
public:
    explicit FileSystem(int size = 4096);
    FileSystem(const FileSystem &fs);
    // ~FileSystem();

    bool createFile(char *name, char *content = "");

    bool createFile(char *name, int size);

    bool deleteFile(std::string);

    bool copyFile(char *src, char *dst);

    bool moveFile(char *src, char *dst);

    bool writeFile(char *name, char *content);

    std::string readFile(char *name);

    bool dump();

private:
    MemoryManager mm_;
    std::vector<File> files_;
};

#endif //FILE_SYSTEM_H
