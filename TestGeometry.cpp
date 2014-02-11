#include "TestGeometry.h"
#include <math.h>

TestGeometry::TestGeometry()
{
}

TestGeometry::TestGeometry(const T2DTVec2D& position, const T2DTVec2D& size)
{	
	this->position = position;
	this->size = size;
}

TestGeometry::~TestGeometry()
{
}

void TestGeometry::Initialize()
{
	blockTexture.Create("testTile.png", true);
}

void TestGeometry::PopulateBodyDefinition(b2BodyDef &def)
{
	def.type = b2BodyType::b2_staticBody;
	def.fixedRotation = true;
	SceneObject::PopulateBodyDefinition(def);
}

void TestGeometry::OnBodyInitialized()
{
	//Create the shape fixture.
	b2PolygonShape boundingBox;
	b2Vec2 b2size = size.ToBox2DVec();
	boundingBox.SetAsBox(b2size.x / 2.0f, b2size.y / 2.0f); //32 x 32 pixels
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boundingBox;
	fixtureDef.density = 1.0f;
	body->CreateFixture(&fixtureDef);
}

void TestGeometry::OnDraw(Tiny2D::Texture& renderTarget)
{
	float wholeX = (float((int)(size.x / blockTexture.GetRealWidth())));
	float wholeY = (float((int)(size.y / blockTexture.GetRealHeight())));
	float remainderX = fmod(size.x, (float)blockTexture.GetRealWidth());
	float remainderY = fmod(size.y, (float)blockTexture.GetRealHeight());

	blockTexture.DrawCentered(position, angle);
}