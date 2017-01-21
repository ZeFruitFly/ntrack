#ifndef NTRACK_H
#define NTRACK_H

#include <irrlicht.h>
#include <netClient.h>
#include <netServer.h>
using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace gui;
using namespace io;
using namespace quake3;

#include "SettingsManager.h"
#include "EventReceiver.h"

/* This class is the hub of all activity lua will be initialized here,
as will settings, client/server connections etc. */
class ntrack
{
    public:
        ntrack(int argc, char *argv[]);
        virtual ~ntrack();

        void buildConnectWindow();

        void run();
    protected:
    private:
        SettingsManager *mgr = NULL;
        IrrlichtDevice *logic = NULL, *controll = NULL, *game = NULL;
        IVideoDriver *driver = NULL;
        ISceneManager *smgr = NULL;
        IGUIEnvironment *guienv = NULL;

        //Network stuff
        netClient *clientCon = NULL;
        netServer *serverCon = NULL;

        //GUI Stuff
        enum
        {
            GUI_ID_CONNECT_WINDOW = 100,
            GUI_ID_CONNECT_BUTTON = 101,
            GUI_ID_IP_TEXTBOX = 102,
            GUI_ID_PORT_TEXTBOX = 103
        };
};

#endif // NTRACK_H
