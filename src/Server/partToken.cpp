/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   partToken.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:21:54 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/29 15:01:21 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::partToken(std::string content, int i)
{
    std::string channelName;

    channelName = content.substr(0, content.find(" "));
    for (int j = 0; j < MAX_CHANNEL; j++)
    {
        if (channelName == _channel[j].getChannelName())
        {
            if (_channel[j].isClientInChannel(_client[i]) == 0)
            {
                sendError(_client[i], "403", "IRCserv: PART :You're not on this channel");
                return ;
            }
            std::string msg = ":" + _client[i].getNickname() + "!" + _client[i].getUser() + "@localhost PART " + channelName + " :leaving\n";
            _channel[j].sendToAll(msg);
            _channel[j].removeClient(_client[i]);
            if (_channel[j].isEmptyChan() == true)
                _channel[j].clear();
            return ;
        }
    }
    sendError(_client[i], "403", "IRCserv: PART :No such channel");
    return ;
}