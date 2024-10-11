/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madegryc <madegryc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:07:16 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/11 21:17:43 by madegryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

Server::Server()
{
    _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    std::cout << "Server socket: " << _serverSocket << std::endl;
}

Server::~Server()
{
    close(_serverSocket);
    std::cout << "Server socket closed" << std::endl;
}

void Server::setPort(char *port)
{
    std::string str = port;
    if (port == NULL)
        throw std::invalid_argument("Port is NULL");
    else if (std::atoi(port) == 0)
        throw std::invalid_argument("Port is not a number");
    else if (str.length() > 5 && str.length() < 4)
        throw std::invalid_argument("Port must be between 4 and 5 characters");
    else if (std::atoi(port) < 1024)
        throw std::invalid_argument("Port is too low, must be between 1024 and 65535");
    else if (std::atoi(port) > 65535)
        throw std::invalid_argument("Port is too high, must be between 1024 and 65535");
    else
        _port = std::atoi(port);
}

void Server::setPassword(std::string password)
{
    if (password.empty())
        throw std::invalid_argument("Password is empty");
    else if (password.size() < 4)
        throw std::invalid_argument("Password is too short, must be between 4 and 16 characters");
    else if (password.size() > 16)
        throw std::invalid_argument("Password is too long, must be between 4 and 16 characters");
    else
        _password = password;
}

void Server::start(char **av)
{
    struct sockaddr_in serverAddr;

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(std::atoi(av[1]));
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(_serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    listen(_serverSocket, MAX_CLIENT);
    for (int i = 0; i < MAX_CLIENT; i++)
    {
        _fds[i].fd = -1;
        _fds[i].events = 0;
        _fds[i].revents = 0;
    }
    setPort(av[1]);
    setPassword(av[2]);
}

int Server::acceptClient()
{
    char BUFF[1024];
    _fds[0].revents = 0;
    _fds[0].events = POLLIN;
    _fds[0].fd = _serverSocket;
    
    static int nbfd;
    if (!nbfd)
        nbfd = 1;
    int i = 0;
    if (poll(_fds, MAX_CLIENT, 0) <= 0)
        return 1;
    if (_fds[0].revents & POLLIN)
    {
        std::cout << "New client is here!" << std::endl;
        int client = accept(_serverSocket, NULL, NULL);
        _fds[nbfd].fd = client;
        _fds[nbfd].events = POLLIN;
        nbfd++;
    }
    i = 1;
    while (i < MAX_CLIENT)
    {
        if (_fds[i].revents & POLLIN)
        {
            int test = recv(_fds[i].fd, BUFF, 1024, 0);
            BUFF[test] = '\0';
            std::cout << i << std::endl;
            std::cout << "CLIENT " << i << " : " << BUFF << std::endl;
        }
        i++;
    }
    return 0;
}
