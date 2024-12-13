#include "pch.h"
#include "../MemoryManager/MemoryManager.cpp"
#include <chrono>

std::chrono::time_point<std::chrono::high_resolution_clock> start, end;

class TimerTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
		start = std::chrono::high_resolution_clock::now();
	}

	void TearDown() override
	{
		end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		std::cout << "Time spent for test: " << duration << " microseconds." << std::endl << std::endl;
	}
};

TEST_F(TimerTest, MemoryManagerWritingAndReadingTest1)
{
	char* data = (char*)malloc(11);
	data = "0123456789";
	char* data2 = (char*)malloc(11);

	MemoryManager* memoryManager = (MemoryManager*)malloc(sizeof(MemoryManager));
	memoryManager->Initialize(2, 20, 1);
	List* locations = memoryManager->WriteData(1, data, 11);

	memoryManager->ReadData(1, locations, data2);

	printf("\n");
	printf("%s %i", "The amount of unused memory is: ", memoryManager->CalculateUnusedMemory());
	printf("\n");

	EXPECT_EQ(data[9], data2[9]);

	//memoryManager->RemoveData(1, locations);

	printf("\n");
	printf("%s %i", "The amount of unused memory is: ", memoryManager->CalculateUnusedMemory());
	printf("\n");

	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	locations = memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 6);

	memoryManager->ReadData(1, locations, data2);
	EXPECT_EQ(data[4], data2[4]);

	printf("\n");
	printf("%s %i", "The amount of unused memory is: ", memoryManager->CalculateUnusedMemory());
	printf("\n\n");

	free(memoryManager);
}

TEST_F(TimerTest, MemoryManagerWritingAndReadingTest2)
{
	char* data = (char*)malloc(11);
	data = "0123456789";
	char* data2 = (char*)malloc(11);

	MemoryManager* memoryManager = (MemoryManager*)malloc(sizeof(MemoryManager));
	memoryManager->Initialize(5, 20, 1);
	List* locations = memoryManager->WriteData(1, data, 11);

	memoryManager->ReadData(1, locations, data2);

	printf("\n");
	printf("%s %i", "The amount of unused memory is: ", memoryManager->CalculateUnusedMemory());
	printf("\n");

	EXPECT_EQ(data[9], data2[9]);

	//memoryManager->RemoveData(1, locations);

	printf("\n");
	printf("%s %i", "The amount of unused memory is: ", memoryManager->CalculateUnusedMemory());
	printf("\n");

	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	locations = memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 6);

	memoryManager->ReadData(1, locations, data2);
	EXPECT_EQ(data[4], data2[4]);

	printf("\n");
	printf("%s %i", "The amount of unused memory is: ", memoryManager->CalculateUnusedMemory());
	printf("\n\n");

	free(memoryManager);
}

TEST_F(TimerTest, MemoryManagerWritingAndReadingTest3)
{
	char* data = (char*)malloc(11);
	data = "0123456789";
	char* data2 = (char*)malloc(11);

	MemoryManager* memoryManager = (MemoryManager*)malloc(sizeof(MemoryManager));
	memoryManager->Initialize(8, 20, 1);
	List* locations = memoryManager->WriteData(1, data, 11);

	memoryManager->ReadData(1, locations, data2);

	printf("\n");
	printf("%s %i", "The amount of unused memory is: ", memoryManager->CalculateUnusedMemory());
	printf("\n");

	EXPECT_EQ(data[9], data2[9]);

	//memoryManager->RemoveData(1, locations);

	printf("\n");
	printf("%s %i", "The amount of unused memory is: ", memoryManager->CalculateUnusedMemory());
	printf("\n");

	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	locations = memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 6);

	memoryManager->ReadData(1, locations, data2);
	EXPECT_EQ(data[4], data2[4]);

	printf("\n");
	printf("%s %i", "The amount of unused memory is: ", memoryManager->CalculateUnusedMemory());
	printf("\n\n");

	free(memoryManager);
}

