#pragma once
#include "Scene.h"

class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();

	virtual void InitializeScene();

private:
	void CreateTestObjects();
};