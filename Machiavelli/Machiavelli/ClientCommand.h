//
//  ClientCommand.h
//  socketexample
//
//  Created by Bob Polis on 27/11/14.
//  Modified by Jeroen de Haas on 23/11/2016.
//  Copyright (c) 2016 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#ifndef __socketexample__ClientCommand__
#define __socketexample__ClientCommand__

#include <string>
#include <memory>
#include "Client.h"

class ClientCommand {
public:
    ClientCommand(const std::string& command_text, std::weak_ptr<Client> client_info)
    : cmd{command_text}, client{client_info} {}

    std::string get_cmd() const { return cmd; }
    std::weak_ptr<Client> get_client_info() const { return client; }

private:
    std::string cmd;
    std::weak_ptr<Client> client;
};

#endif /* defined(__socketexample__ClientCommand__) */
