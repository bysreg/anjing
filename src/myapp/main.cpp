#include "app/app.hpp"
#include "core/memory_manager.hpp"

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

int main(int argc, char* argv[])
{
	anjing::app::App app;
	anjing::app::App::StartApplication(&app, 800, 600, 60, "My App");
	
	if (!ParseArgs(argc, argv))
	{
		return EXIT_FAILURE;
	}

	anjing::core::MemoryManager::GetInstance().Dump();

	if (!auto_close)
	{
		printf("Press any key to close...\n");
		getchar();
	}

	anjing::app::App::StopApplication(&app);

	return 0;
}