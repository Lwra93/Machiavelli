#pragma once
#include "Client.h"
#include "ClientCommand.h"
#include "CommandHandler.h"

namespace client
{

	int connected = 0;

	void handle(Socket socket)
	{
		if (connected < 2)
		{

			try {

				auto client = make_shared<Client>(move(socket));
				client->hello();
				connected++;

				while (true)
				{
					auto client_command{ client->listen() };

					if (client_command == "quit")
						break;

					ClientCommand cmd { client_command, client };
					commands::add(cmd);
				}

				client->disconnect();

			}
			catch (...) {
				cerr << "handle_client crashed\n";
			}

		}
		else
		{
			socket.write("Terribly sorry, but the game cannot contain more players.");
			cerr << "Refusing incoming connection on " << socket.get_dotted_ip() << "!\r\n";
		}


	}

	Client::Client(Socket socket)
	{

		this->socket = move(socket);

	}

	void Client::hello()
	{

		this->socket.write("Welcome to Server 1.0! To quit, type 'quit'.\r\n");
		this->socket.write("What's your name?\r\n");
		this->socket.write("Machiavelli> ");
		string name{ this->socket.readline() };
		Player player{ name };
		this->player = player;

		this->socket << "Welcome, " << player.get_name() << ", have fun playing our game!\r\n Machiavelli> ";

	}

	const string Client::listen() const
	{

		string cmd{ "error" };
		try
		{
			cmd = socket.readline();
			cerr << '[' << socket.get_dotted_ip() << " (" << socket.get_socket() << ") " << player.get_name() << "] " << cmd << "\r\n";

		}
		catch (const exception& ex)
		{
			socket << "ERROR: " << ex.what() << "\r\n";
		}
		catch (...)
		{
			socket.write("ERROR: Somewhting went wrong during handling of your request. Sorry! \r\n");
		}

		return cmd;

	}

	void Client::disconnect() const
	{
		this->socket.write("Thank you for playing Machiavelli. We will await your return!");
		connected--;
	}



	const Player& Client::get_player() const
	{
		return this->player;
	}

	const Socket& Client::get_socket() const
	{
		return this->socket;
	}
}




