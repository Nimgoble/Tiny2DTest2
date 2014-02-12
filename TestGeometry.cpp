#include "TestGeometry.h"
#include <math.h>

TestGeometry::TestGeometry() :
	size(32.0f, 32.0f),
	singleBlockSize(32.0f, 32.0f),
	repeatAmount(0),
	repeatDirection(RepeatDirection::rdNone)
{
}

TestGeometry::TestGeometry(const T2DTVec2D& position, int repeatAmount, RepeatDirection repeatDirection)
{	
	this->position = position;
	this->repeatDirection = (repeatAmount == 0) ? RepeatDirection::rdNone : repeatDirection;
	this->repeatAmount = (repeatDirection == RepeatDirection::rdNone) ? 0 : repeatAmount;
	size = singleBlockSize = T2DTVec2D(32.0f, 32.0f);
	if(repeatDirection != RepeatDirection::rdNone)
	{
		float& axis = (repeatDirection == RepeatDirection::rdHorizontally) ? size.x : size.y;
		axis *= (repeatAmount + 1);
		//adjust size
		/*if(repeatDirection == RepeatDirection::rdHorizontally)
			size.x *= (repeatAmount + 1);
		else
			size.y *= (repeatAmount + 1);*/

		//calculate draw positions
		T2DTVec2D firstDrawPosition;
		T2DTVec2D stepVec;
		if(repeatDirection == RepeatDirection::rdHorizontally)
		{
			firstDrawPosition = T2DTVec2D(position.x - ((size.x / 2.0f) - (singleBlockSize.x / 2.0f)), position.y);
			stepVec.x = singleBlockSize.x;
		}
		else
		{
			firstDrawPosition = T2DTVec2D(position.x, position.y - (size.y / 2.0f) - (singleBlockSize.y / 2.0f));
			stepVec.y = singleBlockSize.y;
		}
		
		drawPositions.push_back(firstDrawPosition);
		for(int i = 1; i <= repeatAmount; ++i)
		{
			T2DTVec2D newDrawPosition = firstDrawPosition;
			newDrawPosition += (stepVec * i);
			drawPositions.push_back(newDrawPosition);
		}
	}
	else
		drawPositions.push_back(position);
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

	/*if(repeatDirection == RepeatDirection::rdHorizontally)
		b2size.x *= repeatAmount;
	else if(repeatDirection == RepeatDirection::rdVertically)
		b2size.y *= repeatAmount;*/

	boundingBox.SetAsBox(b2size.x / 2.0f, b2size.y / 2.0f); //32 x 32 pixels
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boundingBox;
	fixtureDef.density = 1.0f;
	body->CreateFixture(&fixtureDef);
}

void TestGeometry::OnDraw(Tiny2D::Texture& renderTarget)
{
	for(int i = 0; i < drawPositions.size(); ++i)
		blockTexture.DrawCentered(drawPositions[i], angle);
}