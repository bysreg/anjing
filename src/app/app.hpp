#pragma once

#include <string>

namespace anjing 
{
	class App 
	{
	public:


		///
		/// \brief Create the applications' window, initialize the app, SDL, and OpenGL
		///
		static int StartApplication(App* app, int width, int height, int fps, const std::string& title);

	protected:

		///
		/// \brief Init will get called after app is ready to be used (at the end of StartApplication function call)
		///
		virtual int Init();		

		///
		/// \brief Release all app's memory
		///
		virtual void Clean();
	};
}