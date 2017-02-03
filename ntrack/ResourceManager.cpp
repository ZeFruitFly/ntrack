#include "ResourceManager.h"


ResourceManager::ResourceManager(lua_State *L, bool dedicated, IFileSystem *fs, ILogger* logger)
{
	logger->log("Initiated Resource Manager", ELL_INFORMATION);
	if (fs == NULL)
	{ 
		//We should of never got to this point.
	}
	/*TODO: Search the resource directory for zip files or folders.
	Then locate a meta.xml file. Use the contents of the meta.xml to
	load build a list of files to load when the resource is started.*/
	if (!fs->changeWorkingDirectoryTo("Resources"))
	{
		logger->log("Unable to open resource directory, does it exist?", ELL_ERROR);
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
					logger->log("NULL folder name", ELL_ERROR);
					throw "NULL folder name panic";
				}
				path resourceDir = fs->getWorkingDirectory();
				if (!fs->changeWorkingDirectoryTo(theFolder))
				{
					stringw errorout = "Unable to open folder ";
					errorout += theFolder;
					errorout += " skipping";
					logger->log(errorout.c_str(), ELL_ERROR);
					//throw "Unable to change directory";
				}
				else{//The program will no longer throw an exception instead it'll just skip it.
					IFileList *FolderContents = fs->createFileList();
					//Now we need to check if meta.xml exists
					if (FolderContents->findFile("meta.xml") > -1)
					{
						/*meta.xml exists we should do something with it.
						On a personal note I need to figure out how i'm going
						to allocate resources before I continue*/
						IXMLReader *metaReader = fs->createXMLReader("meta.xml");
						if (metaReader == NULL)
						{
							stringw errorout = "Unable to load file";
							errorout += fs->getWorkingDirectory();
							errorout += "/meta.xml";
							logger->log(errorout.c_str(), ELL_ERROR);
						}
						stringw mapTag = "map";
						while (metaReader->read())
						{
							switch (metaReader->getNodeType())
							{
							case EXN_CDATA:
								break;
							case EXN_COMMENT:
								logger->log("Found XML comment in meta.xml");
								break;
							case EXN_ELEMENT:
								if (mapTag.equals_ignore_case(metaReader->getNodeName()))
								{
									//Load a map
								}
								break;
							case EXN_ELEMENT_END:
								break;
							case EXN_NONE:
								break;
							case EXN_TEXT:
								break;
							}
						}
					}
				}


			}//In the future search for zip files too :D
		}
	}

}


ResourceManager::~ResourceManager()
{
}
