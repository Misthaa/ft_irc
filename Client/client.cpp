/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madegryc <madegryc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:20:24 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/11 18:21:52 by madegryc         ###   ########.fr       */
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

void Client::start(char **av)
{
    struct sockaddr_in clientAddr;

    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = htons(atoi(av[1]));
    clientAddr.sin_addr.s_addr = inet_addr(av[1]);

    connect(_clientSocket, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
}