#include "Object.h"
#include "glpch.h"
namespace Glitch {
/// @brief 
	Object::Object()
	{
	}

	/// @brief 
	/// @param id 
	/// @param xPos 
	/// @param yPos 
	/// @param height 
	/// @param width 
	Object::Object(int id, int xPos, int yPos, int height, int width)
	{
		spriteID = id;
		positionX = xPos;
		positionY = yPos;
		this->height = height;
		this->width = width;
	}

	/// @brief 
	Object::~Object()
	{
	}

	void Object::setName(string n) { this->name = n; }
	string Object::getName() { return name; }

	void Object::setSpriteID(int s) { this->spriteID = s; }
	int Object::getSpriteID() { return spriteID; }

	void Object::setPositionX(int x) { this->positionX = x; }
	int Object::getPositionX() { return positionX; }

	void Object::setPositionY(int y) { this->positionY = y; }
	int Object::getPositionY() { return positionY; }

	void Object::setRotation(int r) { this->rotation = r; }
	int Object::getRotation() { return rotation; }

	void Object::setScale(int s) { this->scale = s; }
	int Object::getScale() { return scale; }

	void Object::setDirection(int d) { this->direction = d; }
	int Object::getDirection() { return direction; }

	void Object::setHeight(int h) { this->height = h; }
	int Object::getHeight() { return height; }

	void Object::setWidth(int w) { this->width = w; }
	int Object::getWidth() { return width; }

	void Object::setStatic(bool s) { this->staticObject = s; }
	bool Object::getStatic() { return staticObject; }

	bool Object::getChanged() { return changed; }
}
