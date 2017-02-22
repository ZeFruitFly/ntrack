#pragma once

#include <string>
#include <vector>
#include <iostream>

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
class Script
{
public:
	Script(const std::string&);
	~Script();

	void logError(std::string error);

	template<typename T>
	T get(const std::string& variableName);
private:
	lua_State *L;
};

