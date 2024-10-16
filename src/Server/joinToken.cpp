/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joinToken.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madegryc <madegryc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:00:02 by roguigna          #+#    #+#             */
/*   Updated: 2024/10/16 17:13:54 by madegryc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::joinToken(std::string content, int i)
{
    int countWord = 0;

    countWord = std::count(content.begin(), content.end(), ' ') + 1;
    if (countWord < 1)
    {
        sendError(_client[i], "461", "* JOIN :Not enough parameters");
        return;
    }
    if (_client[i].getNickname() == "" || _client[i].getUser() == "")
    {
        sendError(_client[i], "451", "* JOIN :You have not registered");
        return;
    }
    if (content.find_first_of("#") != 0)
    {
        sendError(_client[i], "461", "* JOIN :Not a channel");
        return;
    }
    for (int j = 0; j < MAX_CHANNEL; j++)
    {
        if (_channel[j].getChannelName() == content)
        {
            _channel[j].addClient(_client[i]);
            _channel[j].sendChannelMsg("New user in channel : " + _client[i].getNickname(), _client[i].getNickname());
            return ;
        }
    }
    _channel[i].start(content, "", _client[i]);
}