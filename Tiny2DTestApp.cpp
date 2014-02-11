#include "Tiny2DTestApp.h"
using namespace Tiny2D;

Tiny2DTestApp::Tiny2DTestApp(void)
{
}

Tiny2DTestApp::~Tiny2DTestApp(void)
{
}

bool Tiny2DTestApp::OnStartup(int numArguments, const char** arguments, const App::SystemInfo& systemInfo, App::StartupParams& outParams)
{
	outParams.name = "Tiny2D Test App";
	outParams.virtualHeight = 600;
	outParams.virtualWidth = 800;
	outParams.emulateTouchpadWithMouse = false;
	outParams.rootDataDirs.push_back("Data/");
	outParams.rootDataDirs.push_back("Content/");
	outParams.disableCursor = false;
	return true;
}

bool Tiny2DTestApp::OnInit()
{
	testScene.InitializeScene();
	return true;
}

void Tiny2DTestApp::OnUpdate(float deltaTime)
{
	if (Input::WasKeyPressed(Input::Key_Escape) || Input::WasKeyPressed(Input::Key_Android_Back))
		App::Quit();

	testScene.OnUpdate(deltaTime);
}

void Tiny2DTestApp::OnDraw(Texture& renderTarget)
{
	testScene.OnDraw(renderTarget);
}

DEFINE_APP(Tiny2DTestApp)
