#include "SceneObject.h"

SceneObject::SceneObject() :
	angle(0.0f)
{
}

SceneObject::~SceneObject(void)
{
}

void SceneObject::Initialize()
{
}

void SceneObject::OnUpdate(float deltaTime)
{
}

void SceneObject::OnCollision(b2Fixture *ourFixture, SceneObject *other)
{
}

void SceneObject::OnDraw(Tiny2D::Texture& renderTarget)
{
}

void SceneObject::InitBody(b2World *world)
{
	b2BodyDef def;
	//Let our subclass add whatever they want
	PopulateBodyDefinition(def);
	body = world->CreateBody(&def);
	//Let our subclass know
	OnBodyInitialized();
}
//Default body values
void SceneObject::PopulateBodyDefinition(b2BodyDef &def)
{
	def.userData = this;
	def.position = position.ToBox2DVec();
	def.angle = angle;
}

void SceneObject::OnBodyInitialized()
{
	//Callback function for children to inherit
}