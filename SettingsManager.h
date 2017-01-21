#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace gui;
using namespace io;
using namespace quake3;//Only for quake3 shaders I think

class SettingsManager
{
    public:
        SettingsManager(stringw);
        virtual ~SettingsManager();

        void saveSettings();
        void loadSettings(stringw);
    protected:
    private:
        int driver, screen_h, screen_w;
        bool fullscreen, dedicatedServer;
};

#endif // SETTINGSMANAGER_H
