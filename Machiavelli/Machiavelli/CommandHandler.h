#pragma once
#include "ClientCommand.h";
#include "ClientInfo.h"
#include "Sync_queue.h"
#include <iostream>

namespace commands
{

	static Sync_queue<ClientCommand> queue;

	inline void consume()
	{

		try {
			while (true) {
				ClientCommand command{ queue.get() }; // will block here unless there are still command objects in the queue
				if (auto clientInfo = command.get_client_info().lock()) {
					auto &client = clientInfo->get_socket();
					auto &player = clientInfo->get_player();
					try {
						// TODO handle command here
						client << player.get_name() << ", you wrote: '" << command.get_cmd() << "', but I'll ignore that for now.\r\n Machiavelli> ";
					}
					catch (const exception& ex) {
						cerr << "*** exception in consumer thread for player " << player.get_name() << ": " << ex.what() << '\n';
						if (client.is_open()) {
							client.write("Sorry, something went wrong during handling of your request.\r\n");
						}
					}
					catch (...) {
						cerr << "*** exception in consumer thread for player " << player.get_name() << '\n';
						if (client.is_open()) {
							client.write("Sorry, something went wrong during handling of your request.\r\n");
						}
					}
				}
			}
		}
		catch (...) {
			cerr << "consume_command crashed\n";
		}

	}

	inline void add(const ClientCommand command)
	{

		queue.put(command);

	}


	inline void handle(const string)
	{



	}

}