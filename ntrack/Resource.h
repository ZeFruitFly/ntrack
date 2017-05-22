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
		Resource(path);
		~Resource();

		void start();//Needs to load in resources
		void stop();//Needs to unload uneeded resources
		inline void restart();//Calls start() then stop()

		void addSpawnPoint(vector3d<s32>);
		void addMap(path);
		void addMesh(path);
		void addTexture(path);
		void addScript(path, char);

		inline void setName(stringw);
		inline void setDescription(stringw);
		inline void setVersion(stringw);
		inline void setType(stringw);

		stringw getName();
		inline stringw getDescription();
		inline stringw getVersion();
		inline stringw getType();

	private:
		bool running;
		list<vector3d<s32>> spawnpoints;
		list<path> maps;
		list<path> meshs;
		list<path> textures;
		list<path> scripts_Client, scripts_Server;

		
		lua_State *L_Client = NULL, *L_Server = NULL;

		stringw name, description, version, type;
	};

}//namespace ntrack_g