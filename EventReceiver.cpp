#include "EventReceiver.h"

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace gui;
using namespace io;
using namespace quake3;

bool EventReceiver::OnEvent(SEvent event)
{
    eventReceived(event);
}
