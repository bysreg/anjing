#include "app/app.hpp"

#include <GL/glew.h>
#include <SDL.h>

#include <cassert>
#include <iostream>

using namespace std;
using namespace anjing;

int App::StartApplication(App* app, int width, int height, int fps, const string& title)
{
	assert(app);

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0){
		cerr << "SDL_Init error: " << SDL_GetError() << endl;
		return -1;
	}

	string win_title = title + " (" + std::to_string(fps) + " fps) ";
	SDL_Window *window = SDL_CreateWindow(win_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (window == NULL)
	{
		cerr << "SDL_CreateWindow error : " << SDL_GetError() << endl;
		return -2;
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	if (glContext == NULL)
	{
		cerr << "SDL_GL_CreateContext failed" << endl;
		return -3;
	}

	GLenum glewErr = glewInit();
	if (glewErr != GLEW_OK)
	{
		cerr << "glewInit failed : " << glewGetErrorString(glewErr) << endl;
		return -4;
	}

	if (app->Init() == 0)
	{
		cout << "application initialized" << endl;
	}

	return 0;
}

int App::Init()
{
	return 0;
}

void App::Clean()
{

}