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

	void *fixtureA = contact->GetFixtureA()->GetBody()->GetUserData();
	if(fixtureA)
		objectA = static_cast<SceneObject *>(fixtureA);

	void *fixtureB = contact->GetFixtureB()->GetBody()->GetUserData();
	if(fixtureB)
		objectB = static_cast<SceneObject *>(fixtureB);

	if(objectA != nullptr)
		objectA->OnCollision(contact->GetFixtureA(), objectB);

	if(objectB != nullptr)
		objectB->OnCollision(contact->GetFixtureB(), objectA);
}

void T2DTestContactListener::EndContact(b2Contact *contact)
{
}