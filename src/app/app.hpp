#pragma once

#include <string>

namespace anjing 
{
	class App 
	{
	public:
		static int StartApplication(App* app, int width, int height, int fps, std::string title);

		virtual int Init();		
		virtual void Clean();
	};
}