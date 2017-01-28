#include <iostream>
#include <irrlicht.h>

#include "ntrack.h"
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace quake3;
using namespace std;
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "lua5.3.3-static.lib")


void main(int argc, char *argv[])
{
	try{
		ntrack *gm = new ntrack(argc, argv);
	}
	catch (const char* error)
	{
		//TODO: Fancy error output here.
		cout << error << endl;
		return;
	}
	
}