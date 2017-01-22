#ifndef EVENTRECEIVER_H
#define EVENTRECEIVER_H

#include <Irrlicht.h>

#include "ntrack.h" //Infinite compiler loop waiting to happen
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
        virtual bool OnEvent(const SEvent& event)
        {
            eventReceived(event);
        }

        bool (*eventReceived)(const SEvent&);
    protected:
    private:
};

#endif // EVENTRECEIVER_H
