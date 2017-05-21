#pragma once

#include <rapidjson/document.h>
#include <irrlicht.h>
#include <WinSock2.h>

#include "Player.h"
using namespace irr;
using namespace core;
namespace ntrack_g{
	class NetworkManager
	{
	public:
		NetworkManager();
		~NetworkManager();

		void setHostname(const char*);
		void setPort(const char*);

		void connectToServer();
		void openServer();

		void sendData(char*);
		char* receiveData();

		void acceptClient();

		void run();

		struct client{
			SOCKET sock;
		};
	};

}//namespace ntrack_g
