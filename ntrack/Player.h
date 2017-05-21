#pragma once
extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace gui;
using namespace io;
using namespace quake3;

namespace ntrack_g{
	namespace ntrack_lua{
		class Player
		{
		public:
			Player();
			~Player();

			void setPos(int x, int y, int z);
			void setName(stringw);

		private:
			stringw name;
			ICameraSceneNode *PlayerCamera;
		};
		int L_Server_Player_Constructor(lua_State *);

		int L_Server_Player_setPos(lua_State *);

		int L_Server_Player_setName(lua_State *);

		void L_Server_Player_RegLua(lua_State *);

		inline Player * L_Server_CheckPlayer(lua_State *, int);
		int L_Server_Player_Destructor(lua_State *);
	}//namespace ntrack_lua
}//namespace ntrack_g

