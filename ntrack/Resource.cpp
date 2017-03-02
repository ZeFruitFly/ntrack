#include "Resource.h"
#include "globals.h"
namespace ntrack_g{
	Resource::Resource(path theFile, bool autoStart=false)
	{
		if (autoStart)
		{
			start();
		}
		if (theFile.empty())
		{
			//NULL filename
		}
	}


	Resource::~Resource()
	{
		stop();
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

	void Resource::addScript(path file, char type)
	{
		if (type == 'c')
		{
			//Client side script should be served to the client or loaded if we are the client.
			if (L_Client == NULL)
			{
				//We need to initialize L_Client first.
			}
			if (luaL_loadfile(L_Client, file.c_str() ) || lua_pcall(L_Client, 0, 0, 0))
			{
				//Error loading file
			}
		}
		else if (type == 's')
		{
			//Server side script load it if we're the server.
			if (L_Server)
			{
				//We need to initialize L_Server first.
			}
			if (luaL_loadfile(L_Server, file.c_str()) || lua_pcall(L_Client, 0, 0, 0))
			{
				//Error loading file
			}
		}
		//scripts.push_back(file);
	}
	void Resource::start()
	{
		if (!meshs.empty())
		{
			for (list<path>::Iterator it = meshs.begin(); it != meshs.end(); it++)
			{
				path thePath = *it;
				if (!thePath.empty())
				{
					/*If this is the first time calling getMesh() for this file
					irr::scene::SceneManager will load it into the mesh cache*/
					globaldefs.smgr->getMesh(thePath);
				}
				else
				{
					//What in the hell went wrong here??????
					stringw error = "Null path provided";
					globaldefs.game->getLogger()->log(error.c_str(), ELL_ERROR);
				}
			}
		}
	}

	void Resource::stop()
	{
		//Unload resources
		if (!meshs.empty())
		{
			//Unload meshs here needs error checking
			for (list<path>::Iterator it = meshs.begin(); it != meshs.end(); it++)
			{
				path thePath = *it;
				IMesh *theMesh = NULL; 
				theMesh = globaldefs.smgr->getMesh(thePath);
				if (theMesh != NULL)
				{
					globaldefs.smgr->getMeshCache()->removeMesh(theMesh);
				}
				else
				{
					stringw error = "Resource manager could not unload resource ";
					error += thePath;
					error += " is it already unloaded?";
					globaldefs.game->getLogger()->log(error.c_str(), ELL_WARNING);
					//Something is seriously wrong here.
				}
			}
		}
		if (!textures.empty())
		{
			//Unload textures here needs error checking
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
		else
		{
			//Nothing client side to unload

		}
		//Cleanup the server lua state.
		if (L_Server)
		{
			lua_close(L_Server);
		}
		else
		{
			//Nothing server side to reload
		}
	}
	void Resource::restart()
	{
		start();

		stop();
	}

}//namespace ntrack_g