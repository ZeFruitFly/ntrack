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
    return 0;
}
