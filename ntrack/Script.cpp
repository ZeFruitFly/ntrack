#include "Script.h"


Script::Script(const std::string& scriptFile)
{
	L = luaL_newstate();
	if (luaL_loadfile(L, scriptFile.c_str()) || lua_pcall(L, 0, 0, 0))
	{
		//We reach this if the script is not loaded;
		L = 0;
	}
}


Script::~Script()
{
	if (L)
	{ 
		lua_close(L);
	}
}
