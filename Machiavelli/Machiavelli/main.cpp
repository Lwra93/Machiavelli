#pragma once
#include "config.h"
#include "GameServer.h"

int main(int argc, const char * argv[])
{

	//thread consumer(commands::consume);
	GameServer server;
	ServerSocket socket{ config::port };
	server.run(move(socket));
	//consumer.join();


}

