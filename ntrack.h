#ifndef NTRACK_H
#define NTRACK_H

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace gui;
using namespace io;
using namespace quake3;

#include "SettingsManager.h"

class ntrack
{
    public:
        ntrack(int argc, char *argv[]);
        virtual ~ntrack();

        void run();
    protected:
    private:
        SettingsManager *mgr = NULL;
        IrrlichtDevice *logic = NULL, *controll = NULL, *game = NULL;
        IVideoDriver *driver = NULL;
        ISceneManager *smgr = NULL;
        IGUIEnvironment *guienv = NULL;
};

#endif // NTRACK_H
