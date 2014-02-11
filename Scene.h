#pragma once
#include <vector>
#include "T2DTestContactListener.h"
#include "SceneObject.h"
#include "DebugDrawer.h"
#include <Box2D\Box2D.h>

class Scene
{
public:
	Scene();
	~Scene();

	virtual void InitializeScene();

	void OnUpdate(float deltaTime);
	void OnDraw(Tiny2D::Texture& renderTarget);

	void Cleanup();

protected:
	T2DTestContactListener contactListener;
	DebugDrawer debugDrawer;
	typedef std::vector<SceneObject *> SceneObjectList;
	SceneObjectList sceneObjects;

	b2Vec2 gravity;
	b2Vec2 size;
	b2World *world;
};