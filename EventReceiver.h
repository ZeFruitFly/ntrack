#ifndef EVENTRECEIVER_H
#define EVENTRECEIVER_H

#include <Irrlicht.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace gui;
using namespace io;
using namespace quake3;

class EventReceiver : public IEventReceiver
{
    public:
        EventReceiver();
        virtual ~EventReceiver();
    protected:
    private:
};

#endif // EVENTRECEIVER_H
