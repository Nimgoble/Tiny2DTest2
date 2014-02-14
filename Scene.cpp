#include "Scene.h"

Scene::Scene()
{
	gravity = b2Vec2(0.0f, 9.8f);
	world = new b2World(gravity);
	world->SetContactListener(&contactListener);
	world->SetDebugDraw(&debugDrawer);
}

Scene::~Scene()
{
	Cleanup();
}

void Scene::InitializeScene()
{
}

void Scene::OnUpdate(float deltaTime)
{
	//Update our objects
	for(int i = 0; i < sceneObjects.size(); i++)
		sceneObjects[i]->OnUpdate(deltaTime);

	/*for(SceneObject *object : sceneObjects)
		object->Update(deltaTime);*/

	//Shouldn't deltaTime be used here, somewhere?
	world->Step(1.0f / 60.0f, 6, 2);
}

void Scene::OnDraw(Tiny2D::Texture& renderTarget)
{
	renderTarget.BeginDrawing(&Tiny2D::Color::Black);

	for(int i = 0; i < sceneObjects.size(); i++)
		sceneObjects[i]->OnDraw(renderTarget);

	//world->DrawDebugData();

	renderTarget.EndDrawing();
	/*for(SceneObject *object : sceneObjects)
		object->OnDraw(renderTarget);*/
}

void Scene::Cleanup()
{
	for(int i = 0; i < sceneObjects.size(); ++i)
	{
		SceneObject *currentObject = sceneObjects[i];
		if(currentObject == nullptr)
			continue;

		if(world != nullptr)
		{
			b2Body *body = currentObject->GetBody();
			if(body != nullptr)
				world->DestroyBody(body);
		}
		delete currentObject;
		currentObject = nullptr;
	}

	if(world != nullptr)
	{
		delete world;
		world = nullptr;
	}
}
