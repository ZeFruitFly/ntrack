#include "ResourceManager.h"


ResourceManager::ResourceManager(lua_State *L, bool dedicated, IFileSystem *fs)
{
	if (fs == NULL)
	{ 
		//We should of never got to this point.
	}
	/*TODO: Search the resource directory for zip files or folders.
	Then locate a meta.xml file. Use the contents of the meta.xml to
	load build a list of files to load when the resource is started.*/
	if (!fs->changeWorkingDirectoryTo("\resources"))
	{

	}
	
	IFileList *FileList = fs->createFileList();
	if (FileList == NULL)
	{
		//Why must this happen D:
	}

}


ResourceManager::~ResourceManager()
{
}
