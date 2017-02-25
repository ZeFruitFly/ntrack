#pragma once

#include <irrlicht.h>

#include <string>
#include <vector>
#include <iostream>

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include "globals.h"

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace gui;
using namespace io;

namespace ntrack_g{
	class Script
	{
	public:
		Script(const std::string&);
		~Script();

		void start();
		void stop();
		void restart();//Just calls start() then stop()
		bool isRunning(); //Only really called by outside classes

		void logError(std::string error);

		template<typename T>
		T get(const std::string& variableName);

		bool lua_gettostack(const std::string& variableName);

		template<typename T>
		T lua_get(const std::string& variableName);

		template<typename T>
		T lua_getdefault(const std::string& variableName);
	private:
		bool running = false;
		lua_State *L = NULL;
	};

}//namespace