#include "app/app.hpp"

#include <cstdio>
#include <cstdlib>

using namespace std;
using namespace anjing;

static bool auto_close = false;

static bool ParseArgs(int argc, char* argv[])
{
	for (int i = 2; i < argc; i++)
	{
		switch (argv[i][1])
		{
		case 'y':
			auto_close = true;
			break;			
		}
	}

	return true;
}

int main(int argc, char* argv[])
{
	App app;
	App::StartApplication(&app, 800, 600, 60, "My App");
	
	if (!ParseArgs(argc, argv))
	{
		return EXIT_FAILURE;
	}

	if (!auto_close)
	{
		printf("Press any key to close...\n");
		char c;
		scanf("%c", &c);
	}

	return 0;
}