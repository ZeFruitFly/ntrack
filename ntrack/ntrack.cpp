#include "ntrack.h"

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace gui;
using namespace io;
using namespace quake3;
namespace ntrack_g{
	
	ntrack::ntrack(int argc, char *argv[])
	{
		logFile.open("Console.log", std::ios::out | std::ios::ate);
		globaldefs.mgr = new SettingsManager("settings.xml");
		//All settings provided via command line over ride the default settings or the settings in the xml.
		for (int i = 0; i < argc; i++)
		{
			if (i != 0)
			{
				if (strcmp("-D", argv[i]) == 0)
				{
					globaldefs.mgr->dedicatedServer = true; //Make sure to store this for later.
				}
				else if (strcmp("-w", argv[i]) == 0)
				{

				}

			}
		}
		globaldefs.game = createDevice(globaldefs.mgr->drvType, dimension2d<u32>(globaldefs.mgr->screen_w, 
																			globaldefs.mgr->screen_h), 
																			16, 
																			globaldefs.mgr->fullscreen, 
																			false, 
																			true, 
																			this);
		if (globaldefs.game == NULL)
		{
			throw "Device creation error";
			return; //Just in case
			//Device creation failed
		}
		globaldefs.driver = globaldefs.game->getVideoDriver();
		if (globaldefs.driver == NULL)
		{
			throw "Something is seriously wrong: getVideoDriver()";
			return;
		}
		globaldefs.smgr = globaldefs.game->getSceneManager();
		if (globaldefs.smgr == NULL)
		{
			throw "Something is seriously wrong: getSceneManager()";
			return;
		}
		globaldefs.guienv = globaldefs.game->getGUIEnvironment();
		if (globaldefs.guienv == NULL)
		{
			throw "Something is seriously wrong: getGUIEnvironment";
			return;
		}
		globaldefs.fs = globaldefs.game->getFileSystem();
		if (globaldefs.fs == NULL)
		{
			throw "Something is seriously wrong: getFileSystem()";
			return;
		}
		globaldefs.rmgr = new ResourceManager();
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
			//We can output this stuff to a file if we like.
			switch (event.LogEvent.Level)
			{
			case ELL_DEBUG:
				if (logFile.is_open())
				{
					logFile << "DEBUG: " << event.LogEvent.Text << std::endl;
				}
				break;
			case ELL_ERROR:
				if (logFile.is_open())
				{
					logFile << "ERROR: " << event.LogEvent.Text << std::endl;
				}
				break;
			case ELL_INFORMATION:
				if (logFile.is_open())
				{
					logFile << "INFO: " << event.LogEvent.Text << std::endl;
				}
				break;
			case ELL_NONE:
				if (logFile.is_open())
				{
					logFile << event.LogEvent.Text << std::endl;
				}
				break;
			case ELL_WARNING:
				if (logFile.is_open())
				{
					logFile << "WARN: " << event.LogEvent.Text << std::endl;
				}
				break;
			}
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
		theWin = globaldefs.guienv->addWindow(rect<s32>(40, 20, 250, 140),
			false,
			L"Connect",
			0,
			GUI_ID_CONNECT_WINDOW);
		theWin->getCloseButton()->setVisible(false);
		IPAddress = globaldefs.guienv->addEditBox(L"",
			rect<s32>(90, 30, 190, 50),
			false,
			theWin,
			GUI_ID_IP_TEXTBOX);
		PORT = globaldefs.guienv->addEditBox(L"",
			rect<s32>(90, 55, 190, 75),
			false,
			theWin,
			GUI_ID_PORT_TEXTBOX);
		globaldefs.guienv->addStaticText(L"Port: ",
			rect<s32>(10, 55, 80, 75),
			false,
			false,
			theWin,
			0,
			false);
		globaldefs.guienv->addStaticText(L"IP Address: ",
			rect<s32>(10, 30, 80, 50),
			false,
			false,
			theWin,
			0,
			false);
		globaldefs.guienv->addButton(rect<s32>(10, 80, 80, 100),
			theWin,
			GUI_ID_CONNECT_BUTTON,
			L"Connect");
		cnttxt = globaldefs.guienv->addStaticText(L"Shadow Sucks",//Text
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
		while (globaldefs.game->run())
		{
			globaldefs.driver->beginScene(true, true, SColor(255, 0, 0, 0));
			globaldefs.smgr->drawAll();
			globaldefs.guienv->drawAll();
			globaldefs.driver->endScene();
		}
		globaldefs.game->drop();
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
}//namespace ntrack_g