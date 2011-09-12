// Entry point for osm-flyer application
#include <iostream>
#include "FlyerWindow.hpp"

int main(int argc, char* argv[])
{
    FlyerWindow flyer(10,36.134,-80.2761);
    flyer.run();

	return 0;
}
