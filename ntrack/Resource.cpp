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
		return scripts_Client.empty() || scripts_Server.empty();
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
			scripts_Client.push_back(file);
		}
		else if (type == 's')
		{
			scripts_Server.push_back(file);
		}
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
		if (!textures.empty())
		{
			//Unload textures here needs error checking
			for (list<path>::Iterator it = textures.begin(); it != textures.end(); it++)
			{
				path thePath = *it;
				globaldefs.driver->getTexture(thePath);
			}
		}
		if (!scripts_Client.empty())
		{
			if (L_Client == NULL)
			{
				L_Client = luaL_newstate();
				
			}
			for (list<path>::Iterator it = scripts_Client.begin(); it != scripts_Client.end(); it++)
			{
				path thePath = *it;
				if (luaL_loadfile(L_Client, thePath.c_str()) || lua_pcall(L_Client, 0, 0, 0))
				{
					//Log error here
				}
			}
		}
		if (!scripts_Server.empty())
		{
			if (L_Server == NULL)
			{
				L_Server = luaL_newstate();
				ntrack_lua::L_Server_Player_RegLua(L_Server);
			}
			for (list<path>::Iterator it = scripts_Server.begin(); it != scripts_Server.end(); it++)
			{
				path thePath = *it;
				if (luaL_loadfile(L_Server, thePath.c_str()) || lua_pcall(L_Server, 0, 0, 0))
				{
					//Log error here
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
					stringw error = "Could not unload some files in resource ";
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
				ITexture *theTexture = globaldefs.driver->getTexture(thePath);
				if (theTexture != NULL)
				{
					globaldefs.driver->removeTexture(globaldefs.game->getVideoDriver()->getTexture(thePath));
				}
				else
				{
					stringw error = "Could not unload some files in resource ";
					error += thePath;
					error += " is it already unloaded?";
					globaldefs.game->getLogger()->log(error.c_str(), ELL_WARNING);
				}
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
			//Nothing server side to unload
		}
	}

	inline void Resource::restart()
	{
		start();

		stop();
	}

}//namespace ntrack_g