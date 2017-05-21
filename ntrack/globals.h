#pragma once
#include <irrlicht.h>

#include "SettingsManager.h"
#include "ResourceManager.h"


using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;
using namespace gui;

namespace ntrack_g{
	struct globals{
		SettingsManager *mgr;
		IrrlichtDevice *logic, *controll, *game;
		IVideoDriver *driver;
		ISceneManager *smgr;
		IGUIEnvironment *guienv;
		IFileSystem *fs;
		ResourceManager *rmgr;
		ILogger *logger;
	};
	extern globals globaldefs;
}//namespace ntrack_g

