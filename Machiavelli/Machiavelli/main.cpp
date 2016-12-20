#pragma once
#include "config.h"
#include "GameServer.h"

int main(int argc, const char * argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//thread consumer(commands::consume);
	GameServer server;
	ServerSocket socket{ config::port };
	server.run(move(socket));
	//consumer.join();


}

