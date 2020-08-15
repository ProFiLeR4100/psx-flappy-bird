#include "GameObject.h"
#include "GameObjectList.h"

#ifndef GAME_OBJECT_SERVICE_H
#define GAME_OBJECT_SERVICE_H

struct GameObjectService {
	static void draw();
	static void update(float fDeltaTime);
	static void updatePhysics(float fDeltaTime);
	static bool enableGameObject(GameObject* gameObject);
	static bool disableGameObject(GameObject* gameObject);

private:
	static GameObjectList gameObjectList;
};

#endif // GAME_OBJECT_SERVICE_H