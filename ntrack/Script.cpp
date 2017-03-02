#include "Script.h"

namespace ntrack_g{

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

	void Script::logError(std::string error){
			globaldefs.game->getLogger()->log(error.c_str(), irr::ELL_ERROR);
	}

	template <typename T>
	T Script::lua_getdefault(const std::string&)
	{
		return "null";
	}
	template<typename T>
	T Script::get(const std::string& variableName){
		if (!L)
		{
			//Error
		}
	}
}
