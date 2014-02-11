#include "TestScene.h"
#include "Player.h"
#include "TestGeometry.h"

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}

void TestScene::InitializeScene()
{
	CreateTestObjects();
}

void TestScene::CreateTestObjects()
{
	//Player
	Player *player = new Player();
	player->Initialize();
	player->InitBody(world);
	player->SetPosition(T2DTVec2D(50.0f, 400.0f));
	sceneObjects.push_back(player);

	//Ground
	for(int i = 0; i < 15; ++i)
	{
		TestGeometry *ground = new TestGeometry(T2DTVec2D(16 + (i * 32.0f), 480.0f), T2DTVec2D(32.0f, 32.0f));
		ground->Initialize();
		ground->InitBody(world);
		sceneObjects.push_back(ground);
	}

	for(int i = 0; i < 15; ++i)
	{
		TestGeometry *ground = new TestGeometry(T2DTVec2D(0.0f, 16 + (i * 32.0f)), T2DTVec2D(32.0f, 32.0f));
		ground->Initialize();
		ground->InitBody(world);
		sceneObjects.push_back(ground);
	}
}