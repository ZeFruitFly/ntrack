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
	if (!fs->changeWorkingDirectoryTo("Resources"))
	{
		throw "Unable to change directory";
	}
	
	IFileList *FileList = fs->createFileList();
	if (FileList == NULL)
	{
		//Why must this happen D:
		throw "Resource manager cannot create file list";
	}
	if (FileList->getFileCount() > 0)
	{
		for (u32 i = 0; i < FileList->getFileCount(); i++)
		{
			if (FileList->isDirectory(i))
			{
				//We have found a directory create a list of the files in it.
				path theFolder = FileList->getFileName(i);
				if (theFolder == NULL)
				{
					throw "NULL folder name panic";
				}
				path resourceDir = fs->getWorkingDirectory();
				if (!fs->changeWorkingDirectoryTo(theFolder))
				{
					throw "Unable to change directory";
				}
				IFileList *FolderContents = fs->createFileList();
				//Now we need to check if meta.xml exists
				if (FolderContents->findFile("meta.xml") > -1)
				{
					/*meta.xml exists we should do something with it.
					On a personal note I need to figure out how i'm going
					to allocate resources before I continue*/
				}


			}//In the future search for zip files too :D
		}
	}

}


ResourceManager::~ResourceManager()
{
}
