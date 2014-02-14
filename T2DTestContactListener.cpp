#include "T2DTestContactListener.h"
#include "SceneObject.h"

T2DTestContactListener::T2DTestContactListener(void)
{
}


T2DTestContactListener::~T2DTestContactListener(void)
{
}

void T2DTestContactListener::BeginContact(b2Contact *contact)
{
	SceneObject *objectA = nullptr, *objectB = nullptr;
	//Get the fixtures
	b2Fixture *fixtureA = contact->GetFixtureA();
	b2Fixture *fixtureB = contact->GetFixtureB();

	//Set the touching member of each fixture
	void *userDataA = fixtureA->GetUserData();
	if(userDataA)
	{
		bool *touching = static_cast<bool *>(userDataA);
		if(touching)
			*touching = true;
	}

	void *userDataB = fixtureB->GetUserData();
	if(userDataB)
	{
		bool *touching = static_cast<bool *>(userDataB);
		if(touching)
			*touching = true;
	}

	//Notify each SceneObject of the collision
	void *bodyUserDataA = fixtureA->GetBody()->GetUserData();
	if(userDataA)
	{
		objectA = static_cast<SceneObject *>(bodyUserDataA );
		if(objectA != nullptr)
			objectA->OnCollision(contact->GetFixtureA(), objectB);
	}

	void *bodyUserDataB = fixtureB->GetBody()->GetUserData();
	if(fixtureB)
	{
		objectB = static_cast<SceneObject *>(bodyUserDataB);
		if(objectB != nullptr)
			objectB->OnCollision(contact->GetFixtureB(), objectA);
	}
}

void T2DTestContactListener::EndContact(b2Contact *contact)
{
	b2Fixture *fixtureA = contact->GetFixtureA();
	b2Fixture *fixtureB = contact->GetFixtureB();

	//Set the touching member of each fixture
	void *userDataA = fixtureA->GetUserData();
	if(userDataA)
	{
		bool *touching = static_cast<bool *>(userDataA);
		if(touching)
			*touching = false;
	}

	void *userDataB = fixtureB->GetUserData();
	if(userDataB)
	{
		bool *touching = static_cast<bool *>(userDataB);
		if(touching)
			*touching = false;
	}
}