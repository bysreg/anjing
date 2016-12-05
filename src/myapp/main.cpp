#include "app/app.hpp"
#include "core/memory_manager.hpp"
#include "core/util.hpp"

#include <cstdio>
#include <cstdlib>

static bool auto_close = false;

static bool ParseArgs(int argc, char* argv[])
{
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-')
		{
			switch (argv[i][1])
			{
			case 'y':
				auto_close = true;
				break;
			}
		}		
	}

	return true;
}

static void GameLoop()
{
	// TODO: to be implemented 
}

int main(int argc, char* argv[])
{
	if (!ParseArgs(argc, argv))
	{
		return EXIT_FAILURE;
	}

	anjing::app::App app;
	anjing::app::App::StartApplication(&app, 800, 600, 60, "My App");
	anjing::app::App::RunMainLoop(&app, GameLoop);

	anjing::core::MemoryManager::GetInstance().Dump();

	anjing::app::App::StopApplication(&app);

	if (!auto_close)
	{
		printf("Press any key to close...\n");
		int _ = getchar();
		ANJING_UNUSED(_);
	}

	return 0;
}