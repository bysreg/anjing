#pragma once

#include <string>

namespace anjing 
{
	namespace app
	{
		class App
		{
		public:


			///
			/// \brief Create the applications' window, initialize the app, SDL, and OpenGL
			///
			static int StartApplication(App* app, int width, int height, int fps, const std::string& title);

			///
			/// \brief Opens the file specified by \a filename in the default assets folder
			///
			/// Returns nullptr if the file does not exist
			/// You need to close the file if it successfully opened
			static std::FILE* GetAssets(std::string filename, std::string mode);

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
}