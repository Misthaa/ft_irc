/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   botVinted.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madegryc <madegryc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:07:53 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/22 20:18:10 by madegryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "botVinted.hpp"

botVinted::botVinted(std::string nickname, std::string port, std::string password)
{
    _nickname = nickname;
    _port = port;
    _password = password;
}

botVinted::~botVinted()
{
    close(_clientSocket);
}

void botVinted::readDataBot()
{
    int ret;
    _fds.events = POLLIN;
    _fds.revents = 0;
    _fds.fd = _clientSocket;
    std::string msg = "PASS " + _password + "\n";
    msg += "USER botVinted 0 * : botVinted\n";
    msg += "NICK " + _nickname + "\n";
    msg += "JOIN #vinted_Stussy\n";
    msg += "JOIN #vinted_Arte\n";
    msg += "JOIN #vinted_Arc'teryx\n";
    msg += "JOIN #vinted_Supraw\n";
    msg += "JOIN #vinted_Mokovel\n";
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
            std::string token = buff;
            std::string content = buff;
            std::cout << "CLIEEEENT " << _nickname << " : " << buff << std::endl;
            token = token.substr(0, token.find(" "));
            content = content.substr(content.find(" ") + 1);
        }
    }
}

void botVinted::run()
{
    std::cout << "BotVinted is running" << std::endl;
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