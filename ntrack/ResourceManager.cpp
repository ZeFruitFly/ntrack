#include "ResourceManager.h"
using namespace irr;
#include "globals.h"

namespace ntrack_g{
	
	ResourceManager::ResourceManager()
	{
		globaldefs.logger->log("Initiated Resource Manager", ELL_INFORMATION);
		/*TODO: Search the resource directory for zip files or folders.
		Then locate a meta.xml file. Use the contents of the meta.xml to
		load build a list of files to load when the resource is started.*/
		if (!globaldefs.game->getFileSystem()->changeWorkingDirectoryTo("Resources"))
		{
			globaldefs.logger->log("Unable to open resource directory, does it exist?", ELL_ERROR);
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
								globaldefs.logger->log("NULL folder name", ELL_ERROR);
								throw "NULL folder name panic";
							}

							if (!globaldefs.game->getFileSystem()->changeWorkingDirectoryTo(theFolder))
							{
								stringw errorout = "Unable to open folder ";
								errorout += theFolder;
								errorout += " skipping";
								globaldefs.logger->log(errorout.c_str(), ELL_ERROR);
								//throw "Unable to change directory";
							}
							else
							{//The program will no longer throw an exception instead it'll just skip it.
								IFileList *FolderContents = globaldefs.game->getFileSystem()->createFileList();
								globaldefs.logger->log(L"Creating new resource...", ELL_DEBUG);
								Resource *tempres = new Resource(theFolder);
								//TODO: Error checking;
								Resources.push_back(tempres);//Add our resource to the list of resources.
								tempres = 0;//Delete is not suitable here and we don't need no pesky memory leaks :P

							}


						}//In the future search for zip files too :D

					}

				}
				globaldefs.game->getFileSystem()->changeWorkingDirectoryTo(resourceDir);
				
			}
		}
		stringw output = "Finished Loading ";
		output += Resources.getSize();
		output += " Resources.";
		globaldefs.logger->log(output.c_str(), ELL_INFORMATION);
		globaldefs.logger->log(L"Dumping loaded resources", ELL_DEBUG);
		for (list< Resource*>::Iterator it = Resources.begin(); it != Resources.end(); it++)
		{
			Resource* temp = *it;
			globaldefs.logger->log(temp->getName().c_str(), ELL_DEBUG);
		}

	}


	ResourceManager::~ResourceManager()
	{
		
	}

}//namespace ntrack_g