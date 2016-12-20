#pragma once
#include "Client.h"
#include "ClientCommand.h"
#include "CommandHandler.h"
#include "GameServer.h"

void handle_client(Socket socket)
{

	if (get_clients().size() < 2)
	{

		try {

			auto client = make_shared<Client>(move(socket));
			client->hello();
			register_client(client);

			//while (true)
			//{
			//	/*auto client_command{ client->listen() };

			//	if (client_command == "quit")
			//		break;

			//	ClientCommand cmd{ client_command, client };
			//	commands::add(cmd);*/
			//}

			//deregister_client(client);

		}
		catch (exception en) {
			cerr << "handle_client crashed\n" << en.what();
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
	auto name{ this->readline() };

	this->socket.write("What's your age?\r\n");
	auto age = -1;

	while(age < 0)
	{
		age = this->readnumber();
	}

	Player player { name, age };
	this->player = player;

	this->socket << "Welcome, " << player.get_name() << ", have fun playing our game!\r\n";

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
		write("ERROR: Somewhting went wrong during handling of your request. Sorry! \r\n");
	}

	return cmd;

}

void Client::write(string line) const
{
	this->socket.write(line);
	this->socket.write("\r\n");
}

void Client::writeInput(string line) const
{
	this->socket.write(line);
}

const string Client::readline() 
{
	this->socket.write("> ");
	auto line = this->socket.readline();

	if (line == "quit")
		deregister_client(shared_from_this());

	return line;
}

const int Client::readnumber()
{
	auto line = this->readline();
	auto nr = -1;

	try
	{
		nr = stoi(line);
	}
	catch(...)
	{
		
	}

	return nr;
}

Player& Client::get_player()
{
	return this->player;
}

const Socket& Client::get_socket() const
{
	return this->socket;
}

void Client::close()
{
	this->socket.close();
}