/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:20:24 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/17 17:19:12 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

Client::Client()
{
    _clientSocket = socket(AF_INET, SOCK_STREAM, 0);
}

Client::~Client()
{
    close(_clientSocket);
}

void Client::closeClient()
{
    if (_clientSocket != -1)
        close(_clientSocket);
    _clientSocket = -1;
}

void Client::start(char **av)
{
    struct sockaddr_in clientAddr;

    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = htons(atoi(av[1]));
    clientAddr.sin_addr.s_addr = inet_addr(av[1]);

    connect(_clientSocket, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
}