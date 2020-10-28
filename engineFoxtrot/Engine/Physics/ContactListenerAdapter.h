#pragma once

class ContactListenerAdapter : public b2ContactListener
{
private:
	PhysicsFacade* facade;
public:
	ContactListenerAdapter(PhysicsFacade* _facade) : facade(_facade) { }
protected:
	void BeginContact(b2Contact* contact) override {
		b2Fixture* fixtureOne = contact->GetFixtureA();
		b2Fixture* fixtureTwo = contact->GetFixtureB();
		auto result = facade->getObjectsByFixture(fixtureOne, fixtureTwo);
		if (result.object1 != nullptr && result.object2 != nullptr) {
			std::cout << "BEGIN === Ob1: " << result.object1->getSpriteID() << "  Obj2: " << result.object2->getSpriteID() << std::endl;
			EventSingleton::get_instance().dispatchEvent<OnCollisionBeginEvent>((Event&)OnCollisionBeginEvent(result.object1->getSpriteID(), result.object2->getSpriteID()));
		}
	}

	void EndContact(b2Contact* contact) override {
		b2Fixture* fixtureOne = contact->GetFixtureA();
		b2Fixture* fixtureTwo = contact->GetFixtureB();

		b2WorldManifold worldManifold;
		auto manifold = contact->GetManifold();
		worldManifold.Initialize(manifold, fixtureOne->GetBody()->GetTransform(), fixtureOne->GetShape()->m_radius, fixtureTwo->GetBody()->GetTransform(), fixtureTwo->GetShape()->m_radius);
		worldManifold.points;
		// TODO Calculate from what direction collision happend


		auto result = facade->getObjectsByFixture(fixtureOne, fixtureTwo);
		if (result.object1 != nullptr && result.object2 != nullptr) {

			std::cout << "END ==== Ob1: " << result.object1->getSpriteID() << "  Obj2: " << result.object2->getSpriteID() << std::endl;
			EventSingleton::get_instance().dispatchEvent<OnCollisionEndEvent>((Event&)OnCollisionEndEvent(result.object1->getSpriteID(), result.object2->getSpriteID()));
		}
	}
};