#include "SettingsManager.h"

SettingsManager::SettingsManager(stringw settingsFile)
{
    IrrlichtDevice *tempDevice = createDevice(EDT_NULL);

    SIrrlichtCreationParameters tempParams;

    const stringw configTag(L"setting");
    const stringw settingTag(L"setting");
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

}

SettingsManager::~SettingsManager()
{
    //dtor
}
