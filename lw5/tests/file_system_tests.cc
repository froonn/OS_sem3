//
// Created by froonn on 16/12/24.
//

#include <gtest/gtest.h>
#include "file_system.h"

TEST(FileSystem, CreateFile) {
    FileSystem fs(32);
    EXPECT_TRUE(fs.createFile("file1"));
    EXPECT_TRUE(fs.createFile("file2", "content"));
    EXPECT_TRUE(fs.createFile("file3", 10));

}