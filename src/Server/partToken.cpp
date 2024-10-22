/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   partToken.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:21:54 by madegryc          #+#    #+#             */
/*   Updated: 2024/10/21 10:48:18 by roguigna         ###   ########.fr       */
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
                sendError(_client[i], "403", "* PART :You're not on this channel");
                return ;
            }
            _channel[j].removeClient(_client[i]);
            std::string msg = ":" + _client[i].getNickname() + "!" + _client[i].getUser() + "@localhost PART " + channelName + "\n";
            _channel[j].sendToAll(msg);
            return ;
        }
    }
    sendError(_client[i], "403", "* PART :No such channel");
    return ;
}