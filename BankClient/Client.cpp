#include "../Public/Socket.h"
#include "Client.h"


Client::Client()
{
	Socket::Startup();
}


Client::~Client()
{
	Socket::Cleanup();
}
