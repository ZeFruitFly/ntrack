#pragma once
#include <irrlicht.h>



extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

#include "Player.h"
using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace gui;
using namespace io;
using namespace quake3;
namespace ntrack_g{
	class Resource
	{
	public:
		Resource(path, bool);
		~Resource();

		void start();//Needs to load in resources
		void stop();//Needs to unload uneeded resources
		inline void restart();//Calls start() then stop()

		bool hasSpawnPoint();
		bool hasMap();
		bool hasMesh();
		bool hasTexture();
		bool hasScript();

		void addSpawnPoint(vector3d<s32>);
		void addMap(path);
		void addMesh(path);
		void addTexture(path);
		void addScript(path, char);


	private:
		bool running;
		list<vector3d<s32>> spawnpoints;
		list<path> maps;
		list<path> meshs;
		list<path> textures;
		list<path> scripts_Client, scripts_Server;

		enum
		{
			map = 0,
			mesh = 1,
			texture = 2,
			script = 3
		};

		lua_State *L_Client = NULL, *L_Server = NULL;

		stringw name, description, version;
	};

}//namespace ntrack_g