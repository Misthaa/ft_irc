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

Bot::Bot(std::string nickname, std::string port, std::string password)
{
    _nickname = nickname;
    _port = port;
    _password = password;
}

Bot::~Bot()
{
    if (_clientSocket != -1)
        close(_clientSocket);
    if (_playerMap.size() > 0)
        _playerMap.clear();
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

static int	ft_stoiprice(std::string &str)
{
	int res = 0;
	int i = 0;
    std::string intMax = "2147483647";

    for (int i = 0; str[i]; i++)
    {
        if (std::isdigit(str[i]) == 0)
                return -1;
    }
    if (str.size() == intMax.size())
    {
        for (int i = 0; str[i]; i++)
        {
            if (str[i] > intMax[i])
                return -2;
        }
    }
	while (str[i])
	{
        
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res);
}

bool Bot::isNewPlayer(std::string player)
{
    for (std::map<std::string, int>::iterator it = _playerMap.begin(); it != _playerMap.end(); it++)
	{
		if (it->first == player)
			return false;
    }
    return true;
}

void Bot::addPlayer(std::string player)
{
    std::string clothing[10] = {"T-shirt 👕", "Pants 👖", "Shoes 👞", "Hat 🧢", "Gloves 🧤", "Socks 🧦", "Underwear 🩲", "Jacket 🧥", "Scarf 🧣", "Jewels 💍"};
    std::string brend[10] = {"Arte", "Nike", "Puma", "Reebok", "Vans", "Supraw", "New Balance", "Carhartt", "Champion", "Asics"};

    srand(time(NULL) + 200);
    int r_cloting = rand() % 10;
    srand(time(NULL));
    int r_brend = rand() % 10;
    std::string msg = "PRIVMSG " + player + " FIND THE PRICERIGHT OF " + brend[r_brend] + " " + clothing[r_cloting];
    response(_clientSocket, msg);
    srand(time(NULL));
    int price = rand() % 1000;
    std::cout << "PRICE : " << price << std::endl;
    _playerMap[player] = price;
}

void Bot::priceIsRight(std::string content, std::string player)
{
    std::string token = content.substr(0, content.find(" "));
    content = content.substr(content.find(" ") + 1);
    content = content.substr(0, content.find("\n") - 1);
    int price = ft_stoiprice(content);
    if (price == -1)
    {
        std::string msg = "PRIVMSG " + player + " PRICE CAN ONLY BE A POSITIVE NUMBER";
        response(_clientSocket, msg);
        return;
    }
    if (price > 1000 || price < 0)
    {
        std::string msg = "PRIVMSG " + player + " PRICE CAN ONLY BE BETWEEN 0 AND 1000";
        response(_clientSocket, msg);
        return;
    }
    if (_playerMap[player] == price)
    {
        std::string msg = "PRIVMSG " + player + " 🎉 CONGRULATIONS YOU FOUND THE RIGHT PRICE ! 🎉 \n";
        msg+= "PRIVMSG " + player + " (TYPE PLAY TO PLAY AGAIN.) 💸";
        response(_clientSocket, msg);
        _playerMap.erase(player);
    }
    else if (_playerMap[player] < price)
    {
        std::string msg = "PRIVMSG " + player + " PRICERIGHT IS LOWER 📉";
        response(_clientSocket, msg);
    }
    else
    {
        std::string msg = "PRIVMSG " + player + " PRICERIGHT IS HIGHER 📈";
        response(_clientSocket, msg);
    }
}

void Bot::readDataBot()
{
    int ret;
    _fds.events = POLLIN;
    _fds.revents = 0;
    _fds.fd = _clientSocket;

    _msg = "PASS " + _password + "\n";
    _msg += "USER bot 0 * : bot\n";
    _msg += "NICK " + _nickname + "\n";
    send(_clientSocket, _msg.c_str(), _msg.size(), MSG_NOSIGNAL | MSG_DONTWAIT);
    while (1)
    {
        ret = poll(&_fds, 1, 100);
        if (ret < 0)
        {
            std::cerr << "Error: poll failed" << std::endl;
            return;
        }
        else if (ret == 0)
            continue;
        if (_fds.revents & POLLIN)
        {
            char buff[1024];
            ret = recv(_clientSocket, buff, 1024, 0);
            if (ret <= 0)
            {
                close(_clientSocket);
                return;
            }
            buff[ret] = '\0';
            std::cout << buff << std::endl;
            std::string content = buff;
            std::string player = content.substr(0, content.find(" "));
            content = nextArg(content);
            std::string token = content.substr(0, content.find(" "));
            content = nextArg(content);
            content = nextArg(content);
            std::string tokenBot = content.substr(0, content.find("\n") - 1);
            player = player.substr(1);
            if (content[0] == ':')
                content = content.substr(1);
            if ((tokenBot == "PLAY" || tokenBot == ":PLAY") && isNewPlayer(player) == true)
                addPlayer(player);
            else if (isNewPlayer(player) == false)
                priceIsRight(content, player);
            else if (token != "401" && token != "001" && token != "421" && token != "password")
            {
                _msg = "PRIVMSG " + player + " Please use the command PLAY to start the game\n";
                response(_clientSocket, _msg);
            }
        }
    }
}

void Bot::run()
{
    // std::cout << "bot is running" << std::endl;
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