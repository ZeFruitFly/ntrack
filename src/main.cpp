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
    try{
        ntrack *gm = new ntrack(argc, argv);
    }catch(const char* error)
    {

    }
    return 0;
}
