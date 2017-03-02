#pragma once
extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
namespace ntrack_g{
	namespace ntrack_lua{
		class Player
		{
		public:
			Player();
			~Player();

			void setPos(vector3d<s32>);
		};
		int L_Server_Player_Constructor(lua_State *);
		int L_Server_Player_setPos(lua_State *);
		int L_Server_Player_RegLua(lua_State *);
	}//namespace ntrack_lua
}//namespace ntrack_g

