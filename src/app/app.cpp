#include "app/app.hpp"

//#include <GL/glew.h>
#include <SDL.h>

#include <cassert>
#include <iostream>

using namespace std;
using namespace anjing;

int App::StartApplication(App* app, int width, int height, int fps, std::string title)
{
	assert(app);

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0){
		std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
		return -1;
	}

	/*GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		MessageBox(0, L"glewInit Failed.", 0, 0);
	}*/

	app->Init();

	return 0;
}

int App::Init()
{


	return 0;
}

void App::Clean()
{

}