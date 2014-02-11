#pragma once

#include "SceneObject.h"
#include "T2DTVec2D.h"

//This will be a building block for our world
//Currently using the dev texture 'testTile.png'
class TestGeometry : public SceneObject
{
public:
	TestGeometry();
	TestGeometry(const T2DTVec2D& position, const T2DTVec2D& size);
	~TestGeometry();

	virtual void Initialize();
	virtual void PopulateBodyDefinition(b2BodyDef &def);
	virtual void OnBodyInitialized();
	virtual void OnDraw(Tiny2D::Texture& renderTarget);

private:
	Tiny2D::Texture blockTexture;
	T2DTVec2D size;
};