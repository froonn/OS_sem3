#include "pch.h"
#include "../MemoryManager/MemoryManager.cpp"

TEST(ListTests, ListAddingAndRemovalTest) {
	printf("\n%s\n", "Output for list tests:");

	List* list = (List*) malloc(sizeof(List));
	int* someValue = (int*)malloc(sizeof(int));

	list->InitializeList(1, someValue);
	list->AddListItem(list, someValue);
	list->AddListItem(list, someValue);
	list->AddListItem(list, someValue);
	list->AddListItem(list, someValue);
	list->AddListItem(list, someValue);

	list->PrintListItemsIndexies(list);

	list->AddListItem(list, someValue);
	list->AddListItem(list, someValue);
	list->AddListItem(list, someValue);
	list->AddListItem(list, someValue);
	list->AddListItem(list, someValue);
	list->AddListItem(list, someValue);

	list->PrintListItemsIndexies(list);

	void* item = list->FindListItemContentById(list, 10);
	EXPECT_EQ((int*)item, someValue);

	item = list->FindListItemContentById(list, 5);
	EXPECT_EQ((int*) item, someValue);

	item = list->FindListItemContentById(list, 7);
	EXPECT_EQ((int*)item, someValue);

	item = list->FindListItemContentById(list, 13);
	EXPECT_EQ(item, nullptr);

	list->RemoveListItemById(&list, 5);
	list->PrintListItemsIndexies(list);
	item = list->FindListItemContentById(list, 5);
	EXPECT_EQ(item, nullptr);

	list->RemoveListItemById(&list, 12);
	list->PrintListItemsIndexies(list);
	item = list->FindListItemContentById(list, 12);

	EXPECT_EQ(item, nullptr);

	list->RemoveListItemById(&list, 1);
	list->PrintListItemsIndexies(list);
	item = list->FindListItemContentById(list, 1);

	EXPECT_EQ(item, nullptr);

	printf("\n");
}