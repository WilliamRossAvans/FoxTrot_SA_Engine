#include "SVIEngine.h"

SVIEngine::SVIEngine()
{
}

SVIEngine::~SVIEngine()
{
}

void SVIEngine::load(const char* filename)
{
	sviEngine->load(filename);
}

void SVIEngine::play()
{
	sviEngine->play();
}

void SVIEngine::testLoopVideo(int x, int y)
{
	sviEngine->testLoopVideo(x,y);
}

void SVIEngine::input()
{
	sviEngine->input();
}
