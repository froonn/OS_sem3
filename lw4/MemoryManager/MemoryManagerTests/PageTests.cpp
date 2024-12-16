#include "pch.h"
#include "../MemoryManager/MemoryManager.cpp"

TEST(PageTests, MemoryAllocationNormalSituationTest) {

	Page* page = (Page*)malloc(sizeof(Page));
	page->Initialize(8, 1, 1);

	int* i = (int*)malloc(sizeof(int));

	if (i != NULL)
	{
		*i = 5;
	}

	Location* contentLocation = page->WriteData(i, sizeof(int));
	EXPECT_FALSE(contentLocation == NULL);

	void* writtenData = malloc(sizeof(contentLocation));
	page->ReadData(contentLocation->Offset, contentLocation->Size, writtenData);
	
	EXPECT_EQ(*(int*)writtenData, *i);

	page->Free();
	free(page);
	free(i);
}

TEST(PageTests, MemoryAllocationNotEnoughMemoryTest)
{
	printf("\n");
	Page* page = (Page*)malloc(sizeof(Page));
	page->Initialize(8, 1, 1);

	int* i = (int*)malloc(sizeof(int));

	if (i != NULL)
	{
		*i = 5;
	}

	Location* contentAddres = page->WriteData(i, sizeof(int));
	page->WriteData(i, sizeof(int));
	Location* contentOutside = page->WriteData(i, sizeof(int));
	EXPECT_TRUE(contentOutside == NULL);

	void* writtenData = malloc(sizeof(contentAddres));
	page->ReadData(contentAddres->Offset, contentAddres->Size, writtenData);

	EXPECT_EQ(*(int*)writtenData, *i);

	page->Free();
	free(page);
	free(i);
	printf("\n");
}

TEST(PageTests, MemoryAllocationLargePageTests)
{
	Page* page = (Page*)malloc(sizeof(Page));
	page->Initialize(1024, 1, 1);

	int* i = (int*)malloc(sizeof(int));

	if (i != NULL)
	{
		*i = 5;
	}

	void* contentAddress = page->WriteData(i, sizeof(int));

	for (int j = 0; j < 1024 / 4 - 1; j++)
	{
		page->WriteData(i, sizeof(int));
	}

	page->Free();
	free(page);
	free(i);
}

TEST(PageTests, EndDeletionTest)
{
	printf("\n");
	Page* page = (Page*)malloc(sizeof(Page));
	page->Initialize(8, 1, 1);

	int* i = (int*)malloc(sizeof(int));

	if (i != NULL)
	{
		*i = 5;
	}

	Location* contentAddres = page->WriteData(i, sizeof(int));
	page->WriteData(i, sizeof(int));
	page->PrintPageReport();
	page->FreePart(4, 4);
	page->PrintPageReport();
	Location* contentOutside = page->WriteData(i, sizeof(int));
	EXPECT_FALSE(contentOutside == NULL);

	void* writtenData = malloc(sizeof(contentAddres));
	page->ReadData(contentAddres->Offset, contentAddres->Size, writtenData);

	EXPECT_EQ(*(int*)writtenData, *i);

	page->Free();
	free(page);
	free(i);
	printf("\n");
}

TEST(PageTests, MiddleDeletionTest)
{
	printf("\n");
	Page* page = (Page*)malloc(sizeof(Page));
	page->Initialize(12, 1, 1);

	int* i = (int*)malloc(sizeof(int));

	if (i != NULL)
	{
		*i = 5;
	}

	Location* contentAddres = page->WriteData(i, sizeof(int));
	page->WriteData(i, sizeof(int));
	page->WriteData(i, sizeof(int));

	page->PrintPageReport();
	page->FreePart(4, 4);
	page->PrintPageReport();
	printf("%s %i \n", "New offset position: ", page->Offset);

	Location* contentOutside = page->WriteData(i, sizeof(int));
	EXPECT_FALSE(contentOutside == NULL);

	void* writtenData = malloc(sizeof(contentAddres));

	page->ReadData(contentAddres->Offset, contentAddres->Size, writtenData);
	EXPECT_EQ(*(int*)writtenData, *i);

	page->ReadData(4, contentAddres->Size, writtenData);
	EXPECT_EQ(*(int*)writtenData, *i);

	page->ReadData(8, contentAddres->Size, writtenData);
	EXPECT_EQ(*(int*)writtenData, *i);

	page->Free();
	free(page);
	free(i);
	printf("\n");
}

TEST(PageTests, StartDeletionTest3)
{
	printf("\n");
	Page* page = (Page*)malloc(sizeof(Page));
	page->Initialize(12, 1, 1);

	int* i = (int*)malloc(sizeof(int));

	if (i != NULL)
	{
		*i = 5;
	}

	Location* contentAddres = page->WriteData(i, sizeof(int));
	page->WriteData(i, sizeof(int));
	page->WriteData(i, sizeof(int));

	page->PrintPageReport();
	page->FreePart(0, 4);
	page->PrintPageReport();
	printf("%s %i \n", "New offset position: ", page->Offset);

	Location* contentOutside = page->WriteData(i, sizeof(int));
	EXPECT_FALSE(contentOutside == NULL);

	void* writtenData = malloc(sizeof(contentAddres));

	page->ReadData(contentAddres->Offset, contentAddres->Size, writtenData);
	EXPECT_EQ(*(int*)writtenData, *i);

	page->ReadData(4, contentAddres->Size, writtenData);
	EXPECT_EQ(*(int*)writtenData, *i);

	page->ReadData(8, contentAddres->Size, writtenData);
	EXPECT_EQ(*(int*)writtenData, *i);

	page->Free();
	free(page);
	free(i);
	printf("\n");
}