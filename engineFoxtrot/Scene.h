#pragma once
#include <vector>
#include <string>
#include <memory>
#include <iostream>

#include "Object.h"
#include "Debug.h"
#include "ErrorCodes.h"
#include "GeneralHelperFunctions.cpp"

using namespace std;

#include <vector>
#include "Object.h"

class Scene 
{
public:
	Scene(int);
    ~Scene();

	void addNewObject(int id, int xPos, int yPos, int height, int width);
	Object * getObject(int ObjectID);

	int getSceneID() { return sceneID; }
	vector<Object*> getPtrToObjects() { return objects; }

private:
	int sceneID = 0;
	vector<Object*> objects;

};
