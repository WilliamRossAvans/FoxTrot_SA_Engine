#pragma once
#include "stdafx.h"
#include "../Engine/Engine.h"
#include "../Engine/Events/AppTickEvent30.h"
#include "../Engine/Events/AppTickEvent60.h"

#include "Events/Window/WindowCloseEvent.h"

// TODO engine.h & engine.cpp

// Doxygen
// Cntrl + / above function or class to generate Doxygen
// https://devblogs.microsoft.com/cppblog/doxygen-and-xml-doc-comment-support/
// Installing
// https://computingonplains.wordpress.com/doxygen-and-visual-studio/

Engine engine;

class Player : public Object {
private:
	bool canJump = false;
public:
	Player() : Object(2) {
		this->setName("person");
		this->setHeight(80);
		this->setWidth(80);
		this->setPositionX(100);
		this->setPositionY(80);

		this->setSpeed(50);
		this->setJumpHeight(400);
		this->setDensity(100);
		this->setFriction(0);
		this->setRestitution(0);
		this->setStatic(false);

		this->setRotatable(true);

		EventSingleton::get_instance().setEventCallback<OnCollisionBeginEvent>(BIND_EVENT_FN(Player::onCollisionBeginEvent));
		EventSingleton::get_instance().setEventCallback<OnCollisionEndEvent>(BIND_EVENT_FN(Player::onCollisionEndEvent));
		EventSingleton::get_instance().setEventCallback<KeyPressedEvent>(BIND_EVENT_FN(Player::onKeyPressed));
	}

	/// @brief 
	/// Handles when an collision event begins, when the direction of the collision happend on the bottom side of the player object, set can jump true
	void onCollisionBeginEvent(Event& event) {
		auto collisionEvent = static_cast<OnCollisionBeginEvent&>(event);
		if (collisionEvent.GetObjectOneId() != this->getSpriteID() && collisionEvent.GetObjectTwoId() != this->getSpriteID()) return;

		auto map = collisionEvent.getDirectionMap();
		auto collidedDirection = map[this->getSpriteID()];
		if (collidedDirection == Direction::DOWN) {
			this->canJump = true;
		}
	}

	/// @brief 
	/// Handles when an collision event ends, when the direction of the collision happend on the bottom side of the player object, set can jump false
	void onCollisionEndEvent(Event& event) {
		auto collisionEvent = static_cast<OnCollisionEndEvent&>(event);
		if (collisionEvent.GetObjectOneId() != this->getSpriteID() && collisionEvent.GetObjectTwoId() != this->getSpriteID()) return;

		auto map = collisionEvent.getDirectionMap();
		auto collidedDirection = map[this->getSpriteID()];
		if (collidedDirection == Direction::DOWN) {
			this->canJump = false;
		}
	}

	/// @brief 
	/// Handles when an key pressed event happend, Player can move right, left and jump
	void onKeyPressed(Event& event) {
		auto keyPressedEvent = static_cast<KeyPressedEvent&>(event);

		switch (keyPressedEvent.GetKeyCode())
		{
		case KeyCode::KEY_A:
			EventSingleton::get_instance().dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::LEFT, this->getSpriteID()));
			break;
		case KeyCode::KEY_D:
			EventSingleton::get_instance().dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::RIGHT, this->getSpriteID()));
			break;
		case KeyCode::KEY_SPACE:
			if (canJump) {
				EventSingleton::get_instance().dispatchEvent<ActionEvent>((Event&)ActionEvent(Direction::UP, this->getSpriteID()));
			}
			break;
		default:
			break;
		}
	}
};

void sceneTestSetup()
{
	SpriteObject so0(1, 16, 16, 1, "../Assets/Sprites/World/LIGHT TILE WITHOUT TOP.png");
	SpriteObject so1(100, 37, 50, 1, "../Assets/Sprites/Character/adventure.png");
	SpriteObject so2(101, 37, 50, 4, "../Assets/Sprites/Character/adventure_air_attack1.png");
	SpriteObject so3(102, 37, 50, 6, "../Assets/Sprites/Character/adventure_run.png");
	SpriteObject so4(103, 37, 50, 2, "../Assets/Sprites/Character/adventure_slide.png");
	SpriteObject so5(104, 37, 50, 2, "../Assets/Sprites/Character/adventure_fall.png");


	engine.loadSprite(so0);

	engine.loadSprite(so1);
	engine.loadSprite(so2);
	engine.loadSprite(so3);
	engine.loadSprite(so4); 
	engine.loadSprite(so5);

	Scene* testScene = new Scene(3);

	Object* object = new Object(1);
	object->setName("person1");
	object->setHeight(100);
	object->setWidth(100);
	object->setPositionX(30);
	object->setPositionY(300);
	object->setSpeed(100);
	object->setJumpHeight(400);
	object->setDensity(1000000);
	object->setFriction(0);
	object->setRestitution(0);
	object->setStatic(false);
	engine.createObject(3, object);

	Object* object2 = new Player();
	object2->setStatic(false);
	object2->registerSprite("default", so1);
	object2->registerSprite("air_attack", so2);
	object2->registerSprite("run", so3);
	object2->registerSprite("slide", so4);
	object2->registerSprite("air_fall", so5);
	object2->changeToState("air_fall");
	engine.createObject(3, object2);

	Object* staticGround = new Object(101);
	staticGround->setScalable(true);
	staticGround->setWidth(500); // width
	staticGround->setHeight(10);// height
	staticGround->setPositionX(20); // x 20 left down
	staticGround->setPositionY(300);// y 300 left down
	staticGround->setStatic(true);
	staticGround->registerSprite("default", so0);
	staticGround->changeToState("default");
	testScene->addNewObjectToLayer(1, staticGround);


	engine.setCurrentScene(3);
	engine.physicsEngine.registerObjectInCurrentVectorWithPhysicsEngine();
	
	engine.insertScene(new Scene(4));

	Object* staticGround2 = new Object(102);
	staticGround2->setWidth(100); // width
	staticGround2->setHeight(80);// height
	staticGround2->setPositionX(220); // x 20 left down
	staticGround2->setPositionY(290);// y 300 left down
	staticGround2->setStatic(true);
	staticGround2->setFriction(0);
	engine.createObject(3, staticGround2);

	engine.insertScene(testScene);
	engine.setCurrentScene(3);
	engine.startTickThreads();
}

int main() {
	sceneTestSetup();

	bool gameRunning = true;
	while (gameRunning)
	{
		AppTickEvent60 appTick;
		AppTickEvent30 appTick30;

		engine.pollEvents();
		EventSingleton::get_instance().dispatchEvent<AppTickEvent60>(appTick);
		EventSingleton::get_instance().dispatchEvent<AppTickEvent30>(appTick30);

		this_thread::sleep_for(chrono::milliseconds(10));
	}
	engine.stopTickThreads();

	return 0;
}
