#pragma once
#include <irrlicht.h>




using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace gui;
using namespace io;
using namespace quake3;

#include "globals.h"
/* This class should search irrlichts filesystem for lua scripts
and hand them down to ntrack.*/
namespace ntrack_g{
	class ResourceManager
	{
	public:
		ResourceManager(bool);
		~ResourceManager();

	private:
	};

}//namespace ntrack_g

