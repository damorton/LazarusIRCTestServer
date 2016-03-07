#include <iostream>

#include "server\server.h"

int main()
{
	server::Server *lazarusServer = new server::Server();
	delete lazarusServer;
	return 0;
}