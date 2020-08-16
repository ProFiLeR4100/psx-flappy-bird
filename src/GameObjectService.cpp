#include "GameObjectService.h"

GameObjectList GameObjectService::gameObjectList;

void GameObjectService::draw() {
	int size = gameObjectList.getLength();

	for (int index = 0; index < size; index++) {
		GameObject* go = gameObjectList.retrieve(index);
		go->draw();
	}
}

void GameObjectService::update(float fDeltaTime) {
	int size = gameObjectList.getLength();

	for (int index = 0; index < size; index++) {
		GameObject* go = gameObjectList.retrieve(index);
		go->update(fDeltaTime);
	}
}

void GameObjectService::updatePhysics(float fDeltaTime) {
	int size = gameObjectList.getLength();

	for (int index = 0; index < size; index++) {
		GameObject* go = gameObjectList.retrieve(index);
		go->updatePhysics(fDeltaTime);
	}
}

bool GameObjectService::enableGameObject(GameObject* gameObject) {
	return gameObjectList.insertAtLayer(gameObject);
}

bool GameObjectService::disableGameObject(GameObject* gameObject) {
	bool success = false;
	// todo: implement
	return success;

}
