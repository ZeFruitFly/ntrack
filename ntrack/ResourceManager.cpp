#include "ResourceManager.h"
using namespace irr;
#include "globals.h"

namespace ntrack_g{
	
	ResourceManager::ResourceManager()
	{
		globaldefs.game->getLogger()->log("Initiated Resource Manager", ELL_INFORMATION);
		/*TODO: Search the resource directory for zip files or folders.
		Then locate a meta.xml file. Use the contents of the meta.xml to
		load build a list of files to load when the resource is started.*/
		if (!globaldefs.game->getFileSystem()->changeWorkingDirectoryTo("Resources"))
		{
			globaldefs.game->getLogger()->log("Unable to open resource directory, does it exist?", ELL_ERROR);
			throw "Unable to change directory";
		}

		IFileList *FileList = globaldefs.game->getFileSystem()->createFileList();
		if (FileList == NULL)
		{
			//Why must this happen D:
			throw "Resource manager cannot create file list";
		}
		path resourceDir = globaldefs.game->getFileSystem()->getWorkingDirectory();
		if (FileList->getFileCount() > 0)
		{
			for (u32 i = 0; i < FileList->getFileCount(); i++)
			{
				if (FileList->isDirectory(i))
				{
					//We have found a directory create a list of the files in it.
					if (!stringw(".").equals_ignore_case(FileList->getFileName(i)))
					{
						if (!stringw("..").equals_ignore_case(FileList->getFileName(i)))
						{
							path theFolder = FileList->getFullFileName(i);
							if (theFolder == NULL)
							{
								globaldefs.game->getLogger()->log("NULL folder name", ELL_ERROR);
								throw "NULL folder name panic";
							}

							if (!globaldefs.game->getFileSystem()->changeWorkingDirectoryTo(theFolder))
							{
								stringw errorout = "Unable to open folder ";
								errorout += theFolder;
								errorout += " skipping";
								globaldefs.game->getLogger()->log(errorout.c_str(), ELL_ERROR);
								//throw "Unable to change directory";
							}
							else{//The program will no longer throw an exception instead it'll just skip it.
								IFileList *FolderContents = globaldefs.game->getFileSystem()->createFileList();
								//Now we need to check if meta.xml exists


								/*meta.xml exists we should do something with it.
								On a personal note I need to figure out how i'm going
								to allocate resources before I continue*/
								//Resource *theResource = new Resource()
								IXMLReader *metaReader = globaldefs.game->getFileSystem()->createXMLReader("meta.xml");
								if (metaReader == NULL)
								{
									stringw errorout = "Unable to load file";
									errorout += globaldefs.game->getFileSystem()->getWorkingDirectory();
									errorout += "/meta.xml";
									globaldefs.game->getLogger()->log(errorout.c_str(), ELL_ERROR);
								}
								stringw mapTag = "map";
								while (metaReader->read())
								{
									switch (metaReader->getNodeType())
									{
									case EXN_CDATA:
										break;
									case EXN_COMMENT:
										globaldefs.game->getLogger()->log("Found XML comment in meta.xml");
										break;
									case EXN_ELEMENT:
										if (mapTag.equals_ignore_case(metaReader->getNodeName()))
										{
											globaldefs.game->getLogger()->log("Loading map", ELL_INFORMATION);
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


						}//In the future search for zip files too :D

					}

				}
				globaldefs.game->getFileSystem()->changeWorkingDirectoryTo(resourceDir);
			}
		}

	}


	ResourceManager::~ResourceManager()
	{
		
	}

}//namespace ntrack_g