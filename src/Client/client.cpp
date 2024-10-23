/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:20:24 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/23 19:27:59 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

Client::Client()
{
    _clientSocket = -1;
    _correctPassword = false;
}

Client::~Client()
{
    if (_clientSocket != -1)
        close(_clientSocket);
}

void Client::closeClient()
{
    if (_clientSocket != -1)
        close(_clientSocket);
    _clientSocket = -1;
    _nickname = "";
    _user = "";
    _correctPassword = false;
}

void Client::start(char **av)
{
    _clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in clientAddr;

    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = htons(atoi(av[1]));
    clientAddr.sin_addr.s_addr = inet_addr(av[1]);

    connect(_clientSocket, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
}