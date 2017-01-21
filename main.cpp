#include <irrlicht.h>
#include "SettingsManager.h"
#include "ntrack.h"

using namespace irr;
using namespace io;
using namespace scene;
using namespace video;
using namespace gui;
using namespace quake3;

int main(int argc, char *argv[])
{
    ntrack *gm = new ntrack(argc, argv);
    /*if(argc > 1)
	{
		//Special arguments passed
		for(int i=0; i < argc; i++)
		{
			if(i != 0)
			{
				if(strcmp("-D", argv[i]) == 0)
				{

				}

			}
		}
	}*/
    return 0;
}
