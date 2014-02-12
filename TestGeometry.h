#pragma once

#include "SceneObject.h"
#include "T2DTVec2D.h"

//This will be a building block for our world
//Currently using the dev texture 'testTile.png'
class TestGeometry : public SceneObject
{
public:
	enum RepeatDirection
	{
		rdNone = 0,
		rdHorizontally,
		rdVertically
	};

	TestGeometry();
	TestGeometry(const T2DTVec2D& position, int repeatAmount = 0, RepeatDirection = rdNone);
	~TestGeometry();

	virtual void Initialize();
	virtual void PopulateBodyDefinition(b2BodyDef &def);
	virtual void OnBodyInitialized();
	virtual void OnDraw(Tiny2D::Texture& renderTarget);

private:
	Tiny2D::Texture blockTexture;
	T2DTVec2D size;
	std::vector<T2DTVec2D> drawPositions;
	T2DTVec2D singleBlockSize;
	int repeatAmount;
	RepeatDirection repeatDirection;
};