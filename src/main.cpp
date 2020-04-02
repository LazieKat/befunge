#include <iostream>
#include "befunge.h"

int main(int argc, char* argv[])
{
	if(argv[1] == NULL)
	{
		std::cout << "Error: No input file\n";
		return 1;
	}

	std::ifstream file;
	file.open(argv[1]);
	
	if(!file.is_open())
	{
		std::cout << "Error: Could not open input file \"" << argv[1] << "\"\n";
		return 2;
	}
	
	Befunge app(&file);
	file.close();

	while(true)
	{
		app.execute();
		app.move();
	}
}