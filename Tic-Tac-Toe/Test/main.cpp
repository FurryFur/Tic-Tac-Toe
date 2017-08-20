//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: main.cpp
// Description	: Tests entry point
// Author		: Lance Chaney
// Mail			: lance.cha7337@mediadesign.school.nz
//

#include <conio.h>

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

int main(int argc, char* argv[])
{
	// global setup...

	int result = Catch::Session().run(argc, argv);

	// global clean-up...

	_getch();

	return (result < 0xff ? result : 0xff);
}