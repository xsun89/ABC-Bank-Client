#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "../Public/Singleton.h"
using namespace PUBLIC;

class Client
{
	friend class Singleton<Client>;
public:
	Client();
	~Client();
};

#endif

