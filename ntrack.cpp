#include "ntrack.h"

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace gui;
using namespace io;
using namespace quake3;

ntrack::ntrack(int argc, char *argv[])
{
    mgr = new SettingsManager("settings.xml");
    //All settings provided via command line over ride the default settings or the settings in the xml.
    for(int i=0; i < argc; i++)
    {
			if(i != 0)
			{
				if(strcmp("-D", argv[i]) == 0)
				{
                    mgr->dedicatedServer = true; //Make sure to store this for later.
				}

			}
    }
    game = createDevice(mgr->drvType, dimension2d<u32>(mgr->screen_w, mgr->screen_h), 16, mgr->fullscreen);

}

ntrack::~ntrack()
{
    //dtor
}
