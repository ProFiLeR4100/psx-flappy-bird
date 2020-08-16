#include "GameObjectList.h"
#include <STDIO.H>

GameObjectList::GameObjectList() : items(), size(0) {
}

bool GameObjectList::isEmpty() const {
	return size == 0;
}

int GameObjectList::getLength() const {
	return size;
}

bool GameObjectList::insert(int index, GameObject *newItem) {
	bool success = (index >= 0)
				   && (index <= size)
				   && (size < MAX_LIST);
	if (success) {
		for (int pos = size; pos >= index; --pos) {
			items[pos + 1] = items[pos];
		}

		items[index] = newItem;
		++size;
	}

	return success;
}

bool GameObjectList::insertAtLayer(GameObject *newItem) {
	bool success = (size < MAX_LIST);
	printf("\n==============================\n Starting inserting item with layer %d\n Size:%d\n\n Items: {", newItem->layer, size);
	for (int i = 0; i < size; i++) {
		if(i>0) {
			printf(", ");
		}

		printf("%d", items[i]->layer);
	}

	printf("}\n");


	if (success) {
		int index = 0;
		if (size > 0) {
			for (int pos = size; items[pos]->layer > newItem->layer; pos--) {
				printf(" \tMoving item from %d to %d\n", pos, pos + 1);

				items[pos + 1] = items[pos];
				index = pos;

				if (pos == 0) {
					break;
				}
			}
		}

		printf(" \t\tInserting to: %d Layer: %d\n", index, newItem->layer);
		items[index] = newItem;
		printf(" \t\tInserted to: %d Layer: %d\n", index, newItem->layer);
		size++;
	}

	return success;
}

bool GameObjectList::remove(int index) {
	bool success = (index >= 0) && (index <= size);
	if (success) {
		for (int fromPosition = index + 1; fromPosition <= size; ++fromPosition) {
			items[fromPosition - 1] = items[fromPosition];
		}

		--size;
	}
	return success;
}

GameObject *GameObjectList::retrieve(int index) {
	bool success = (index >= 0) && (index <= size);
	GameObject *go = 0;

	if (success) {
		go = items[index];
	}

	return go;
}