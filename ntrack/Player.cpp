#include "Player.h"
#include "globals.h"

namespace ntrack_g{
	namespace ntrack_lua{
		Player::Player()
		{
		}


		Player::~Player()
		{
		}

		int L_Server_Player_Constructor(lua_State *L_Server)
		{
			Player **udata = (Player**)lua_newuserdata(L_Server, sizeof(Player*));
			*udata = new Player();
			return 0;
		}

		int L_Server_Player_setPos(lua_State *L_Server)
		{
			return 0;
		}
		int L_Server_Player_setName(lua_State *L_Server)
		{
			return 0;
		}
		void L_Server_Player_RegLua(lua_State *L_Server)
		{
			luaL_Reg sPlayerRegs[] =
			{
				{ "new", L_Server_Player_Constructor },
				{ "setPosition", L_Server_Player_setPos},
				{ "setName", L_Server_Player_setName },
				{ "__gc", L_Server_Player_Destructor },
				{ NULL, NULL}
			};

			luaL_newlibtable(L_Server, "luaL_Player");

			luaL_setfuncs(L_Server, sPlayerRegs, 0);

			lua_pushvalue(L_Server, -1);

			lua_setfield(L_Server, -1, "__index");

			lua_setglobal(L_Server, "player");
		}
		inline Player * L_Server_CheckPlayer(lua_State *L_Server, int n)
		{
			return *(Player **)luaL_checkudata(L_Server, n, "luaL_Player");
		}
		int L_Server_Player_Destructor(lua_State *L_Server)
		{
			Player *thePlayer = L_Server_CheckPlayer(L_Server, 1);

			delete thePlayer;

			return 0;
		}
	}//namespace ntrack_lua
}//namespace ntrack_g
