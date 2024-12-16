//
// Created by froonn on 16/12/24.
//

#include "memory_manager.h"
#include <gtest/gtest.h>


TEST(MemoryManager, WriteToFreeMemory) {
    MemoryManager mm(1024);
    int data = 123;
    void *ptr = mm.write(&data, sizeof(data));
    EXPECT_NE(ptr, nullptr);
}

TEST(MemoryManager, WriteToFullMemory) {
    MemoryManager mm(4);
    int data1 = 123;
    int data2 = 456;
    mm.write(&data1, sizeof(data1));
    void *ptr = mm.write(&data2, sizeof(data2));
    EXPECT_EQ(ptr, nullptr);
}

TEST(MemoryManager, FreeMemory) {
    MemoryManager mm(1024);
    int data = 123;
    void *ptr = mm.write(&data, sizeof(data));
    bool result = mm.free(ptr);
    EXPECT_TRUE(result);
}

TEST(MemoryManager, FreeInvalidPointer) {
    MemoryManager mm(1024);
    int data = 123;
    void *ptr = &data;
    bool result = mm.free(ptr);
    EXPECT_FALSE(result);
}

TEST(MemoryManager, Fragmentation) {
    MemoryManager mm(1024);
    int data1 = 123;
    int data2 = 456;
    mm.write(&data1, sizeof(data1));
    mm.write(&data2, sizeof(data2));
    auto [te, tu] = mm.fragmentation();
    EXPECT_EQ(te, 0);
    EXPECT_EQ(tu, sizeof(data1) + sizeof(data2));
}

TEST(MemoryManager, GetSize) {
    MemoryManager mm(1024);
    EXPECT_EQ(mm.getSize(), 1024);
}

TEST(MemoryManager, GetStatus) {
    MemoryManager mm(1024);
    testing::internal::CaptureStdout();
    mm.getStatus();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());
}

TEST(MemoryManager, ForCopy) {
    MemoryManager mm(32);
    mm.getStatus();
    char *ptr = (char *) mm.write("file1", 6);
    mm.getStatus();
    mm.write("1", 2);
    mm.getStatus();
    std::cout << ptr << std::endl;
}