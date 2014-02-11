#pragma once
#include "ThirdParty\Tiny2D\Include\Tiny2D.h"
#include "TestScene.h"

using namespace Tiny2D;

class Tiny2DTestApp : public App::Callbacks
{
public:
	Tiny2DTestApp(void);
	~Tiny2DTestApp(void);

	virtual bool OnStartup(int numArguments, const char** arguments, const App::SystemInfo& systemInfo, App::StartupParams& outParams);
	virtual bool OnInit();
	virtual void OnUpdate(float deltaTime);
	virtual void OnDraw(Texture& renderTarget);

private:
	TestScene testScene;
};

