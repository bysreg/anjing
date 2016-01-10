#include "app/app.hpp"
#include "core/log.hpp"

#include <GL/glew.h>
#include <SDL.h>

#include <cassert>
#include <cstdio>

int anjing::app::App::StartApplication(anjing::app::App* app, int width, int height, int fps, const std::string& title)
{
	assert(app);

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0){
		std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
		return -1;
	}

	std::string win_title = title + " (" + std::to_string(fps) + " fps) ";
	SDL_Window *window = SDL_CreateWindow(win_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (window == NULL)
	{
		std::cerr << "SDL_CreateWindow error : " << SDL_GetError() << std::endl;
		return -2;
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	if (glContext == NULL)
	{
		std::cerr << "SDL_GL_CreateContext failed" << std::endl;
		return -3;
	}

	GLenum glewErr = glewInit();
	if (glewErr != GLEW_OK)
	{
		std::cerr << "glewInit failed : " << glewGetErrorString(glewErr) << std::endl;
		return -4;
	}

	if (app->Init() == 0)
	{
		std::cout << "application initialized" << std::endl;
	}

	return 0;
}

std::FILE* anjing::app::App::GetAssets(std::string filename, std::string mode)
{	
	static std::string assets_dir = "./assets";
	static bool is_init = false;
	
	// try to open it first inside the assets folder in the same directory as the program
	std::string path = (assets_dir + "/" + filename);
	std::FILE* file = std::fopen(path.c_str(), mode.c_str());
	
	// if it fails to open it, try to open the file above the folder hierarchy four times 
	// (this means the program is inside :
	// <project directory>/build/<src or test>/<the startup project>/<build mode (Debug or Release)>/
	if (file == nullptr)
	{
		path = "../../../assets/" + filename;
		file = std::fopen(path.c_str(), mode.c_str());
	}
	
	// still cannot open the file
	if (file == nullptr)
	{
		ANJING_LOGF_E("unable to open file : %s\n", filename.c_str());
	}

	return file;
}

int anjing::app::App::Init()
{
	return 0;
}

void anjing::app::App::Clean()
{

}