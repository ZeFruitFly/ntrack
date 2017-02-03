#pragma once
#include <irrlicht.h>

extern "C"{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace gui;
using namespace io;
using namespace quake3;
/* This class should search irrlichts filesystem for lua scripts
and hand them down to ntrack.*/
class ResourceManager
{
public:
	ResourceManager(lua_State*, bool, IFileSystem*, ILogger*);
	~ResourceManager();

private:
	list<vector3d<s32>> spawnpoints; //Used to store spawn locations.
	list<path> scripts;
	list<path> maps;
};

