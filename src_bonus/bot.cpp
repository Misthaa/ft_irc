/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madegryc <madegryc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:07:53 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/23 17:37:40 by madegryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"

bot::bot(std::string nickname, std::string port, std::string password)
{
    _nickname = nickname;
    _port = port;
    _password = password;
}

bot::~bot()
{
    close(_clientSocket);
}

static std::string nextArg(std::string infos)
{
	if (infos.find(" ") == std::string::npos)
		return "";
	infos = infos.substr(infos.find(" ") + 1);
	return infos;
}

std::string ft_to_string(int i)
{
    std::string str;
    std::stringstream ss;
    ss << i;
    ss >> str;
    return str;
}

void response(int _clientSocket, std::string msg)
{
    msg += "\n";
    send(_clientSocket, msg.c_str(), msg.size(), MSG_NOSIGNAL | MSG_DONTWAIT);
}

// void bot::priceIsRight(std::string content, std::string player)
// {
//     std::string allPlayer[100];
//     std::string clothing[10] = {"T-shirt", "Pants", "Shoes", "Hat", "Gloves", "Socks", "Underwear", "Jacket", "Scarf", "Belt"};
//     std::string brend[10] = {"Arte", "Nike", "Puma", "Reebok", "Vans", "Supraw", "New Balance", "Carhartt", "Champion", "Asics"};

//     bool firstTime = true;
//     player = player.substr(1);
//     std::string token = content.substr(0, content.find(" "));
//     content = content.substr(content.find(" ") + 1);
//     int price = 0;
//     if (firstTime == true)
//     {
//         firstTime = false;
//         int random = rand() % 10;
//         std::string msg = "PRIVMSG " + player + " PRICERIGHT " + clothing[random] + " " + brend[random];
//         response(_clientSocket, msg);
//         price = rand() % 1000;
//         std::cout << "PRICE : " << price << std::endl;
//     }
//     else
//     {
//         if (content == ft_to_string(price))
//         {
//             firstTime = true;
//             std::string msg = "PRIVMSG " + player + " PRICERIGHT " + "YES";
//             response(_clientSocket, msg);

//         }
//         else
//         {
//             std::string msg = "PRIVMSG " + player + " PRICERIGHT " + "NO";
//             response(_clientSocket, msg);

//         }
//     }
// }

bool bot::isNewPlayer(std::string player)
{
    for (std::map<std::string, int>::iterator it = _playerMap.begin(); it != _playerMap.end(); it++)
	{
		if (it->first == player)
			return false;
    }
    return true;
}

void bot::addPlayer(std::string player)
{
    std::string clothing[10] = {"T-shirt", "Pants", "Shoes", "Hat", "Gloves", "Socks", "Underwear", "Jacket", "Scarf", "Belt"};
    std::string brend[10] = {"Arte", "Nike", "Puma", "Reebok", "Vans", "Supraw", "New Balance", "Carhartt", "Champion", "Asics"};

    int random = rand() % 10;
    std::string msg = "PRIVMSG " + player + " PRICERIGHT " + clothing[random] + " " + brend[random];
    response(_clientSocket, msg);
    int price = rand() % 1000;
    std::cout << "PRICE : " << price << std::endl;
    _playerMap[player] = price;
}

void bot::priceIsRight(std::string content, std::string player)
{
    if (isNewPlayer(player) == false)
    {
        addPlayer(player);
        return ;
    }

    player = player.substr(1);
    std::string token = content.substr(0, content.find(" "));
    content = content.substr(content.find(" ") + 1);
    if (content == ft_to_string(price))
    {
        std::string msg = "PRIVMSG " + player + " PRICERIGHT " + "YES";
        response(_clientSocket, msg);

    }
    else
    {
        std::string msg = "PRIVMSG " + player + " PRICERIGHT " + "NO";
        response(_clientSocket, msg);

    }
}

void bot::readDataBot()
{
    int ret;
    _fds.events = POLLIN;
    _fds.revents = 0;
    _fds.fd = _clientSocket;
    std::string msg = "PASS " + _password + "\n";
    msg += "USER bot 0 * : bot\n";
    msg += "NICK " + _nickname + "\n";
    send(_clientSocket, msg.c_str(), msg.size(), MSG_NOSIGNAL | MSG_DONTWAIT);
    while (1)
    {
        ret = poll(&_fds, 1, 100);
        if (_fds.revents & POLLIN)
        {
            char buff[1024];
            ret = recv(_clientSocket, buff, 1024, 0);
            if (ret <= 0)
            {
                close(_clientSocket);
                return;
            }
            buff[ret - 1] = '\0';
            std::string content = buff;
            std::string player = content.substr(0, content.find(" "));
            content = nextArg(content);
            std::string token = content.substr(0, content.find(" "));
            content = nextArg(content);
            content = nextArg(content);
            std::string tokenBot = content.substr(0, content.find("\n"));
            std::cout << "TOKEN BOT ICIII : " << "'" << tokenBot << "'" << std::endl;
            if (tokenBot == "PLAY")
            {
                std::cout << "YOU WANT TO PLAY LETS PLAY" << std::endl;
                addPlayer(content, player);
            }
            else (isNewPlayer(player) == false)
            {
                priceIsRight(content, player);
            }
        }
    }
}

void bot::run()
{
    std::cout << "bot is running" << std::endl;
    _clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_clientSocket == -1)
    {
        std::cerr << "Error: socket creation failed" << std::endl;
        return;
    }
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(std::atoi(_port.c_str()));
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (connect(_clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        std::cerr << "Error: connection failed" << std::endl;
        return;
    }
    readDataBot();
}