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
	}//namespace ntrack_lua
}//namespace ntrack_g
