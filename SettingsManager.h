#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

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
    protected:
    private:
};

#endif // SETTINGSMANAGER_H