TEST_F(TimerTest, MemoryManagerWritingAndReadingTest4)
{
	char* data = (char*)malloc(11);
	data = "0123456789";
	char* data2 = (char*)malloc(11);

	MemoryManager* memoryManager = (MemoryManager*)malloc(sizeof(MemoryManager));
	memoryManager->Initialize(11, 20, 1);
	List* locations = memoryManager->WriteData(1, data, 11);

	memoryManager->ReadData(1, locations, data2);

	printf("\n");
	printf("%s %i", "The amount of unused memory is: ", memoryManager->CalculateUnusedMemory());
	printf("\n");

	EXPECT_EQ(data[9], data2[9]);

	//memoryManager->RemoveData(1, locations);

	printf("\n");
	printf("%s %i", "The amount of unused memory is: ", memoryManager->CalculateUnusedMemory());
	printf("\n");

	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	locations = memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 6);

	memoryManager->ReadData(1, locations, data2);
	EXPECT_EQ(data[4], data2[4]);

	printf("\n");
	printf("%s %i", "The amount of unused memory is: ", memoryManager->CalculateUnusedMemory());
	printf("\n\n");

	free(memoryManager);
}

TEST_F(TimerTest, MemoryManagerWritingAndReadingTest5)
{
	char* data = (char*)malloc(11);
	data = "0123456789";
	char* data2 = (char*)malloc(11);

	MemoryManager* memoryManager = (MemoryManager*)malloc(sizeof(MemoryManager));
	memoryManager->Initialize(22, 20, 1);
	List* locations = memoryManager->WriteData(1, data, 11);

	memoryManager->ReadData(1, locations, data2);

	printf("\n");
	printf("%s %i", "The amount of unused memory is: ", memoryManager->CalculateUnusedMemory());
	printf("\n");

	EXPECT_EQ(data[9], data2[9]);

	//memoryManager->RemoveData(1, locations);

	printf("\n");
	printf("%s %i", "The amount of unused memory is: ", memoryManager->CalculateUnusedMemory());
	printf("\n");

	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	locations = memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 6);

	memoryManager->ReadData(1, locations, data2);
	EXPECT_EQ(data[4], data2[4]);

	printf("\n");
	printf("%s %i", "The amount of unused memory is: ", memoryManager->CalculateUnusedMemory());
	printf("\n\n");

	free(memoryManager);
}

TEST_F(TimerTest, MemoryManagerWritingAndReadingTest6)
{
	char* data = (char*)malloc(11);
	data = "0123456789";
	char* data2 = (char*)malloc(11);

	MemoryManager* memoryManager = (MemoryManager*)malloc(sizeof(MemoryManager));
	memoryManager->Initialize(50, 20, 1);
	List* locations = memoryManager->WriteData(1, data, 11);

	memoryManager->ReadData(1, locations, data2);

	printf("\n");
	printf("%s %i", "The amount of unused memory is: ", memoryManager->CalculateUnusedMemory());
	printf("\n");

	EXPECT_EQ(data[9], data2[9]);

	//memoryManager->RemoveData(1, locations);

	printf("\n");
	printf("%s %i", "The amount of unused memory is: ", memoryManager->CalculateUnusedMemory());
	printf("\n");

	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	locations = memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 6);

	memoryManager->ReadData(1, locations, data2);
	EXPECT_EQ(data[4], data2[4]);

	printf("\n");
	printf("%s %i", "The amount of unused memory is: ", memoryManager->CalculateUnusedMemory());
	printf("\n\n");

	free(memoryManager);
}

TEST_F(TimerTest, MemoryManagerWritingAndReadingTest7)
{
	char* data = (char*)malloc(11);
	data = "0123456789";
	char* data2 = (char*)malloc(11);

	MemoryManager* memoryManager = (MemoryManager*)malloc(sizeof(MemoryManager));
	memoryManager->Initialize(100, 20, 1);
	List* locations = memoryManager->WriteData(1, data, 11);

	memoryManager->ReadData(1, locations, data2);

	printf("\n");
	printf("%s %i", "The amount of unused memory is: ", memoryManager->CalculateUnusedMemory());
	printf("\n");

	EXPECT_EQ(data[9], data2[9]);

	//memoryManager->RemoveData(1, locations);

	printf("\n");
	printf("%s %i", "The amount of unused memory is: ", memoryManager->CalculateUnusedMemory());
	printf("\n");

	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 11);
	locations = memoryManager->WriteData(1, data, 11);
	memoryManager->WriteData(1, data, 6);

	memoryManager->ReadData(1, locations, data2);
	EXPECT_EQ(data[4], data2[4]);

	printf("\n");
	printf("%s %i", "The amount of unused memory is: ", memoryManager->CalculateUnusedMemory());
	printf("\n\n");

	free(memoryManager);
}