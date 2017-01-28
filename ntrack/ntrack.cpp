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
	for (int i = 0; i < argc; i++)
	{
		if (i != 0)
		{
			if (strcmp("-D", argv[i]) == 0)
			{
				mgr->dedicatedServer = true; //Make sure to store this for later.
			}
			else if (strcmp("-w", argv[i]) == 0)
			{

			}

		}
	}
	game = createDevice(mgr->drvType, dimension2d<u32>(mgr->screen_w, mgr->screen_h), 16, mgr->fullscreen, false, true, this);
	if (game == NULL)
	{
		throw "Device creation error";
		return; //Just in case
		//Device creation failed
	}
	driver = game->getVideoDriver();
	if (driver == NULL)
	{
		throw "Something is seriously wrong: getVideoDriver()";
		return;
	}
	smgr = game->getSceneManager();
	if (smgr == NULL)
	{
		throw "Something is seriously wrong: getSceneManager()";
		return;
	}
	guienv = game->getGUIEnvironment();
	if (guienv == NULL)
	{
		throw "Something is seriously wrong: getGUIEnvironment";
		return;
	}
	fs = game->getFileSystem();
	if (fs == NULL)
	{
		throw "Something is seriously wrong: getFileSystem()";
		return;
	}
	run();

}

ntrack::~ntrack()
{
	//dtor
}

bool ntrack::OnEvent(const SEvent& event)
{
	if (event.EventType == EET_GUI_EVENT)
	{
		switch (event.GUIEvent.EventType)
		{
		case EGET_BUTTON_CLICKED:
			//A button has been clicked
			onButtonClicked((IGUIButton*)event.GUIEvent.Caller);
			break;
		}
	}
	else if (event.EventType == EET_JOYSTICK_INPUT_EVENT)
	{

	}if (event.EventType == EET_KEY_INPUT_EVENT)
	{

	}if (event.EventType == EET_LOG_TEXT_EVENT)
	{

	}
	else if (EET_MOUSE_INPUT_EVENT)
	{

	}
	else if (EET_USER_EVENT)
	{

	}
	return false;
}

//Build the gui for our connection window
void ntrack::buildConnectWindow()
{
	theWin = guienv->addWindow(rect<s32>(40, 20, 250, 140),
		false,
		L"Connect",
		0,
		GUI_ID_CONNECT_WINDOW);
	theWin->getCloseButton()->setVisible(false);
	IPAddress = guienv->addEditBox(L"",
		rect<s32>(90, 30, 190, 50),
		false,
		theWin,
		GUI_ID_IP_TEXTBOX);
	PORT = guienv->addEditBox(L"",
		rect<s32>(90, 55, 190, 75),
		false,
		theWin,
		GUI_ID_PORT_TEXTBOX);
	guienv->addStaticText(L"Port: ",
		rect<s32>(10, 55, 80, 75),
		false,
		false,
		theWin,
		0,
		false);
	guienv->addStaticText(L"IP Address: ",
		rect<s32>(10, 30, 80, 50),
		false,
		false,
		theWin,
		0,
		false);
	guienv->addButton(rect<s32>(10, 80, 80, 100),
		theWin,
		GUI_ID_CONNECT_BUTTON,
		L"Connect");
	cnttxt = guienv->addStaticText(L"Shadow Sucks",//Text
		rect<s32>(10, 100, 80, 110),//Size & Location
		false,
		false,
		theWin,//Parent
		GUI_ID_CONNECT_WINDOW_TEXT,//iD
		false);//Background
	cnttxt->setVisible(false);
}

void ntrack::run()
{
	buildConnectWindow();
	while (game->run())
	{
		driver->beginScene(true, true, SColor(255, 0, 0, 0));
		smgr->drawAll();
		guienv->drawAll();
		driver->endScene();
	}
	game->drop();
}

void ntrack::onButtonClicked(IGUIButton *btn)
{
	//TODO: Check if the button is ours if not dispatch to lua
	s32 id = btn->getID();
	if (id == GUI_ID_CONNECT_BUTTON)
	{
		//The connect button has been pushed
		//clientCon = new netClient()

		cnttxt->setVisible(true);//We tell them that shadow sucks for now. :P
	}
}
void ntrack::onMenuItemSelected(IGUIContextMenu *menu)
{


}
