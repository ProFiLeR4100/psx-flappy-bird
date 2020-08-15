#include "GameObjectList.h"

GameObjectList::GameObjectList() : items(), size(0) {
}

bool GameObjectList::isEmpty() const {
	return size == 0;
}

int GameObjectList::getLength() const {
	return size;
}

bool GameObjectList::insert(int index, GameObject* newItem) {
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

GameObject* GameObjectList::retrieve(int index) {
	bool success = (index >= 0) && (index <= size);
	GameObject* go = 0;

	if (success) {
		go = items[index];
	}

	return go;
}