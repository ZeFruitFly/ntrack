#include "ntrack.h"

ntrack::ntrack(int argc, char *argv[])
{
    mgr = new SettingsManager("settings.xml");
    for(int i=0; i < argc; i++)
		{
			if(i != 0)
			{
				if(strcmp("-D", argv[i]) == 0)
				{
                    mgr.dedicatedServer = true; //Make sure to store this for later.
				}

			}
		}
}

ntrack::~ntrack()
{
    //dtor
}
