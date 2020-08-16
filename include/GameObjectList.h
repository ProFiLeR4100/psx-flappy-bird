#include "GameObject.h"

#ifndef GAME_OBJECT_LIST_H
#define GAME_OBJECT_LIST_H

struct GameObjectList {
	GameObjectList();
	bool isEmpty() const;
	int getLength() const;
	bool insert(int index, GameObject* newItem);
	bool insertAtLayer(GameObject* newItem);
	GameObject* retrieve(int index);
	bool remove(int index);
private:
	static const int MAX_LIST = 10;
	GameObject* items[MAX_LIST];
	int size;
};
#endif // GAME_OBJECT_LIST_H