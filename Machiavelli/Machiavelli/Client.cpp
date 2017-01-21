#pragma once
#include "Client.h"
#include "ClientCommand.h"
#include "CommandHandler.h"
#include "GameServer.h"

void handle_client(Socket socket)
{

	if (get_clients().size() < 2)
	{

		shared_ptr<Client> client;

		try {

			client = make_shared<Client>(move(socket));
			client->hello();
			register_client(client);
		}
		catch (exception en) {
			cerr << client->get_player().get_name() + " disconnected. Deregistering client.\n";
		}

	}
	else
	{
		socket.write("Het spijt ons, maar het maximum aantal spelers is bereikt!");
		cerr << "Refusing incoming connection on " << socket.get_dotted_ip() << "!\r\n";
	}

}


Client::Client(Socket socket)
{

	this->socket = move(socket);

}

void Client::hello()
{

	this->socket.write("Welkom bij Machiavelli! Om te stoppen, typ 'quit'\r\n");
	this->socket.write("Wat is je naam?\r\n");
	auto name{ this->readline() };

	this->socket.write("Wat is je leeftijd?\r\n");
	auto age = -1;

	while(age < 0)
	{
		age = this->readnumber();
	}

	Player player { name, age };
	this->player = player;

	this->socket << "Welkom, " << player.get_name() << ", en veel plezier!\r\n";

}

const string Client::listen()
{

	string cmd{ "error" };
	try
	{
		cmd = this->readline();
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

	std::string result = "";

	std::function<void(std::string line)> function = [&](std::string line) { result = line; };

	bool worked = false;

	while(!worked)
	{
		worked = this->socket.readline(function);
	}

	if (result == "quit")
		deregister_client(shared_from_this());
	else if (result == "quit_server")
		shutdown_machiavelli();
	

	return result;
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