#include "Resource.h"

namespace ntrack_g{
	Resource::Resource()
	{
	}


	Resource::~Resource()
	{
	}

	//A usefull bit to avoid searching for uneeded bits thus saving some performance. :P
	bool Resource::hasSpawnPoint()
	{
		return spawnpoints.empty();
	}

	bool Resource::hasMap()
	{
		return maps.empty();
	}

	bool Resource::hasMesh()
	{
		return meshs.empty();
	}

	bool Resource::hasTexture()
	{
		return textures.empty();
	}

	bool Resource::hasScript()
	{
		return scripts.empty();
	}

	void Resource::addSpawnPoint(vector3d<s32> point)
	{
		spawnpoints.push_back(point);
	}

	void Resource::addMap(path file)
	{
		maps.push_back(file);
	}

	void Resource::addMesh(path file)
	{
		meshs.push_back(file);
	}

	void Resource::addTexture(path file)
	{
		textures.push_back(file);
	}

	void Resource::addScript(path file)
	{
		scripts.push_back(file);
	}
	void Resource::start()
	{
		
	}
	void Resource::stop()
	{
		//Unload resources
		if (!meshs.empty())
		{
			//Unload meshs here
			for (list<path>::Iterator it = meshs.begin(); it != meshs.end(); it++)
			{
				path thePath = *it;
				globaldefs.game->getSceneManager()->getMeshCache()->removeMesh(globaldefs.game->getSceneManager()->getMesh(thePath));
			}
		}
		if (!textures.empty())
		{
			//Unload textures here
			for (list<path>::Iterator it = textures.begin(); it != textures.end(); it++)
			{
				path thePath = *it;
				globaldefs.game->getVideoDriver()->removeTexture(globaldefs.game->getVideoDriver()->getTexture(thePath));
			}
		}
		//Cleanup the client lua state.
		if (L_Client)
		{
			lua_close(L_Client);
		}
		//Cleanup the server lua state.
		if (L_Server)
		{
			lua_close(L_Server);
		}
	}
	void Resource::restart()
	{
		start();

		stop();
	}

}//namespace ntrack_g