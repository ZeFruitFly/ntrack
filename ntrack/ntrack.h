#pragma once
#include <iostream>
#include <fstream>
#include <irrlicht.h>
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace gui;
using namespace io;
using namespace quake3;

#include "SettingsManager.h"
#include "ResourceManager.h"


/* This class is the hub of all activity, lua will be initialized here,
as will settings, client/server connections etc. */
class ntrack : public IEventReceiver
{
public:
	ntrack(int argc, char *argv[]);
	virtual ~ntrack();

	virtual bool OnEvent(const SEvent&);

	void buildConnectWindow();

	void run();

	void connectToServer();
	void startServer();

	//Called when a corresponding event has been triggered.
	void onButtonClicked(IGUIButton *);
	void onMenuItemSelected(IGUIContextMenu *);
protected:
private:
	SettingsManager *mgr = NULL;
	IrrlichtDevice *logic = NULL, *controll = NULL, *game = NULL;
	IVideoDriver *driver = NULL;
	ISceneManager *smgr = NULL;
	IGUIEnvironment *guienv = NULL;
	IFileSystem *fs = NULL;



	//Network stuff

	//GUI Stuff
	enum
	{
		GUI_ID_CONNECT_WINDOW = 100,
		GUI_ID_CONNECT_BUTTON = 101,
		GUI_ID_IP_TEXTBOX = 102,
		GUI_ID_PORT_TEXTBOX = 103,
		GUI_ID_CONNECT_WINDOW_TEXT = 104
	};
	IGUIStaticText *cnttxt = NULL;
	IGUIWindow *theWin = NULL;
	IGUIEditBox *IPAddress = NULL, *PORT = NULL;

	//Lua stuff
	lua_State *cL = NULL, *sL = NULL;

	//Resource manager garbage

	ResourceManager * rmgr = NULL;

	//Logging stuff
	std::ofstream logFile;
};



