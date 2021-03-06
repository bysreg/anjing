#include "app/app.hpp"
#include "core/log.hpp"
#include "core/scene.hpp"
#include "core/assert.hpp"

#include <GL/glew.h>

#include <cstdio>

int anjing::app::App::StartApplication(anjing::app::App* app, int width, int height, int fps, const std::string& title)
{
	ANJING_ASSERT(app);

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0){
		std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
		return -1;
	}

	// set OpenGL attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, ANJING_OPENGL_MAJOR_VERSION);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, ANJING_OPENGL_MINOR_VERSION);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	std::string win_title = title + " (" + std::to_string(fps) + " fps) ";
	SDL_Window *window = SDL_CreateWindow(win_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (window == NULL)
	{
		std::cerr << "SDL_CreateWindow error : " << SDL_GetError() << std::endl;
		return -2;
	}

	SDL_GLContext gl_context = SDL_GL_CreateContext(window);
	if (gl_context == NULL)
	{
		std::cerr << "SDL_GL_CreateContext failed : " << SDL_GetError() << std::endl;
		return -3;
	}

	glewExperimental = GL_TRUE;
	GLenum glewErr = glewInit();
	if (glewErr != GLEW_OK)
	{
		std::cerr << "glewInit failed : " << glewGetErrorString(glewErr) << std::endl;
		return -4;
	}

	app->width = width;
	app->height = height;
	app->window = window;
	app->gl_context = gl_context;

	if (app->Init() == 0)
	{
		std::cout << "application initialized" << std::endl;
	}

	return 0;
}

int anjing::app::App::StopApplication(anjing::app::App* app)
{
	ANJING_ASSERT(app);

	if(app->gl_context != nullptr)
		SDL_GL_DeleteContext(app->gl_context);
	
	if(app->window != nullptr)
		SDL_DestroyWindow(app->window);

	ANJING_LOGS("application is closed\n");

	return 0;
}

void anjing::app::App::UpdateEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		switch (e.type)
		{
		case SDL_QUIT:
			Shutdown();
			break;
		}
	}
}

void anjing::app::App::RunMainLoop(anjing::app::App* app, MainLoopFunc func)
{
	ANJING_ASSERT(app);

	while (!app->shutting_down)
	{
		app->UpdateEvents();
		
		func(); // call the user provided function

		glFlush();
		SDL_GL_SwapWindow(app->window);
	}
}

std::FILE* anjing::app::App::GetAssets(std::string filename, std::string mode)
{	
	static std::string assets_dir = "./assets";
	
	// try to open it first inside the assets folder in the same directory as the program
	std::string path = (assets_dir + "/" + filename);
	std::FILE* file = std::fopen(path.c_str(), mode.c_str());
	
	// if it fails to open it, try to open the file above the folder hierarchy THREE times
	// (this means the program relative path starts from:
	// <project directory>/build/<src or test>/<the startup project>/
	if (file == nullptr)
	{
		path = "../../../assets/" + filename;
		file = std::fopen(path.c_str(), mode.c_str());
	}

	// if it fails to open it, try to open the file above the folder hierarchy FOUR times 
	// (this means the program relative path starts from:
	// <project directory>/build/<src or test>/<the startup project>/<build mode (Debug or Release)>/
	if (file == nullptr)
	{
		path = "../../../../assets/" + filename;
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
	// initialize Anjing Scene
	anjing::core::Scene::GetInstance().SetScreenSize(width, height);

	// this is needed since OpenGL 3.2+ Core profile
	GLuint vertex_array_id;
	glGenVertexArrays(1, &vertex_array_id);
	glBindVertexArray(vertex_array_id);


	return 0;
}

void anjing::app::App::Clean()
{
}