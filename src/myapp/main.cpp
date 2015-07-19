#include "app/app.hpp"

#include <iostream>
#include <cstdio>

using namespace std;
using namespace anjing;

int main()
{
	App app;
	App::StartApplication(&app, 800, 600, 60, "My App");
	

	printf("Press any key...\n");
	char c;
	scanf("%c", &c);

	return 0;
}