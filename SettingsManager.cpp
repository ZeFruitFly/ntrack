#include "SettingsManager.h"

SettingsManager::SettingsManager(stringw settingsFile)
{
    IrrlichtDevice *tempDevice = createDevice(EDT_NULL);

    SIrrlichtCreationParameters tempParams;

    const stringw configTag(L"setting");
    const stringw displaySettingTag(L"display");
    const stringw serverSettingTag(L"server"); //Only used when launching a server(Not yet implemented).
    const stringw resolution(L"resolution");
    const stringw drivertag(L"driver");
    const stringw fullscreentag(L"fullscreen");

    IXMLReader* settingsReader = tempDevice->getFileSystem()->createXMLReader(settingsFile);

    while(settingsReader->read()) //This will loop until we reach the end of the file
    {
        switch(settingsReader->getNodeType())
        {
        case EXN_NONE:
            break;
        case EXN_ELEMENT:
            if(configTag.equals_ignore_case(settingsReader->getNodeName()))//if <setting>
            {
                if(displaySettingTag.equals_ignore_case(settingsReader->getAttributeValueSafe(L"name")))//name=display
                {
                    //We gather our display settings here.
                    int driver = settingsReader->getAttributeValueAsInt(L"driver");//driver=???
                    if((driver != 0) && (driver < 5))
                    {
                        //Driver settings 1 = Software, 2 = OpenGL, 3 = DirectX9, 4 = burning(default).
                        switch(driver)
                        {
                        case 1:
                            drvType = EDT_SOFTWARE;
                            break;
                        case 2:
                            drvType = EDT_OPENGL;
                            break;
                        case 3:
                            drvType = EDT_DIRECT3D9;
                            break;
                        case 4:
                            drvType = EDT_BURNINGSVIDEO;
                            break;
                        }
                    }else{
                        drvType = EDT_BURNINGSVIDEO;
                    }
                    screen_w = settingsReader->getAttributeValueAsInt(L"width");//width=???
                    screen_h = settingsReader->getAttributeValueAsInt(L"height");//height=???
                    if((screen_w == 0) || (screen_h == 0))
                    {
                        //Use Default setting here.
                        screen_w = 800, screen_h = 600;
                    }
                    if(settingsReader->getAttributeValueAsInt(L"fullscreen") == 0)//fullscreen= 0 or 1
                    {
                        fullscreen = false;
                    }else{
                        fullscreen = true;
                    }
                }else if(serverSettingTag.equals_ignore_case(settingsReader->getAttributeValueSafe(L"name")))//name=server
                {
                    //Here is where the settings for the dedicated server will be processed or lan servers.
                }
            }
            break;
        case EXN_ELEMENT_END:
            break;
        case EXN_TEXT:
            break;
        case EXN_COMMENT:
            break;
        case EXN_CDATA:
            break;
        case EXN_UNKNOWN:
            break;
        }
    }

    //Free up memory
    settingsReader->drop();
    tempDevice->drop();

}

SettingsManager::~SettingsManager()
{
    //dtor
}

void saveSettings()
{

}
