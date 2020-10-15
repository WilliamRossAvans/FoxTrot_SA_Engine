#pragma once

#include "PhysicsBody.h"

/// @brief 
/// Interface facade for all physics actions
#if(EXPORT)
class DLLEXPORT IPhysicsFacade
#else
class IPhysicsFacade
#endif
{
public:
	IPhysicsFacade() {};
	virtual ~IPhysicsFacade() {};

	virtual void addStaticObject(const PhysicsBody* object) = 0;
	virtual void addNonStaticObject(PhysicsBody* object) = 0;

	virtual PhysicsBody* getPhysicsObject(const int objectId) = 0;

	virtual void MoveLeft(const int objectId) = 0;
	virtual void MoveRight(const int objectId) = 0;
	virtual void Jump(const int objectId) = 0;
	virtual void JumpLeft(const int objectId) = 0;
	virtual void JumpRight(const int objectId) = 0;

	virtual void update() = 0;
private:

};



